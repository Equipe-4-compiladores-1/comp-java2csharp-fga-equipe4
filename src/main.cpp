#include <iostream>
#include <fstream>
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


    // 1. Cria e abre um arquivo chamado Program.cs
    std::ofstream outFile("Saida.cs");
    
    // 2. Salva o destino original do cout (o terminal)
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    
    // 3. Redireciona tudo que for impresso no cout para o arquivo
    std::cout.rdbuf(outFile.rdbuf());

    // 4. Inicia a geração de código (ele acha que está imprimindo na tela, mas vai pro arquivo!)
    CSharpCodegenVisitor codegen;
    if (rootNode) {
        rootNode->accept(&codegen);
    }

    // 5. Devolve o cout para o terminal e fecha o arquivo
    std::cout.rdbuf(oldCoutBuffer);
    outFile.close();

    // 6. Imprime uma mensagem de sucesso no terminal real
    std::cout << "Arquivo 'Saida.cs' gerado com sucesso.\n";

    return 0;
}