%{
#include "ast.h"
#include "parser.tab.hpp"
#include <cstdlib>
%}

%option noyywrap

%%

[ \t\r\n]+          ; // Ignora espaços em branco

"class"             { return CLASS;}
"int"               { yylval.sval = strdup(yytext); return TYPE_INT; }
"boolean"           { yylval.sval = strdup(yytext); return TYPE_BOOL; }
"void"              { yylval.sval = strdup(yytext); return TYPE_VOID; }
"return"            { return RETURN; }
"public"            { return PUBLIC; }
"static"            { return STATIC; }
"String"            { return TYPE_STRING; }

[0-9]+              { yylval.sval = strdup(yytext); return INT_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENTIFIER; }

"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"="                 { return '='; }
";"                 { return ';'; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
"["                 { return '['; }
"]"                 { return ']'; }

.                   { printf("Caractere desconhecido: %s\n", yytext); }

%%