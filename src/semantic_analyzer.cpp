#include "semantic_analyzer.h"

bool SemanticAnalyzerVisitor::analyze(const std::shared_ptr<ClassDeclNode>& root) {
    if (root) root->accept(this);
    return !hasErrors;
}

void SemanticAnalyzerVisitor::visit(ClassDeclNode* node) {
    for (auto& func : node->functions) {
        func->accept(this);
    }
}

void SemanticAnalyzerVisitor::visit(FunctionDeclNode* node) {
    symTable.enterScope();

    for (const auto& param : node->params) {
        if (!symTable.defineSymbol(param.name, param.type)) {
            std::cerr << "Erro Semântico: Parâmetro '" << param.name
                      << "' redefinido na função '" << node->name << "'.\n";
            hasErrors = true;
        }
    }

    for (auto& stmt : node->body) {
        if (stmt) stmt->accept(this);
    }

    symTable.exitScope();
}

void SemanticAnalyzerVisitor::visit(VarDeclNode* node) {
    if (node->initExpr) {
        node->initExpr->accept(this);
    }
    
    if (!symTable.defineSymbol(node->name, node->type)) {
        std::cerr << "Erro Semântico: Variável '" << node->name 
                  << "' já foi declarada neste escopo.\n";
        hasErrors = true;
    }
}

void SemanticAnalyzerVisitor::visit(LiteralNode* node) {
    if (!node->value.empty() && isalpha(node->value[0])) {
        SymbolInfo info;
        if (!symTable.resolveSymbol(node->value, info)) {
            std::cerr << "Erro Semântico: Uso de variável não declarada '" << node->value << "'.\n";
            hasErrors = true;
        }
    }
}

void SemanticAnalyzerVisitor::visit(BinaryExprNode* node) {
    if (node->left) node->left->accept(this);
    if (node->right) node->right->accept(this);
}
void SemanticAnalyzerVisitor::visit(ReturnStmtNode* node) {
    if (node->expr) node->expr->accept(this);
}
void SemanticAnalyzerVisitor::visit(PrintStmtNode* node) {
    if (node->expr) node->expr->accept(this);
}
void SemanticAnalyzerVisitor::visit(PrintfStmtNode* node) {
    for (auto& arg : node->args) arg->accept(this);
}
void SemanticAnalyzerVisitor::visit(MethodCallExprNode* node) {
    for (auto& arg : node->args) arg->accept(this);
}
void SemanticAnalyzerVisitor::visit(MethodCallStmtNode* node) {
    for (auto& arg : node->args) arg->accept(this);
}
void SemanticAnalyzerVisitor::visit(StringNode* node) {}
