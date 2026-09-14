# Roadmap e Implementações Futuras

Para tornar o transpilador mais robusto e completo, o planejamento de evolução do **Java2CSharp** contempla as seguintes etapas e estruturas para as próximas sprints:

## :material-clock-outline: Próximas Funcionalidades Planejadas

### 1. Estruturas de Controle de Fluxo (`if / else`)
* **Objetivo:** Permitir desvios condicionais básicos na tradução.
* **Gramática Alvo:**
    ```java
    if (condicao) { ... } else { ... }
    ```


* **Impacto na AST:** Criação dos nós `IfElseStmtNode` contendo sub-árvores para a condição, o bloco `then` e o bloco `else`.

### 2. Laços de Repetição (`while`)

* **Objetivo:** Adicionar suporte a loops iterativos condicionais.
* **Gramática Alvo:**
    ```java
    while (condicao) { ... }
    ```

* **Impacto na AST:** Criação do nó `WhileStmtNode` no `ast.h` e mapeamento correspondente no codegen para a estrutura `while` nativa do C#.

### 3. Tratamento de Escopo e Checagem Semântica

* **Objetivo:** Implementar uma tabela de símbolos prévia à geração de código para validar a existência de variáveis, compatibilidade de tipos e retorno de funções antes da conversão para C#.

---

### Planejamento de Sprints (Backlog)


| Sprint | Foco Principal | Entregas / Issues Alvo |
| --- | --- | --- |
| **Sprint 1 (Concluída)** | **Fundação e Funções** | • Configuração da AST e padrão Visitor |
• Suporte a tipos primitivos e variáveis
• Suporte a chamadas de funções e métodos estáticos (`#1`) |
| **Sprint 2** | **Controle de Fluxo** | • Implementação de blocos condicionais (`if/else`) |
• Implementação de laços de repetição (`while`)
• Ajustes na precedência lógica de expressões |
| **Sprint 3** | **Análise Semântica** | • Criação da Tabela de Símbolos |
• Validação de tipos na atribuição
• Verificação de retorno obrigatório em funções não-void |
| **Sprint 4** | **Refinamento e Testes** | • Ampliação da suíte de testes de integração |
• Documentação final de arquitetura e casos de borda
• Empacotamento final |

---