/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MNT_C_USERS_MARCO_DOCUMENTS_UNB_COMP_JAVA2CSHARP_FGA_EQUIPE4_BUILD_WSL_PARSER_TAB_HPP_INCLUDED
# define YY_YY_MNT_C_USERS_MARCO_DOCUMENTS_UNB_COMP_JAVA2CSHARP_FGA_EQUIPE4_BUILD_WSL_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE_INT = 259,                /* TYPE_INT  */
    TYPE_BOOL = 260,               /* TYPE_BOOL  */
    TYPE_VOID = 261,               /* TYPE_VOID  */
    INT_LITERAL = 262,             /* INT_LITERAL  */
    RETURN = 263,                  /* RETURN  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    TRUE = 266,                    /* TRUE  */
    FALSE = 267,                   /* FALSE  */
    EQ = 268,                      /* EQ  */
    NE = 269,                      /* NE  */
    LT = 270,                      /* LT  */
    LE = 271,                      /* LE  */
    GT = 272,                      /* GT  */
    GE = 273,                      /* GE  */
    CLASS = 274,                   /* CLASS  */
    PUBLIC = 275,                  /* PUBLIC  */
    STATIC = 276,                  /* STATIC  */
    TYPE_STRING = 277,             /* TYPE_STRING  */
    PRINT = 278,                   /* PRINT  */
    PRINTLN = 279,                 /* PRINTLN  */
    PRINTF = 280,                  /* PRINTF  */
    STRING_LITERAL = 281,          /* STRING_LITERAL  */
    TYPE_DOUBLE = 282,             /* TYPE_DOUBLE  */
    TYPE_FLOAT = 283,              /* TYPE_FLOAT  */
    TYPE_CHAR = 284,               /* TYPE_CHAR  */
    TYPE_LONG = 285,               /* TYPE_LONG  */
    FLOAT_LITERAL = 286,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 287             /* CHAR_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "grammar/parser.y"

    char* sval;
    ASTNode* node;
    StmtNode* stmt;
    ExprNode* expr;
    Param* param;
    std::vector<Param>* param_list;
    std::vector<std::shared_ptr<StmtNode>>* stmt_list;
    std::vector<std::shared_ptr<ExprNode>>* expr_list;

#line 107 "/mnt/c/Users/marco/Documents/UNB/comp-java2csharp-fga-equipe4/build-wsl/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MNT_C_USERS_MARCO_DOCUMENTS_UNB_COMP_JAVA2CSHARP_FGA_EQUIPE4_BUILD_WSL_PARSER_TAB_HPP_INCLUDED  */
