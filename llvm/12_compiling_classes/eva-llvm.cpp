/**
 * Eva LLVM executable.
 */
#include "./src/EvaLLVM.h"

int main(int argc, char *argv[]) {
    /**
     * Program to execute.
     */
    std::string program = R"(

        (class Point null
            (begin

                (var x 0)
                (var y 0)

                (def constructor (self x y)
                    (begin
                        0))
                        // (set (prop self x) x)
                        // (set (prop self y) y)))

                (def calc (self)
                    0)
                    // (+ (prop self x) (prop self y)))
            )
        )
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
