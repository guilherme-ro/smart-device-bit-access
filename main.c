#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Definição de um Campo de Bits (Bit Field)
// mapeia 8 características específicas em um único byte (uint8_t)
// Cada campo é de 1 bit (1 ou 0)
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
// A diretiva __attribute__((packed)) garante que a estrutura use 
// o mínimo de bytes possível, neste caso, exatamente 1 byte (8 bits).

// -------------------------------------------------------------------

// Variável global que armazena o byte (característica)
// O valor 0b10110010 em binário (ou 178 em decimal) será usado para demonstração.
// Binário: |Pronto|Erro|Bloq|Vali|Conf|Ativo|Carr|Disp|
// Valor:   |  1   | 0  | 1  | 1  | 0  | 0   | 1  | 0  |
uint8_t status_byte = 0b10110010; 
// 0b10110010 = 1 * 128 + 0 * 64 + 1 * 32 + 1 * 16 + 0 * 8 + 0 * 4 + 1 * 2 + 0 * 1 = 178

// -------------------------------------------------------------------

/**
 * @brief Função que extrai o valor de um bit específico de um byte.
 * * @param byte - O byte de onde o bit será extraído.
 * @param n - O índice do bit (0 a 7), independente de MSB ou LSB.
 * @return true (1) se o bit estiver setado, false (0) caso contrário.
 */
bool extrai_bit_generico(uint8_t byte, int n) {
    // Para extrair o bit 'n':
    // 1. O operador de 'shift' para a esquerda (<<) para criar uma MÁSCARA
    //    onde apenas o bit na posição 'n' é 1. Ex: n=2 -> 0b00000100
    // 2. O operador bitwise E (&) para isolar o bit.
    // 3. a operação (byte & (1 << n)) != 0; para converter o resultado em um valor booleano (0 ou 1).
    return (byte & (1 << n)) != 0; // se o resultado for zero, retorna false. se res for diferente de zero, retorna true
    //return !!(byte & (1 << n)); mesmo resultado !!0 -> !(1) -> 0 // !!X -> !(0) -> 1
}

// -------------------------------------------------------------------

int main() {
    printf("Demonstração de Manipulação de Bits em C\n");
    printf("==========================================\n");
    printf("Byte de Status (Decimal): %d\n", status_byte);
    printf("Byte de Status (Binário): 10110010\n");

    // Acesso usando a estrutura de Campo de Bits (Bit Field)
    printf("\n--- Extração com Campo de Bits (Bit Field) ---\n");
    Caracteristicas *c = (Caracteristicas *)&status_byte;
    
    // Observação: A ordem dos bits na estrutura é definida pela 
    // especificação do compilador (geralmente LSB para MSB).
    printf("Campo de Bits (Ordem LSB -> MSB):\n");
    printf("  Disponível (Bit 0 - LSB): %d\n", c->disponivel);
    printf("  Carregado  (Bit 1):      %d\n", c->carregado);
    printf("  Ativo      (Bit 2):      %d\n", c->ativo);
    printf("  Configurado(Bit 3):      %d\n", c->configurado);
    printf("  Validado   (Bit 4):      %d\n", c->validado);
    printf("  Bloqueado  (Bit 5):      %d\n", c->bloqueado);
    printf("  Erro       (Bit 6):      %d\n", c->erro);
    printf("  Pronto     (Bit 7 - MSB):%d\n", c->pronto);

    // Acesso e Extração Manual (Low-Level)
    // Extração da Direita para a Esquerda (LSB -> MSB)
    printf("\n--- Extração Manual: LSB -> MSB (Bit 0 para Bit 7) ---\n");
    for (int i = 0; i < 8; i++) {
        // Máscara: Cria um 1 na posição 'i'. Ex: i=2 -> 0b00000100
        uint8_t mascara = 1 << i;
        
        // Operação Bitwise AND (&): Testa se o bit 'i' está setado no byte.
        // Se (status_byte & mascara) for diferente de zero, o bit está setado.
        uint8_t valor = (status_byte & mascara) != 0;
        
        printf("Bit %d (LSB -> MSB): %d\n", i, valor);
    }

    // Extração da Esquerda para a Direita (MSB -> LSB)
    printf("\n--- Extração Manual: MSB -> LSB (Bit 7 para Bit 0) ---\n");
    for (int i = 7; i >= 0; i--) {
        // cria máscara: 1 << i. Ex: i=7 -> 0b10000000
        uint8_t mascara = 1 << i;
        
        // Operação Bitwise AND (&): Isola o valor do bit na posição 'i'
        // (o resultado será 0 ou 2^i).
        uint8_t bit_isolado = status_byte & mascara;
        
        // Operação SHIFT para a Direita (>>): Move o bit isolado para a 
        // posição do LSB (Bit 0) para obter o valor 0 ou 1.
        uint8_t valor = bit_isolado >> i; 

        printf("Bit %d (MSB -> LSB): %d\n", i, valor);
    }
    
    // Acesso com a Função Genérica
    printf("\n--- Extração com Função Genérica (extrai_bit_generico) ---\n");
    // Essa função encapsula a lógica de extração LSB -> MSB
    printf("Acesso ao Bit 7 (MSB - Pronto):     %d\n", extrai_bit_generico(status_byte, 7)); // Deve ser 1
    printf("Acesso ao Bit 6 (Erro):             %d\n", extrai_bit_generico(status_byte, 6)); // Deve ser 0
    printf("Acesso ao Bit 1 (Carregado):        %d\n", extrai_bit_generico(status_byte, 1)); // Deve ser 1
    printf("Acesso ao Bit 0 (LSB - Disponível): %d\n", extrai_bit_generico(status_byte, 0)); // Deve ser 0

    return 0;
}
