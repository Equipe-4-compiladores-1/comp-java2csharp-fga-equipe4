#include "codegen.h"

void CSharpCodegenVisitor::generateProgram(const std::vector<std::shared_ptr<FunctionDeclNode>>& functions) {
    std::cout << "using System;\n\n";
    std::cout << "namespace TranspiledProgram {\n";
    std::cout << "    public static class Program {\n";

    for (const auto& func : functions) {
        func->accept(this);
    }

    std::cout << "    }\n";
    std::cout << "}\n";
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