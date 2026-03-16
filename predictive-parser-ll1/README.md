# LL(1) Predictive Parser

Implementation of a predictive parser for arithmetic expressions written in
LISP-style format.

## Features
- LEX-based lexical analysis
- LL(1) predictive parsing
- Stack-based parsing algorithm
- Binary parse tree construction
- Expression evaluation

## Files

list.l → lexical analyzer  
evalexpr.cpp → parser and evaluation engine

## Compilation

flex list.l
g++ evalexpr.cpp -o parser

## Run

./parser < input.txt
