#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <sstream>
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
        // 1. Redireciona o cout para um buffer de memória virtual
        std::stringstream buffer;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());

        // 2. Inicia a geração de código
        CSharpCodegenVisitor codegen;
        if (rootNode) {
            codegen.generateProgram(rootNode); 
        }

        // 3. Restaura o cout IMEDIATAMENTE para o terminal real
        std::cout.rdbuf(oldCoutBuffer);

        // 4. Captura o código gerado em uma string
        std::string codigoCsharp = buffer.str();

        // 5. Grava fisicamente no arquivo
        std::ofstream outFile("Saida.cs");
        outFile << codigoCsharp;
        outFile.close();

        // 6. Imprime no terminal para a equipe visualizar
        std::cout << "\n========== CODIGO GERADO ==========\n";
        std::cout << codigoCsharp;
        std::cout << "===================================\n";
        std::cout << "Arquivo 'Saida.cs' gerado com sucesso.\n";
    } else {
        std::cerr << "Falha na compilacao." << std::endl;
        return 1;
    }

    return 0;
}