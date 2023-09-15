/**
 * Eva to LLVM IR compiler.
 */
#ifndef EvaLLVM_h
#define EvaLLVM_h

#include <memory>
#include <regex>
#include <string>

#include "./parser/EvaParser.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

class EvaLLVM {
public:
    EvaLLVM() : parser(std::make_unique<syntax::EvaParser>()) {
        moduleInit();
        setupExternalFunctions();
    }

    /**
     * Executes a program.
     */
    void exec(const std::string& program) {
        // 1. Parse the program to AST.
        auto ast = parser->parse(program);

        // 2. Compile AST to LLVM IR.
        compile(ast);

        // Print generated code.
        module->print(llvm::outs(), nullptr);

        // 3. Save modulr IR to file.
        saveModuleToFile("./out.ll");
    }

private:
    /**
     * Initialize the module.
     */
    void moduleInit() {
        // Open a new context and module.
        ctx = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("EvaLLVM", *ctx);

        // Create a new builder for the module.
        builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
    }

    /**
     * Compiles an expression.
     */
    void compile(const Exp& ast) {
        // 1. Create main function
        fn = createFunction("main", llvm::FunctionType::get(builder->getInt32Ty(), false));

        createGlobalVar("VERSION", builder->getInt32(42));

        // 2. Compile main body
        auto result = gen(ast);

        builder->CreateRet(builder->getInt32(0));
    }

    llvm::Function* createFunction(const std::string& fnName, llvm::FunctionType* fnType) {
        // Function Prototype might already be defined
        auto fn = module->getFunction(fnName);

        // If not, allocate the function
        if (fn == nullptr) {
            fn = createFunctionProto(fnName, fnType);
        }

        createFunctionBlock(fn);
        return fn;
    }

    /**
     * Create function prototype (defines the function, but not the body).
     */
    llvm::Function* createFunctionProto(const std::string& fnName, llvm::FunctionType* fnType) {
        auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, fnName, *module);
        verifyFunction(*fn);
        return fn;
    }

    /**
     * Creates function block.
     */
    void createFunctionBlock(llvm::Function* fn) {
        auto entry = createBB("entry", fn);
        builder->SetInsertPoint(entry);
    }

    /**
     * Creates a basic block.
     *
     * If the `fn` is passed, the block is automatically appended to the
     * parent function. Otherwise, the block should later be appended
     * manually via `fn->getBasicBlockList().push_back(block);`
     */
    llvm::BasicBlock* createBB(const std::string& name, llvm::Function* fn = nullptr) {
        return llvm::BasicBlock::Create(*ctx, name, fn);
    }

    /**
     * Creates a global variable.
     */
    llvm::GlobalVariable* createGlobalVar(const std::string& name, llvm::Constant* init) {
        module->getOrInsertGlobal(name, init->getType());
        auto variable = module->getNamedGlobal(name);
        variable->setAlignment(llvm::MaybeAlign(4));
        variable->setConstant(false);
        variable->setInitializer(init);
        return variable;
    }

    /**
     * Main compile loop.
     */
    llvm::Value* gen(const Exp& exp) {
        switch (exp.type) {
            case ExpType::NUMBER: {
                return builder->getInt32(exp.number);
                break;
            }
            case ExpType::STRING: {
                // Unescape special chars.
                // TODO: support all chars or handle in parser.
                auto re = std::regex("\\\\n");
                auto str = std::regex_replace(exp.string, re, "\n");
                return builder->CreateGlobalStringPtr(str);
                break;
            }
            case ExpType::SYMBOL: {
                // Boolean
                if (exp.string == "true" || exp.string == "false") {
                    return builder->getInt1(exp.string == "true" ? true : false);
                }

                // Global variables.
                return module->getNamedGlobal(exp.string)->getInitializer();
                // TODO: support all symbols.
                break;
            }
            case ExpType::LIST: {
                auto tag = exp.list[0];
                if (tag.type == ExpType::SYMBOL) {
                    auto op = tag.string;

                    // Variable declaration:
                    //     (var x (+ y 10))
                    if (op == "var") {
                        // TODO: handle generic values.

                        auto varName = exp.list[1].string;
                        // Initializer
                        auto init = gen(exp.list[2]);
                        return createGlobalVar(varName, (llvm::Constant*)init)->getInitializer();
                    }
                    // Print extern function:
                    //     (printf "Value: %d" 42)
                    else if (op == "printf") {
                        // Get function `printf`
                        auto printfFn = module->getFunction("printf");

                        // Create args from exp list
                        std::vector<llvm::Value*> args{};
                        for (auto i = 1; i < exp.list.size(); i++) {
                            args.push_back(gen(exp.list[i]));
                        }

                        // Call function `printf`
                        return builder->CreateCall(printfFn, args);
                    }
                }
                break;
            }
        }
        return builder->getInt32(0);
    }

    /**
     * Define external functions (from libc++).
     */
    void setupExternalFunctions() {
        // i8* to substutite for char*, void*, etc
        auto bytePtrTy = builder->getInt8Ty()->getPointerTo();

        // int printf(const char* format, ...);
        module->getOrInsertFunction("printf", llvm::FunctionType::get(builder->getInt32Ty(), bytePtrTy, true));
    }

    /**
     * Saves IR to file.
     */
    void saveModuleToFile(const std::string& fileName) {
        std::error_code errorCode;
        llvm::raw_fd_ostream outLL(fileName, errorCode);
        module->print(outLL, nullptr);
    }

    /**
     * Global LLVM context.
     *
     * It owns and manages the core "global" data of LLVM's core
     * infrastructure, including the type and constant unique tables.
     */
    std::unique_ptr<llvm::LLVMContext> ctx;

    /**
     * A module instance is used to store all the information related to an
     * LLVM module. Modules are the top level container of all other LLVM
     * Intermediate Representation (IR) objects. Each module directly contains a
     * list of global variables, a list of functions, a list of libraries (or
     * other modules) this module depends on, a symbol table, and various data
     * about the target's characteristics.
     *
     * A module maintains a GlobalList object that is used to hold all
     * constant references to global variables in the module. When a global
     * variable is destroyed, it should have no entries in the GlobalList.
     * The main container class for the LLVM Intermediate Representation.
     */
    std::unique_ptr<llvm::Module> module;

    /**
     * IR Builder.
     *
     * This provides a uniform API for creating instructions and inserting
     * them into a basic block; either at the end of a BasicBlock, or at a
     * specific iterator location in a block.
     */
    std::unique_ptr<llvm::IRBuilder<>> builder;

    /**
     * Currently compiling function.
     */
    llvm::Function* fn;

    /**
     * Parser.
     */
    std::unique_ptr<syntax::EvaParser> parser;
};

#endif
