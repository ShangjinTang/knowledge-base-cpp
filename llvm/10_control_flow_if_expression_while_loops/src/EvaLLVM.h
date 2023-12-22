/**
 * Eva to LLVM IR compiler.
 */
#ifndef EvaLLVM_h
#define EvaLLVM_h

#include <memory>
#include <regex>
#include <string>

#include "./Environment.h"
#include "./parser/EvaParser.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

// Generic binary operator.
#define GEN_BINARY_OP(Op, varName)             \
    do {                                       \
        auto op1 = gen(exp.list[1], env);      \
        auto op2 = gen(exp.list[2], env);      \
        return builder->Op(op1, op2, varName); \
    } while (false)

class EvaLLVM {
public:
    EvaLLVM() : parser(std::make_unique<syntax::EvaParser>()) {
        moduleInit();
        setupExternalFunctions();
        setupGlobalEnvironment();
    }

    /**
     * Executes a program.
     */
    void exec(const std::string& program) {
        // 1. Parse the program to AST.
        auto ast = parser->parse("(begin " + program + ")");

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

        // Create a new builder for variables
        varsBuilder = std::make_unique<llvm::IRBuilder<>>(*ctx);
    }

    /**
     * Compiles an expression.
     */
    void compile(const Exp& ast) {
        // 1. Create main function
        fn = createFunction("main", llvm::FunctionType::get(builder->getInt32Ty(), false), GlobalEnv);

        createGlobalVar("VERSION", builder->getInt32(42));

        // 2. Compile main body
        gen(ast, GlobalEnv);

        builder->CreateRet(builder->getInt32(0));
    }

    llvm::Function* createFunction(const std::string& fnName, llvm::FunctionType* fnType,
                                   std::shared_ptr<Environment> env) {
        // Function Prototype might already be defined
        auto fn = module->getFunction(fnName);

        // If not, allocate the function
        if (fn == nullptr) {
            fn = createFunctionProto(fnName, fnType, env);
        }

        createFunctionBlock(fn);
        return fn;
    }

    /**
     * Create function prototype (defines the function, but not the body).
     */
    llvm::Function* createFunctionProto(const std::string& fnName, llvm::FunctionType* fnType,
                                        std::shared_ptr<Environment> env) {
        auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, fnName, *module);

        verifyFunction(*fn);

        // Install in the environment.
        env->define(fnName, fn);

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
    llvm::Value* gen(const Exp& exp, std::shared_ptr<Environment> env) {
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

                // Variables.
                auto varName = exp.string;
                auto value = env->lookup(varName);

                // 1. Local variables.
                if (auto localVar = llvm::dyn_cast<llvm::AllocaInst>(value)) {
                    return builder->CreateLoad(localVar->getAllocatedType(), localVar, varName.c_str());
                }

                // 2. Global variables.
                else if (auto globalVar = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
                    return builder->CreateLoad(globalVar->getInitializer()->getType(), globalVar, varName.c_str());
                }

                break;
            }
            case ExpType::LIST: {
                auto tag = exp.list[0];
                if (tag.type == ExpType::SYMBOL) {
                    auto op = tag.string;

                    // Binary math operations:
                    //     (+ a b)
                    //     (- a b)
                    //     (* a b)
                    //     (/ a b)
                    if (op == "+") {
                        GEN_BINARY_OP(CreateAdd, "tmpadd");
                    } else if (op == "-") {
                        GEN_BINARY_OP(CreateSub, "tmpsub");
                    } else if (op == "*") {
                        GEN_BINARY_OP(CreateMul, "tmpadd");
                    } else if (op == "/") {
                        GEN_BINARY_OP(CreateSDiv, "tmpdiv");
                    }

                    // Comparison operations:
                    //     (< a b)
                    //     (<= a b)
                    //     (> a b)
                    //     (>= a b)
                    //     (== a b)
                    //     (!= a b)
                    else if (op == "<") {
                        // ULT - unsigned, less than
                        GEN_BINARY_OP(CreateICmpULT, "tmpcmp");
                    } else if (op == "<=") {
                        // ULE - unsigned, less than or equal
                        GEN_BINARY_OP(CreateICmpULE, "tmpcmp");
                    } else if (op == ">") {
                        // UGT - unsigned, greater than
                        GEN_BINARY_OP(CreateICmpUGT, "tmpcmp");
                    } else if (op == ">=") {
                        // UGE - unsigned, greater than or equal
                        GEN_BINARY_OP(CreateICmpUGE, "tmpcmp");
                    } else if (op == "==") {
                        // EQ - equal
                        GEN_BINARY_OP(CreateICmpEQ, "tmpcmp");
                    } else if (op == "!=") {
                        // NE - not equal
                        GEN_BINARY_OP(CreateICmpNE, "tmpcmp");
                    }

                    // If instructions:
                    //     (if <cond> <expression1> <expression2>)
                    else if (op == "if") {
                        // Compile "if <cond>"
                        auto cond = gen(exp.list[1], env);

                        // Create blocks "then", appended to fn
                        auto thenBlock = createBB("then", fn);

                        // Create blocks "else" "ifend" - appended later
                        // to handle nested if-expressions
                        auto elseBlock = createBB("else");
                        auto ifEndBlock = createBB("ifend");

                        // Conditional branch
                        builder->CreateCondBr(cond, thenBlock, elseBlock);

                        // Block "then"
                        builder->SetInsertPoint(thenBlock);
                        auto thenRes = gen(exp.list[2], env);
                        builder->CreateBr(ifEndBlock);

                        // Block "else" (support nested if-expressions)
                        //   Restore the block to handle nested if-expressions.
                        //   This is needed for `phi` instruction.
                        thenBlock = builder->GetInsertBlock();
                        //   Append the block to the function now.
                        // Note: code on llvm version>=16: fn->insert(fn->end(), elseBlock);
                        fn->getBasicBlockList().push_back(elseBlock);
                        builder->SetInsertPoint(elseBlock);
                        auto elseRes = gen(exp.list[3], env);
                        builder->CreateBr(ifEndBlock);

                        // Block "ifend" (support nested if-expressions)
                        //   Restore the block to handle nested if-expressions.
                        //   This is needed for `phi` instruction.
                        elseBlock = builder->GetInsertBlock();
                        //   Append the block to the function now.
                        // Note: code on llvm version>=16: fn->insert(fn->end(), ifEndBlock);
                        fn->getBasicBlockList().push_back(ifEndBlock);
                        builder->SetInsertPoint(ifEndBlock);

                        // Result of the if-expression is `phi` in llvm
                        auto phi = builder->CreatePHI(thenRes->getType(), 2, "tmpif");

                        phi->addIncoming(thenRes, thenBlock);
                        phi->addIncoming(elseRes, elseBlock);

                        return phi;
                    }

                    // If instructions:
                    //     (while <cond> <expression1>)
                    else if (op == "while") {
                        // Condition
                        auto condBlock = createBB("cond", fn);
                        builder->CreateBr(condBlock);

                        // Create blocks "body" "loopend"
                        auto bodyBlock = createBB("body");
                        auto loopEndBlock = createBB("loopend");

                        // Compile <cond>
                        builder->SetInsertPoint(condBlock);
                        auto cond = gen(exp.list[1], env);

                        // Condition branch
                        builder->CreateCondBr(cond, bodyBlock, loopEndBlock);

                        // Body
                        // Note: code on llvm version>=16: fn->insert(fn->end(), bodyBlock);
                        fn->getBasicBlockList().push_back(bodyBlock);
                        builder->SetInsertPoint(bodyBlock);
                        gen(exp.list[2], env);
                        builder->CreateBr(condBlock);

                        // Note: code on llvm version>=16: fn->insert(fn->end(), loopEndBlock);
                        fn->getBasicBlockList().push_back(loopEndBlock);
                        builder->SetInsertPoint(loopEndBlock);

                        return builder->getInt32(0);
                    }
                    // Variable declaration:
                    //     (var x (+ y 10))
                    //     (var (x number) 42)
                    // Note: local variables are allocated on the stack.
                    else if (op == "var") {
                        auto varNameDecl = exp.list[1];
                        auto varName = extractVarName(varNameDecl);
                        // Initializer
                        auto init = gen(exp.list[2], env);
                        // Type
                        auto varTy = extractVarType(varNameDecl);
                        // Variable
                        auto varBinding = allocVar(varName, varTy, env);
                        // Set value
                        return builder->CreateStore(init, varBinding);
                    }

                    // Blocks:
                    //     (set x 100)
                    else if (op == "set") {
                        auto varName = exp.list[1].string;

                        // Value
                        auto value = gen(exp.list[2], env);

                        // Variable
                        auto varBinding = env->lookup(varName);

                        // Set value
                        builder->CreateStore(value, varBinding);

                        // return value
                        return value;
                    }

                    // Blocks:
                    //     (begin <expression>)
                    else if (op == "begin") {
                        // Block scope.
                        auto blockEnv = std::make_shared<Environment>(std::map<std::string, llvm::Value*>{}, env);

                        // Compile each expression within the block.
                        // Result is the latest evaluated expression.
                        llvm::Value* blockRes;
                        for (auto i = 1; i < exp.list.size(); i++) {
                            blockRes = gen(exp.list[i], blockEnv);
                        }
                        return blockRes;
                    }

                    // Print extern function:
                    //     (printf "Value: %d" 42)
                    else if (op == "printf") {
                        // Get function `printf`
                        auto printfFn = module->getFunction("printf");

                        // Create args from exp list
                        std::vector<llvm::Value*> args{};
                        for (auto i = 1; i < exp.list.size(); i++) {
                            args.push_back(gen(exp.list[i], env));
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
     * Sets up the global environment.
     */
    void setupGlobalEnvironment() {
        std::map<std::string, llvm::Value*> globalObject{
                {"VERSION", builder->getInt32(42)},
        };
        std::map<std::string, llvm::Value*> globalRec{};

        for (const auto& entry : globalObject) {
            globalRec[entry.first] = createGlobalVar(entry.first, (llvm::Constant*)entry.second);
        }

        GlobalEnv = std::make_shared<Environment>(globalRec, nullptr);
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
     * Extracts var or parameter name considering type.
     *     x -> x
     *     (x number) -> x
     */
    std::string extractVarName(const Exp& exp) {
        return exp.type == ExpType::LIST ? exp.list[0].string : exp.string;
    }

    /**
     * Extracts var or parameter name with i32 as default.
     *     x -> i32
     *     (x number) -> number
     */
    llvm::Type* extractVarType(const Exp& exp) {
        return exp.type == ExpType::LIST ? getTypeFromString(exp.list[1].string) : builder->getInt32Ty();
    }

    /**
     * Returns LLVM type from string representation.
     */
    llvm::Type* getTypeFromString(const std::string& type_) {
        // number -> i32
        if (type_ == "number") {
            return builder->getInt32Ty();
        }
        // string -> i8* (aka char*)
        if (type_ == "string") {
            return builder->getInt8Ty()->getPointerTo();
        }
        // default:
        return builder->getInt32Ty();
    }

    /**
     * Allocate a local variable on the stack.
     * Result is the alloca instruction.
     */
    llvm::Value* allocVar(const std::string& name, llvm::Type* type_, std::shared_ptr<Environment> env) {
        varsBuilder->SetInsertPoint(&fn->getEntryBlock());

        auto varAlloc = varsBuilder->CreateAlloca(type_, 0, name.c_str());

        // Add to the environment.
        env->define(name, varAlloc);

        return varAlloc;
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
     * Extra builder for variables declaration.
     * This builder always prepends to the beginning of the
     * function entry block.
     */
    std::unique_ptr<llvm::IRBuilder<>> varsBuilder;

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

    /**
     * Global environment (Symbol Table).
     */
    std::shared_ptr<Environment> GlobalEnv;
};

#endif
