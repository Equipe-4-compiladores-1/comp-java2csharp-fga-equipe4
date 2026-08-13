cmake_minimum_required(VERSION 3.12)
project(java2csharp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Diretórios de include
include_directories(include ${CMAKE_CURRENT_BINARY_DIR})

# Gerar Parser e Lexer
BISON_TARGET(Parser grammar/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp)
FLEX_TARGET(Lexer grammar/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Fontes do projeto
set(SOURCES
        src/main.cpp
        src/codegen.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS}
)

add_executable(java2csharp ${SOURCES})