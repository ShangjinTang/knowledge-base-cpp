; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"
target triple = "x86_64-pc-linux-gnu"

%Point_vTable = type { i32 (%Point*)*, i32 (%Point*, i32, i32)* }
%Point = type { %Point_vTable*, i32, i32 }
%Point3D_vTable = type { i32 (%Point3D*)*, i32 (%Point3D*, i32, i32, i32)* }
%Point3D = type { %Point3D_vTable*, i32, i32, i32 }

@VERSION = global i32 42, align 4
@Point_vTable = global %Point_vTable { i32 (%Point*)* @Point_calc, i32 (%Point*, i32, i32)* @Point_constructor }, align 4
@Point3D_vTable = global %Point3D_vTable { i32 (%Point3D*)* @Point3D_calc, i32 (%Point3D*, i32, i32, i32)* @Point3D_constructor }, align 4
@0 = private unnamed_addr constant [26 x i8] c"p_2d.x = %d, p_2d.y = %d\0A\00", align 1
@1 = private unnamed_addr constant [39 x i8] c"p_3d.x = %d, p_3d.y = %d, p_3d.z = %d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i8* @GC_malloc(i64)

define i32 @main() {
entry:
  %p_2d = call i8* @GC_malloc(i64 16)
  %0 = bitcast i8* %p_2d to %Point*
  %1 = getelementptr inbounds %Point, %Point* %0, i32 0, i32 0
  store %Point_vTable* @Point_vTable, %Point_vTable** %1, align 8
  %2 = call i32 @Point_constructor(%Point* %0, i32 10, i32 20)
  %px = getelementptr inbounds %Point, %Point* %0, i32 0, i32 1
  %x = load i32, i32* %px, align 4
  %py = getelementptr inbounds %Point, %Point* %0, i32 0, i32 2
  %y = load i32, i32* %py, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @0, i32 0, i32 0), i32 %x, i32 %y)
  %p_3d = call i8* @GC_malloc(i64 24)
  %4 = bitcast i8* %p_3d to %Point3D*
  %5 = getelementptr inbounds %Point3D, %Point3D* %4, i32 0, i32 0
  store %Point3D_vTable* @Point3D_vTable, %Point3D_vTable** %5, align 8
  %6 = call i32 @Point3D_constructor(%Point3D* %4, i32 10, i32 20, i32 30)
  %px1 = getelementptr inbounds %Point3D, %Point3D* %4, i32 0, i32 1
  %x2 = load i32, i32* %px1, align 4
  %py3 = getelementptr inbounds %Point3D, %Point3D* %4, i32 0, i32 2
  %y4 = load i32, i32* %py3, align 4
  %pz = getelementptr inbounds %Point3D, %Point3D* %4, i32 0, i32 3
  %z = load i32, i32* %pz, align 4
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @1, i32 0, i32 0), i32 %x2, i32 %y4, i32 %z)
  %8 = call i32 @check(%Point* %0)
  %9 = bitcast %Point3D* %4 to %Point*
  %10 = call i32 @check(%Point* %9)
  ret i32 0
}

define i32 @Point_constructor(%Point* %self, i32 %x, i32 %y) {
entry:
  %self1 = alloca %Point*, align 8
  store %Point* %self, %Point** %self1, align 8
  %x2 = alloca i32, align 4
  store i32 %x, i32* %x2, align 4
  %y3 = alloca i32, align 4
  store i32 %y, i32* %y3, align 4
  %x4 = load i32, i32* %x2, align 4
  %self5 = load %Point*, %Point** %self1, align 8
  %px = getelementptr inbounds %Point, %Point* %self5, i32 0, i32 1
  store i32 %x4, i32* %px, align 4
  %y6 = load i32, i32* %y3, align 4
  %self7 = load %Point*, %Point** %self1, align 8
  %py = getelementptr inbounds %Point, %Point* %self7, i32 0, i32 2
  store i32 %y6, i32* %py, align 4
  ret i32 %y6
}

define i32 @Point_calc(%Point* %self) {
entry:
  %self1 = alloca %Point*, align 8
  store %Point* %self, %Point** %self1, align 8
  %self2 = load %Point*, %Point** %self1, align 8
  %px = getelementptr inbounds %Point, %Point* %self2, i32 0, i32 1
  %x = load i32, i32* %px, align 4
  %self3 = load %Point*, %Point** %self1, align 8
  %py = getelementptr inbounds %Point, %Point* %self3, i32 0, i32 2
  %y = load i32, i32* %py, align 4
  %tmpadd = add i32 %x, %y
  ret i32 %tmpadd
}

define i32 @Point3D_constructor(%Point3D* %self, i32 %x, i32 %y, i32 %z) {
entry:
  %self1 = alloca %Point3D*, align 8
  store %Point3D* %self, %Point3D** %self1, align 8
  %x2 = alloca i32, align 4
  store i32 %x, i32* %x2, align 4
  %y3 = alloca i32, align 4
  store i32 %y, i32* %y3, align 4
  %z4 = alloca i32, align 4
  store i32 %z, i32* %z4, align 4
  %0 = load i32 (%Point*, i32, i32)*, i32 (%Point*, i32, i32)** getelementptr inbounds (%Point_vTable, %Point_vTable* @Point_vTable, i32 0, i32 1), align 8
  %self5 = load %Point3D*, %Point3D** %self1, align 8
  %1 = bitcast %Point3D* %self5 to %Point*
  %x6 = load i32, i32* %x2, align 4
  %y7 = load i32, i32* %y3, align 4
  %2 = call i32 %0(%Point* %1, i32 %x6, i32 %y7)
  %z8 = load i32, i32* %z4, align 4
  %self9 = load %Point3D*, %Point3D** %self1, align 8
  %pz = getelementptr inbounds %Point3D, %Point3D* %self9, i32 0, i32 3
  store i32 %z8, i32* %pz, align 4
  ret i32 %z8
}

define i32 @Point3D_calc(%Point3D* %self) {
entry:
  %self1 = alloca %Point3D*, align 8
  store %Point3D* %self, %Point3D** %self1, align 8
  %0 = load i32 (%Point*)*, i32 (%Point*)** getelementptr inbounds (%Point_vTable, %Point_vTable* @Point_vTable, i32 0, i32 0), align 8
  %self2 = load %Point3D*, %Point3D** %self1, align 8
  %1 = bitcast %Point3D* %self2 to %Point*
  %2 = call i32 %0(%Point* %1)
  %self3 = load %Point3D*, %Point3D** %self1, align 8
  %pz = getelementptr inbounds %Point3D, %Point3D* %self3, i32 0, i32 3
  %z = load i32, i32* %pz, align 4
  %tmpadd = add i32 %2, %z
  ret i32 %tmpadd
}

define i32 @check(%Point* %obj) {
entry:
  %obj1 = alloca %Point*, align 8
  store %Point* %obj, %Point** %obj1, align 8
  %obj2 = load %Point*, %Point** %obj1, align 8
  %0 = getelementptr inbounds %Point, %Point* %obj2, i32 0, i32 0
  %vt = load %Point_vTable*, %Point_vTable** %0, align 8
  %1 = getelementptr inbounds %Point_vTable, %Point_vTable* %vt, i32 0, i32 0
  %2 = load i32 (%Point*)*, i32 (%Point*)** %1, align 8
  %obj3 = load %Point*, %Point** %obj1, align 8
  %3 = call i32 %2(%Point* %obj3)
  ret i32 %3
}
