# Guia de Compilação e Uso

Este guia apresenta o passo a passo para configurar o ambiente, compilar o transpilador e executar as suas primeiras conversões de Java para C#.

## :material-hammer-wrench: Pré-requisitos

Para compilar o projeto, você precisará de uma cadeia de ferramentas C++ padrão e dos geradores de analisadores léxicos e sintáticos. 

Certifique-se de ter os seguintes pacotes instalados no seu sistema:
* **GCC** (ou Clang) com suporte a C++17
* **CMake** (versão 3.10 ou superior)
* **Flex** (Lexer)
* **Bison** (Parser)

!!! tip "Dica de Instalação (Linux)"
    Em distribuições baseadas em Arch Linux, você pode garantir todas as dependências com um único comando:
    `sudo pacman -S base-devel cmake flex bison`

## :material-cogs: Como Compilar

O projeto utiliza o CMake para gerenciar o build de forma isolada (Out-of-source build). Execute os comandos abaixo na raiz do repositório:

```bash
# 1. Crie e acesse o diretório de build
mkdir build && cd build

# 2. Gere os arquivos de configuração do CMake
cmake ..

# 3. Compile o projeto
make
```

Após o término da compilação, o executável (ex: `java2csharp`) estará disponível dentro do diretório `build`.

## :material-play-circle: Como Executar

Para rodar o transpilador, basta passar o arquivo `.java` de origem como argumento para o executável.

```bash
./java2csharp ../tests/input/MeuPrograma.java
```

**Resultado Esperado:**
O programa fará a leitura, exibirá a árvore ou o código gerado no terminal e criará o arquivo de saída `Saida.cs` contendo o código transpilado. Caso haja algum erro léxico ou sintático, a execução será interrompida e o erro será apontado.
