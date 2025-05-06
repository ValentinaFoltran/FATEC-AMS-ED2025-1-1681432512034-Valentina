/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: << Bubblesort >>                                           */
/*                                                                                  */
/*                                    Autores:  Valentina Foltran Carvalho          */
/*                                                                                  */
/*                                                                                  */
/*                                                                  Data:06/05/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Função para verificar se a string representa um número válido (permitindo números negativos)
int numeroValido(char entrada[]) {
    int i = 0;
    if (entrada[0] == '-') {
        i = 1;
    }
    for (; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para verificar se a string representa um inteiro positivo
int inteiroPositivo(char entrada[]) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0;
        }
    }
    int valor = atoi(entrada);
    return valor > 0;
}

// Função para ler e validar a quantidade de números
int obterQuantidadeNumeros() {
    char entrada[100];
    int qtdeNumeros;

    while (1) {
        printf("Quantos números deseja ordenar? ");
        scanf("%s", entrada);

        if (inteiroPositivo(entrada)) {
            qtdeNumeros = atoi(entrada);
            return qtdeNumeros;
        } else {
            printf("Entrada inválida. Digite apenas um número inteiro positivo.\n");
        }
    }
}

// Função para ler os números e validar a entrada
void lerNumeros(int* numeros, int qtdeNumeros) {
    char entrada[100];
    for (int i = 0; i < qtdeNumeros; i++) {
        while (1) {
            printf("Digite o número %d: ", i + 1);
            scanf("%s", entrada);

            if (numeroValido(entrada)) {
                numeros[i] = atoi(entrada);
                break;
            } else {
                printf("Entrada inválida. Digite apenas números inteiros (ex: -3, 0, 25).\n");
            }
        }
    }
}

// Função para aplicar o algoritmo Bubble Sort
void bubbleSort(int* numeros, int qtdeNumeros) {
    int aux;
    for (int i = 0; i < qtdeNumeros - 1; i++) {
        for (int j = 0; j < qtdeNumeros - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                aux = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = aux;
            }
        }
    }
}

// Função para exibir os números ordenados
void exibirNumeros(int* numeros, int qtdeNumeros) {
    printf("\nNúmeros em ordem crescente:\n");
    for (int i = 0; i < qtdeNumeros; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");
}

// Função principal
int main() {
    char continuar[10];

    do {
        // Solicitar a quantidade de números a serem ordenados
        int qtdeNumeros = obterQuantidadeNumeros();

        // Alocar dinamicamente o vetor de números
        int* numeros = (int*)malloc(qtdeNumeros * sizeof(int));
        
        if (numeros == NULL) {
            printf("Falha na alocação de memória.\n");
            return 1;
        }

        // Ler e validar os números
        lerNumeros(numeros, qtdeNumeros);

        // Ordenar os números
        bubbleSort(numeros, qtdeNumeros);

        // Exibir os números ordenados
        exibirNumeros(numeros, qtdeNumeros);

        // Perguntar se deseja continuar
        printf("\nDeseja ordenar outro conjunto de números? (s/n): ");
        scanf("%s", continuar);

        // Liberar a memória alocada
        free(numeros);

    } while (continuar[0] == 's' || continuar[0] == 'S');

    printf("Programa encerrado.\n");
    return 0;
}
