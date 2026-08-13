%{
#include "ast.h"
#include <iostream>
#include <vector>
#include <memory>

extern int yylex();
void yyerror(const char* s);

std::vector<std::shared_ptr<FunctionDeclNode>> programFunctions;
%}

%union {
    char* sval;
    ASTNode* node;
    StmtNode* stmt;
    ExprNode* expr;
    std::vector<std::shared_ptr<StmtNode>>* stmt_list;
}

%token <sval> IDENTIFIER TYPE_INT TYPE_BOOL TYPE_VOID INT_LITERAL
%token RETURN

%type <stmt> var_decl stmt
%type <expr> expr
%type <stmt_list> stmt_list
%type <sval> type_specifier

%left '+' '-'
%left '*' '/'

%%

program:
    function_list
    ;

function_list:
    function_decl
    | function_list function_decl
    ;

type_specifier:
    TYPE_INT  { $$ = $1; }
    | TYPE_BOOL { $$ = $1; }
    | TYPE_VOID { $$ = $1; }
    ;

function_decl:
    type_specifier IDENTIFIER '(' ')' '{' stmt_list '}' {
        auto func = std::make_shared<FunctionDeclNode>($1, $2);
        func->body = *$6;
        delete $6;
        programFunctions.push_back(func);
    }
    ;

stmt_list:
    /* vazio */ { $$ = new std::vector<std::shared_ptr<StmtNode>>(); }
    | stmt_list stmt {
        $1->push_back(std::shared_ptr<StmtNode>($2));
        $$ = $1;
    }
    ;

stmt:
    var_decl ';' { $$ = $1; }
    | RETURN expr ';' { $$ = new ReturnStmtNode(std::shared_ptr<ExprNode>($2)); }
    ;

var_decl:
    type_specifier IDENTIFIER '=' expr {
        $$ = new VarDeclNode($1, $2, std::shared_ptr<ExprNode>($4));
    }
    ;

expr:
    INT_LITERAL { $$ = new LiteralNode($1); }
    | expr '+' expr { $$ = new BinaryExprNode("+", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '-' expr { $$ = new BinaryExprNode("-", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '*' expr { $$ = new BinaryExprNode("*", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '/' expr { $$ = new BinaryExprNode("/", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Erro sintatico: " << s << std::endl;
}