#ifndef CODEGEN_H
#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <iostream>
#include <vector>
#include <memory>

class CSharpCodegenVisitor : public ASTVisitor {
public:
    void generateProgram(const std::vector<std::shared_ptr<FunctionDeclNode>>& functions);

    void visit(BinaryExprNode* node) override;
    void visit(LiteralNode* node) override;
    void visit(VarDeclNode* node) override;
    void visit(ReturnStmtNode* node) override;
    void visit(FunctionDeclNode* node) override;
};

#endif