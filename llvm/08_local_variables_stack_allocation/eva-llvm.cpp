/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        (var x 42)

        (begin
            (var (x string) "Hello")
            (printf "X: %s\n" x))

        (printf "X: %d\n" x)

        (set x 100)

        (printf "X: %d\n" x)
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
