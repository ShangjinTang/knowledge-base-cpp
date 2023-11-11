/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        (def square (x) (* x x))

        (square 2)

        (def sum ((a number) (b number)) -> number (+ a b))

        (sum 2 3)

        (printf "value 2^2 : %d\n" (square 2))
        (printf "value 2+3 : %d\n" (sum 2 3))

        0
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
