# Transpilador Java :material-arrow-right: C&#35;

<p align="left">
  <img src="https://img.shields.io/badge/Linguagem-C%2B%2B17-blue.svg" />
  <img src="https://img.shields.io/badge/Tools-Flex%20%7C%20Bison-orange.svg" />
  <img src="https://img.shields.io/badge/Build-CMake-green.svg" />
  <img src="https://img.shields.io/badge/Disciplina-Compiladores%201-purple.svg" />
</p>

O **Java2CSharp** é um transpilador desenvolvido para converter um subconjunto **procedural/imperativo** da linguagem **Java** diretamente para código **C#** válido e executável.

!!! info "Projeto Acadêmico"
Este projeto foi construído para a disciplina de **Compiladores 1**. O foco é aplicar os conceitos de análise léxica, análise sintática, construção de AST e padrão Visitor para geração de código.

---

## :material-bullseye: Objetivos do Projeto

<div class="grid cards" markdown>

-   :material-swap-horizontal: **Tradução Procedural**

    ---

    Mapeamento direto de variáveis, tipos primitivos, expressões aritméticas/lógicas e funções.

-   :material-cube-outline: **Encapsulamento C#**

    ---

    Geração automática de uma classe wrapper estática (`public static class Program`) para adaptar funções Java ao C#.

-   :material-sitemap: **AST Robusta**

    ---

    Estrutura de dados em C++ baseada em **Visitor Pattern**, mantendo o parsing totalmente desacoplado da geração de código.

</div>

---

## :material-code-json: Exemplo de Transpilação

Veja abaixo a conversão que o compilador realiza:

=== "Java (Entrada)"
```java
class Program {
    public static void main(String[] args) {
        int resultado = somar(10, 20);
    }
    
    int somar(int a, int b) {
        return a + b;
    }      
}
```
=== "C# (Saída Gerada)"

```csharp
using System;

    namespace TranspiledProgram {
        public static class Program {
            public static void Main() {
                int resultado = somar(10, 20);
            }

            public static int somar(int a, int b) {
                return (a + b);
            }
        }
    }
```

---

## :material-rocket-launch: Próximos Passos

??? tip "Como testar localmente?"
Consulte nosso **[Guia de Compilação](guia-de-uso.md)** para aprender a compilar o projeto com o CMake e rodar os testes automatizados.

---