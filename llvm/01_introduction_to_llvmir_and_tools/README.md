# README

## .cpp -> .ll

```bash
clang++ -S -emit-llvm test.cpp
```

## .ll -> .bc

```bash
llvm-as test.ll
```

## .bc -> .ll

```bash
llvm-dis test.bc -o test-2.ll
```

## .cpp / .ll / .bc -> .s

```bash
clang -S test.cpp
```

or

```bash
clang -S test.ll
```

or

```bash
clang -S test.bc
```
