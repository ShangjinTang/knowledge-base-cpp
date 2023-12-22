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

        (class Point3D Point
            (begin

                (var z 0)

                (def constructor (self x y z)
                    (begin
                        // ((method (super Point3D) constructor) self x y)
                        (set (prop self z) z)))

                (def calc (self)
                    0)
                    // (+ ((method (super Point3D) calc) self) (prop self z)))
            )
        )

        (var p_2d (new Point 10 20))
        (printf "p_2d.x = %d, p_2d.y = %d\n" (prop p_2d x) (prop p_2d y))

        (var p_3d (new Point3D 10 20 30))
        (printf "p_3d.x = %d, p_3d.y = %d, p_3d.z = %d\n" (prop p_3d x) (prop p_3d y) (prop p_3d z))
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
