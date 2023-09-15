/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        // (var VERSION 42)

        // (begin
        //     (var VERSION "Hello")
        //     (printf "Version: %s\n" VERSION))

        (printf "Version: %d\n" VERSION)

    )";

    /**
     * Compiler instance.
     */
    EvaLLVM vm;

    /**
     * Generate LLVM IR.
     */
    vm.exec(program);

    return 0;
}
