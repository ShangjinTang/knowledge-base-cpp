; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"

@VERSION = global i32 42, align 4
@0 = private unnamed_addr constant [7 x i8] c"X: %d\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"X == 42\0A\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"X < 42\0A\00", align 1
@3 = private unnamed_addr constant [8 x i8] c"X > 42\0A\00", align 1
@4 = private unnamed_addr constant [6 x i8] c"X: %d\00", align 1
@5 = private unnamed_addr constant [7 x i8] c" -> %d\00", align 1
@6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 10, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 %x1)
  %x2 = load i32, ptr %x, align 4
  %tmpcmp = icmp eq i32 %x2, 42
  br i1 %tmpcmp, label %then, label %else

then:                                             ; preds = %entry
  %1 = call i32 (ptr, ...) @printf(ptr @1)
  br label %ifend7

else:                                             ; preds = %entry
  %x3 = load i32, ptr %x, align 4
  %tmpcmp4 = icmp ult i32 %x3, 42
  br i1 %tmpcmp4, label %then5, label %else6

then5:                                            ; preds = %else
  %2 = call i32 (ptr, ...) @printf(ptr @2)
  br label %ifend

else6:                                            ; preds = %else
  %3 = call i32 (ptr, ...) @printf(ptr @3)
  br label %ifend

ifend:                                            ; preds = %else6, %then5
  %tmpif = phi i32 [ %2, %then5 ], [ %3, %else6 ]
  br label %ifend7

ifend7:                                           ; preds = %ifend, %then
  %tmpif8 = phi i32 [ %1, %then ], [ %tmpif, %ifend ]
  %x9 = load i32, ptr %x, align 4
  %4 = call i32 (ptr, ...) @printf(ptr @4, i32 %x9)
  br label %cond

cond:                                             ; preds = %body, %ifend7
  %x10 = load i32, ptr %x, align 4
  %tmpcmp11 = icmp ugt i32 %x10, 0
  br i1 %tmpcmp11, label %body, label %loopend

body:                                             ; preds = %cond
  %x12 = load i32, ptr %x, align 4
  %tmpsub = sub i32 %x12, 2
  store i32 %tmpsub, ptr %x, align 4
  %x13 = load i32, ptr %x, align 4
  %5 = call i32 (ptr, ...) @printf(ptr @5, i32 %x13)
  br label %cond

loopend:                                          ; preds = %cond
  %6 = call i32 (ptr, ...) @printf(ptr @6)
  ret i32 0
}
