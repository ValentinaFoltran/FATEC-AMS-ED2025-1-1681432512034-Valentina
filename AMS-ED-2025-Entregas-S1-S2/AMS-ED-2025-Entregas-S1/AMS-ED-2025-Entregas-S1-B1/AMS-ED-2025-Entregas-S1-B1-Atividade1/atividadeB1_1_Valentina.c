#include <stdio.h>

// Função para aplicar o desconto em porcentagem
void aplicarDesconto(float *preco, float desconto) {
    *preco -= (*preco * desconto / 100); // Aplica o desconto percentual
}

int main() {
    float precoOriginal, desconto, precoFinal;
    
    printf("Loja de produtos eletrônicos - Obtenha descontos em seus produtos!\n\n");

    // Solicita o preço do produto
    printf("Digite o preço do produto: R$ ");
    scanf("%f", &precoOriginal);

    // Solicita o valor do desconto em %
    printf("Digite o valor do desconto (%%): ");
    scanf("%f", &desconto);

    // Inicializa precoFinal com o valor do precoOriginal para mostrar no final
    precoFinal = precoOriginal;

    // Aplica o desconto usando a função
    aplicarDesconto(&precoFinal, desconto);

    // Exibe os resultados
    printf("\nPreço original: R$ %.2f\n", precoOriginal);
    printf("Desconto aplicado: %.2f%%\n", desconto);
    printf("Preço final após desconto: R$ %.2f\n", precoFinal);

    return 0;
}