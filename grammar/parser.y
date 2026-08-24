%{
#include "ast.h"
#include <iostream>
#include <vector>
#include <memory>

extern int yylex();
void yyerror(const char* s);

std::vector<std::shared_ptr<FunctionDeclNode>> programFunctions;
std::shared_ptr<ClassDeclNode> rootNode;
%}

%union {
    char* sval;
    ASTNode* node;
    StmtNode* stmt;
    ExprNode* expr;
    std::vector<std::shared_ptr<StmtNode>>* stmt_list;
    std::vector<std::shared_ptr<ExprNode>>* expr_list;
}

%token <sval> IDENTIFIER TYPE_INT TYPE_BOOL TYPE_VOID INT_LITERAL
%token RETURN
%token CLASS
%token PUBLIC STATIC TYPE_STRING
%token PRINT PRINTLN PRINTF
%token <sval> STRING_LITERAL

%type <stmt> var_decl stmt
%type <expr> expr
%type <stmt_list> stmt_list
%type <sval> type_specifier

%left '+' '-'
%left '*' '/'

%%

program:
    class_decl
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
    | PUBLIC STATIC TYPE_VOID IDENTIFIER '(' TYPE_STRING '[' ']' IDENTIFIER ')' '{' stmt_list '}' {
        /* $3 é o TYPE_VOID, $4 é o nome da função (main) */
        auto func = std::make_shared<FunctionDeclNode>($<sval>3, $<sval>4);
        
        /* $12 é a stmt_list (o corpo do método) */
        func->body = *($<stmt_list>12);
        delete $<stmt_list>12;
        programFunctions.push_back(func);
    }
    ;
class_decl:
    CLASS IDENTIFIER '{' function_list '}' {
        auto classNode = std::make_shared<ClassDeclNode>($2);
        classNode->functions = programFunctions;
        programFunctions.clear();
        rootNode = classNode;
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
    | PRINT '(' expr ')' ';' { $$ = new PrintStmtNode(std::shared_ptr<ExprNode>($3), false); }
    | PRINTLN '(' expr ')' ';' { $$ = new PrintStmtNode(std::shared_ptr<ExprNode>($3), true); }
    | PRINTF '(' STRING_LITERAL ',' expr ')' ';' { 
        // 1. Criamos a lista que o nó espera
        std::vector<std::shared_ptr<ExprNode>> args;
        
        // 2. Adicionamos a string (convertendo para StringNode)
        args.push_back(std::make_shared<StringNode>($3));
        
        // 3. Adicionamos a variável/conta
        args.push_back(std::shared_ptr<ExprNode>($5));
        
        // 4. Passamos a lista pronta para o PrintfStmtNode
        $$ = new PrintfStmtNode(args); 
    }
    ;

var_decl:
    type_specifier IDENTIFIER '=' expr {
        $$ = new VarDeclNode($1, $2, std::shared_ptr<ExprNode>($4));
    }
    ;



expr:
    INT_LITERAL { $$ = new LiteralNode($1); }
    | STRING_LITERAL { $$ = new StringNode($1); } // <-- Agora suporta Strings
    | IDENTIFIER { 
        // <-- AGORA SUPORTA LER VARIÁVEIS NA MATEMÁTICA E NO PRINT!
        $$ = new LiteralNode($1); // (Reutilizando o LiteralNode para facilitar)
    }
    | expr '+' expr { $$ = new BinaryExprNode("+", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '-' expr { $$ = new BinaryExprNode("-", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '*' expr { $$ = new BinaryExprNode("*", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    | expr '/' expr { $$ = new BinaryExprNode("/", std::shared_ptr<ExprNode>($1), std::shared_ptr<ExprNode>($3)); }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Erro sintatico: " << s << std::endl;
}