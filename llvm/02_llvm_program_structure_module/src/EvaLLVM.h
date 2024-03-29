/**
 * Eva to LLVM IR compiler.
 */
#ifndef EvaLLVM_h
#define EvaLLVM_h

#include <memory>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

class EvaLLVM {
public:
    EvaLLVM() {
        moduleInit();
    }

    /**
     * Executes a program.
     */
    void exec(const std::string& program) {
        // 1. Parse the program to AST.
        // auto ast = parser->parser(program);

        // 2. Compile AST to LLVM IR.
        // compile(ast);

        // Print generated code.
        module->print(llvm::outs(), nullptr);

        // 3. Save module IR to file.
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
};

#endif
