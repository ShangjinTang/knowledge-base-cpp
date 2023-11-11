# README

`syntax-cli` is required for this chapter.

Installation:

```bash
npm install --global syntax-cli
```

## Basic If-Expression Implementation

This is just for comparision to show how basic if-expression (do not support nested if) is implemented.

For nested if-expression support, see source code file.

```cpp
else if (op == "if") {
    // Compile "if <cond>"
    auto cond = gen(exp.list[1], env);

    // Create blocks
    auto thenBlock = createBB("then", fn);
    auto elseBlock = createBB("else", fn);
    auto ifEndBlock = createBB("ifend", fn);

    // Conditional branch
    builder->CreateCondBr(cond, thenBlock, elseBlock);

    // Block "then"
    builder->SetInsertPoint(thenBlock);
    auto thenRes = gen(exp.list[2], env);
    builder->CreateBr(ifEndBlock);

    // Block "else"
    builder->SetInsertPoint(elseBlock);
    auto elseRes = gen(exp.list[3], env);
    builder->CreateBr(ifEndBlock);

    // Block "ifend"
    builder->SetInsertPoint(ifEndBlock);

    // Result of the if-expression is `phi` in llvm
    auto phi = builder->CreatePHI(builder->getInt32Ty(), 2, "tmpif");

    phi->addIncoming(thenRes, thenBlock);
    phi->addIncoming(elseRes, elseBlock);

    return phi;
}
```

## LLVM API Change

code on llvm old version:

```cpp
fn->getBasicBlockList().push_back(someBlock);
```

code on llvm new version:

```cpp
fn->insert(fn->end(), someBlock);
```
