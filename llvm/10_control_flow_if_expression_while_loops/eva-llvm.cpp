/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        (var x 10)

        (printf "X: %d\n" x)

        (if (== x 42)
            (printf "X == 42\n")
            (if (< x 42)
                (printf "X < 42\n")
                (printf "X > 42\n")))

        (printf "X: %d" x)

        (while (> x 0)
            (begin
                (set x (- x 2))
                (printf " -> %d" x)))

        (printf "\n")

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
