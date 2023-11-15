#!/bin/bash

# check if syntax-cli installed
if ! command -v syntax-cli &> /dev/null; then
    echo "'syntax-cli' not found, please install it by:"
    echo "    npm install --global syntax-cli@0.1.27"
    echo "and make sure 'syntax-cli' is in PATH"
    exit 1
fi

# Generate the parser
syntax-cli -g src/parser/EvaGrammar.bnf -m LALR1 -o src/parser/EvaParser.h

# Compile main
clang++ -o eva-llvm $(llvm-config --cxxflags --ldflags --system-libs --libs core) -fexceptions eva-llvm.cpp

# Run main
./eva-llvm

# Execute generated IR
lli ./out.ll
