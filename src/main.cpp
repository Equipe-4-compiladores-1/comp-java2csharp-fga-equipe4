#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include "ast.h"
#include "codegen.h"

extern FILE* yyin;
extern int yyparse();
extern std::vector<std::shared_ptr<FunctionDeclNode>> programFunctions;
extern std::shared_ptr<ClassDeclNode> rootNode;

int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
            return 1;
        }
        yyin = file;
    } else {
        std::cout << "Lendo da entrada padrao (Ctrl+D para encerrar)..." << std::endl;
    }

    // Executa a Análise Sintática
    if (yyparse() == 0) {
        // Gera o código C#
        CSharpCodegenVisitor codegen;
        codegen.generateProgram(rootNode);
    } else {
        std::cerr << "Falha na compilacao." << std::endl;
        return 1;
    }

    return 0;
}