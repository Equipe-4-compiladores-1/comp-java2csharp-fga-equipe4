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
        src/symbol_table.cpp
        src/semantic_analyzer.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS}
)

add_executable(java2csharp ${SOURCES})
# Configuração de testes
enable_testing()
file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/input/*.java")
foreach(INPUT_FILE IN LISTS TEST_FILES)
get_filename_component(TEST_NAME ${INPUT_FILE} NAME_WE)
add_test(
        NAME "Compila_${TEST_NAME}"
        COMMAND java2csharp ${INPUT_FILE}
)
add_test(
        NAME "Valida_${TEST_NAME}"
        COMMAND diff -u --strip-trailing-cr
                Saida.cs 
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/${TEST_NAME}_expected.cs
)
    
    # Garante que a validação só ocorra se a compilação não der crash
    set_tests_properties("Valida_${TEST_NAME}" PROPERTIES DEPENDS "Compila_${TEST_NAME}")
endforeach()
# Fim  da configuração de testes
# Configuração do relatório de cobertura de teste
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
# Gerar relatório de cobertura de teste no terminal
add_custom_target(coverage
    COMMAND mkdir -p coverage_report
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --filter "\".*/src/.*\"" --filter "\".*/include/.*\"" -e ".*/usr/.*"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Gerando relatorio de cobertura resumido no terminal..."
)

# Gerar Html de cobertura de teste
add_custom_target(coverage_html
    COMMAND mkdir -p coverage_report
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --filter "\".*/src/.*\"" --filter "\".*/include/.*\"" -e ".*/usr/.*" --html --html-details -o coverage_report/index.html
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Gerando relatorio de cobertura visual em HTML..."
)
# Fim da Configuração do relatório de cobertura de teste