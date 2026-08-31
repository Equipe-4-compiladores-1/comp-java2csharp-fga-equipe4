# Transpilador Java para C# (Subconjunto Procedural)

Projeto desenvolvido para a disciplina de **Compiladores 1**. Trata-se de um transpilador da linguagem **Java** (focado no paradigma imperativo/procedural) para **C#**, utilizando **Flex**, **Bison** e **C++**.

---

## Arquitetura

O fluxo de compilação/transpilação é estruturado em etapas desacopladas:

1. **Análise Léxica (Flex):** Converte o código fonte `.java` em um fluxo de tokens.
2. **Análise Sintática (Bison):** Valida a sintaxe e constrói a Árvore de Sintaxe Abstrata (AST).
3. **Representação Intermediária (AST):** Estrutura hierárquica em C++ representando comandos, expressões e funções.
4. **Geração de Código (C++ / Visitor):** Percorre a AST gerando o código em C# equivalente (envelopando funções em uma classe estática wrapper).

---

## Estrutura do Repositório

```text
.
├── CMakeLists.txt            # Automação de build (Flex + Bison + C++)
├── grammar/                  # Especificações das gramáticas
│   ├── lexer.l               # Regras do analisador léxico (Flex)
│   └── parser.y              # Regras sintáticas e construção da AST (Bison)
├── include/                  # Cabeçalhos C++ (.h / .hpp)
│   ├── ast.h                 # Definição dos nós da AST
│   ├── codegen.h             # Emissor de código C# (Visitor)
│   └── symbol_table.h        # Tabela de símbolos e escopos
├── src/                      # Implementação dos módulos em C++
│   ├── ast.cpp
│   ├── codegen.cpp
│   ├── symbol_table.cpp
│   └── main.cpp              # Ponto de entrada (CLI)
└── tests/                    # Suíte de testes
    ├── input/                # Arquivos Java imperativos de entrada
    └── expected/             # Código C# esperado de saída

```

---

## Pré-requisitos

Para compilar e executar o projeto, você precisará de:

* **GCC / Clang** (com suporte a C++17 ou superior)
* **Flex** (v2.6+)
* **Bison** (v3.0+)
* **CMake** (v3.12+)

---

## Como Compilar e Executar

1. **Criar diretório de build:**
```bash
mkdir build && cd build
```


2. **Gerar os arquivos de compilação com CMake:**
```bash
cmake ..
make
```



3. **Executar o transpilador:**
```bash
./java2csharp ../tests/input/exemplo.java -o saida.cs
```

## Como executar os testes
Para executat os testes basta apenas rodar o seguinte comando na pasta build, após ter compilado e executado
```
make test
```
## Como gerar Relatorio de Cobertura

1. **Instalar o gcovr**
```
sudo apt update && sudo apt install gcovr
```

2. ** Executar um dos dois comandos para gerar o relatorio **

Gerar no Terminal

```
make coverage
```

Gerar um HTML

```
make coverage_html
```
