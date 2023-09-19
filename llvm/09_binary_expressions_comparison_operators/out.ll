; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"

@VERSION = global i32 42, align 4
@0 = private unnamed_addr constant [7 x i8] c"X: %d\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"Is X == 42?: %d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %z = alloca i32, align 4
  store i32 32, ptr %z, align 4
  %z1 = load i32, ptr %z, align 4
  %tmpadd = add i32 %z1, 10
  %x = alloca i32, align 4
  store i32 %tmpadd, ptr %x, align 4
  %x2 = load i32, ptr %x, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %x2)
  %x3 = load i32, ptr %x, align 4
  %tmpcmp = icmp eq i32 %x3, 42
  %1 = call i32 (ptr, ...) @printf(ptr @1, i1 %tmpcmp)
  ret i32 0
}
