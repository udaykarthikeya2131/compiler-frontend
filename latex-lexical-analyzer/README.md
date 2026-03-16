# LaTeX Lexical Analyzer

Lex-based program to analyze LaTeX files and report statistics about commands,
environments, and mathematical expressions.

## Features
- Detects LaTeX commands
- Tracks environment usage
- Counts inline math formulas
- Counts displayed equations

## Files

latex.l → Lex specification  
procltx.cpp → statistics generator

## Compilation

flex latex.l
g++ procltx.cpp -o analyzer

## Run

./analyzer < file.tex
