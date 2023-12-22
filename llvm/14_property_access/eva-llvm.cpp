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
                        (set (prop self x) x)
                        (set (prop self y) y)))

                (def calc (self)
                    (+ (prop self x) (prop self y)))
            )
        )

        (var p (new Point 10 20))

        (printf "p.x = %d, p.y = %d\n" (prop p x) (prop p y))
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
