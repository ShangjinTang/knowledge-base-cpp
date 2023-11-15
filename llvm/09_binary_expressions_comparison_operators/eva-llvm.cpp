/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        (var z 32)

        (var x (+ z 10))

        // (begin
        //     (var (x string) "Hello")
        //     (printf "X: %s\n" x))

        (printf "X: %d\n" x)

        // (set x 100)

        (printf "Is X == 42?: %d\n" (== x 42))
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
