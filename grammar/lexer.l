%{
#include "ast.h"
#include "parser.tab.hpp"
#include <cstdlib>
%}

%option noyywrap
%option yylineno

%%

[ \t\r\n]+          ; // Ignora espaços em branco

"class"             { return CLASS;}
"int"               { yylval.sval = strdup(yytext); return TYPE_INT; }
"double"            { yylval.sval = strdup(yytext); return TYPE_DOUBLE; } 
"float"             { yylval.sval = strdup(yytext); return TYPE_FLOAT; }  
"char"              { yylval.sval = strdup(yytext); return TYPE_CHAR; }  
"long"              { yylval.sval = strdup(yytext); return TYPE_LONG; }
"boolean"           { yylval.sval = strdup(yytext); return TYPE_BOOL; }
"void"              { yylval.sval = strdup(yytext); return TYPE_VOID; }
"return"            { return RETURN; }
"public"            { return PUBLIC; }
"static"            { return STATIC; }
"String"            { return TYPE_STRING; }
"System.out.println" { return PRINTLN; }
"System.out.print"   { return PRINT; }
"System.out.printf" { return PRINTF; }
","                 { return ','; }
\"[^"]*\"           { yylval.sval = strdup(yytext); return STRING_LITERAL; }

[0-9]+              { yylval.sval = strdup(yytext); return INT_LITERAL; }
[0-9]+\.[0-9]+      { yylval.sval = strdup(yytext); return FLOAT_LITERAL; } 
\'[^']\'            { yylval.sval = strdup(yytext); return CHAR_LITERAL; }  
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

.                   { return yytext[0]; }

%%