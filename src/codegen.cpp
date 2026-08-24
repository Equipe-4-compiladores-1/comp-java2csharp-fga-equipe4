#include "codegen.h"




void CSharpCodegenVisitor::generateProgram(const std::shared_ptr<ClassDeclNode>& root) {
    if (!root) return;

    std::cout << "using System;\n\n";
    std::cout << "namespace TranspiledProgram {\n";

    // Chama o visitante para processar o nó da classe
    root->accept(this);

    std::cout << "}\n";
}

void CSharpCodegenVisitor::visit(ClassDeclNode* node) {
    // Usa o nome dinâmico da classe que veio do código Java
    std::cout << "    public static class " << node->className << " {\n";

    // Visita cada função dentro da classe
    for (const auto& func : node->functions) {
        func->accept(this);
    }

    std::cout << "    }\n";
}

void CSharpCodegenVisitor::visit(FunctionDeclNode* node) {
    std::string returnType = (node->returnType == "boolean") ? "bool" : node->returnType;
    std::string name = (node->name == "main") ? "Main" : node->name;

    std::cout << "        public static " << returnType << " " << name << "() {\n";
    for (const auto& stmt : node->body) {
        stmt->accept(this);
    }
    std::cout << "        }\n\n";
}

void CSharpCodegenVisitor::visit(VarDeclNode* node) {
    std::string type = (node->type == "boolean") ? "bool" : node->type;
    std::cout << "            " << type << " " << node->name << " = ";
    if (node->initExpr) {
        node->initExpr->accept(this);
    }
    std::cout << ";\n";
}

void CSharpCodegenVisitor::visit(ReturnStmtNode* node) {
    std::cout << "            return ";
    if (node->expr) {
        node->expr->accept(this);
    }
    std::cout << ";\n";
}

void CSharpCodegenVisitor::visit(BinaryExprNode* node) {
    std::cout << "(";
    node->left->accept(this);
    std::cout << " " << node->op << " ";
    node->right->accept(this);
    std::cout << ")";
}

void CSharpCodegenVisitor::visit(LiteralNode* node) {
    std::cout << node->value;
}
void CSharpCodegenVisitor::visit(PrintStmtNode* node) {
    if (node->isNewLine) {
        std::cout << "            Console.WriteLine(";
    } else {
        std::cout << "            Console.Write(";
    }
    
    // Visita a expressão que está dentro dos parênteses
    if (node->expr) {
        node->expr->accept(this);
    }
    
    std::cout << ");\n";
}