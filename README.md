# ⚙️ Manipulação de Bits em C (Bitwise Operations & Bit Fields)

Este projeto demonstra duas abordagens principais para **acessar, extrair e interpretar bits** dentro de um único byte (`uint8_t`) na linguagem C:

1.  **Operações Bitwise (Low-Level):** Uso dos operadores `&` (AND), `|` (OR), `^` (XOR), `~` (NOT) e `<<`, `>>` (Shift) para manipular bits diretamente.
    
2.  **Campos de Bits (Bit Fields):** Uso de estruturas (`struct`) para mapear bits individuais a nomes de variáveis, permitindo o acesso direto e legível.
    

## 🌟 O que o código demonstra

O arquivo `main.c` utiliza um **byte de status** fixo, `status_byte = 0b10110010` (Decimal 178), para demonstrar como extrair e interpretar cada um dos seus 8 bits, onde cada bit representa uma característica ou _flag_.

### Byte de Status: `0b10110010` (178)

```
+-------------------+---------+-------+-------+-------+-------+-------+-------+---------+
| Posição (Bit Index) | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0   |
|                   | (MSB)   |       |       |       |       |       |       | (LSB)   |
+-------------------+---------+-------+-------+-------+-------+-------+-------+---------+
| Característica    | Pronto  | Erro  | Bloq  | Vali  | Conf  | Ativo | Carr  | Disp    |
+-------------------+---------+-------+-------+-------+-------+-------+-------+---------+
| Valor             | 1       | 0     | 1     | 1     | 0     | 0     | 1     | 0       |
+-------------------+---------+-------+-------+-------+-------+-------+-------+---------+

```

----------

## 🛠️ Detalhes da Implementação

### 1. Campo de Bits (`Caracteristicas`)

A estrutura `Caracteristicas` é definida para sobrepor o `status_byte`, garantindo um mapeamento legível:

C

```
typedef struct {
    uint8_t disponivel : 1; // LSB (Bit 0) - Disponibilidade - ocupa 1 bit -> : 1
    uint8_t carregado   : 1; // Bit 1 - Item carregado - ocupa 1 bit -> : 1
    uint8_t ativo      : 1; // Bit 2 - Estado ativo
    uint8_t configurado  : 1; // Bit 3 - Configuração feita
    uint8_t validado   : 1; // Bit 4 - Dado validado
    uint8_t bloqueado  : 1; // Bit 5 - Acesso bloqueado
    uint8_t erro       : 1; // Bit 6 - Estado de erro
    uint8_t pronto     : 1; // MSB (Bit 7) - Item pronto
} __attribute__((packed)) Caracteristicas;

```

-   O especificador `: 1` define que cada membro da estrutura ocupa **apenas 1 bit** de memória.
    
-   A diretiva `__attribute__((packed))` é usada para garantir que a estrutura ocupe o mínimo de espaço (exatamente 1 byte), prevenindo o _padding_ (preenchimento) da estrutura pelo compilador.
    
-   **Observação de Ordem de Bits:** A ordem real dos bits dentro do byte (da esquerda para a direita ou da direita para a esquerda) depende da **arquitetura** (Endianness) e das regras do **compilador** (que geralmente mapeia do LSB para o MSB, como visto no código).
    

### 2. Extração Bitwise (Manual)

O código demonstra a extração de bits usando a lógica de máscara e AND bitwise:

#### Função Genérica

A função `extrai_bit_generico(uint8_t byte, int n)` encapsula a técnica mais comum para extrair o valor de um bit na posição `n` (onde 0 <= n <= 7):

`Retorno = (byte & (1 << n)) != 0`

-   **Passo 1: Máscara (`(1 << n)`)** - Cria uma máscara onde apenas o bit na posição $n$ é 1.
    
    -   Exemplo: Para Bit 5, 1 << 5 resulta em `0b00100000`.
        
-   **Passo 2: AND Bitwise (`&`)** - Aplica a máscara ao byte para isolar o bit. Se o bit original era 1, o resultado será não-zero. Se era 0, o resultado será zero.
    

----------

## 💻 Saída Esperada

A execução do `main.c` produzirá resultados que confirmam a interpretação binária do `status_byte` (`10110010`).

```
Demonstração de Manipulação de Bits em C
==========================================
Byte de Status (Decimal): 178
Byte de Status (Binário): 10110010

--- Extração com Campo de Bits (Bit Field) ---
Campo de Bits (Ordem LSB -> MSB):
  Disponível (Bit 0 - LSB): 0 // status_byte[0]
  Carregado  (Bit 1):      1 // status_byte[1]
  Ativo      (Bit 2):      0
  Configurado(Bit 3):      0
  Validado   (Bit 4):      1
  Bloqueado  (Bit 5):      1
  Erro       (Bit 6):      0
  Pronto     (Bit 7 - MSB):1 // status_byte[7]

--- Extração Manual: LSB -> MSB (Bit 0 para Bit 7) ---
Bit 0 (LSB -> MSB): 0
Bit 1 (LSB -> MSB): 1
// ... (outros bits)
Bit 7 (LSB -> MSB): 1

--- Extração com Função Genérica (extrai_bit_generico) ---
Acesso ao Bit 7 (MSB - Pronto):     1
Acesso ao Bit 6 (Erro):             0
Acesso ao Bit 1 (Carregado):        1
Acesso ao Bit 0 (LSB - Disponível): 0

```

----------

## 🚀 Como Compilar e Rodar

### Pré-requisitos

-   Um compilador C (como GCC, Clang, etc.)
    

### Passos

1.  **Salve o código:** Salve o conteúdo do código no arquivo `main.c`.
    
2.  **Compile usando GCC:**
    
    Bash
    
    ```
    gcc main.c -o bitwise_demo
    
    ```
    
3.  **Execute:**
    
    Bash
    
    ```
    ./bitwise_demo
    ```
