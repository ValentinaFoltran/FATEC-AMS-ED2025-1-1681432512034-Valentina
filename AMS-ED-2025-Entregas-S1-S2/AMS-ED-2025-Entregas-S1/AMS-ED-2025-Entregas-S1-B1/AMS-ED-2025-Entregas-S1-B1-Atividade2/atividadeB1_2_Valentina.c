/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2.                                   */
/*             Objetivo: << Manipulação de array com ponteiro >>                    */
/*                                                                                  */
/*                                  Autor: Valentina Foltran Carvalho               */
/*                                                                  Data:11/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

// Estrutura para armazenar os dados de cada candidato
struct Candidato {
    char nome[100];
    float PE[4], AC[5], PP[10], EB[3];
    float nota_final;
    struct Candidato *prox;  // Ponteiro para o próximo candidato
};

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para validar e inserir notas
void inserir_notas(float *notas, int tamanho, const char *descricao) {
    printf("\nDigite as %d notas para %s (valores entre 0.0 e 10.0):\n", tamanho, descricao);

    for (int i = 0; i < tamanho; i++) {
        int resultado;
        do {
            printf("Nota %d: ", i + 1);
            resultado = scanf("%f", &notas[i]);

            if (resultado != 1) {
                printf("Erro: Entrada inválida! Digite apenas números entre 0,0 e 10,0.\n");
                limpar_buffer();  
                continue;
            }

            if (notas[i] < 0.0 || notas[i] > 10.0) {
                printf("Erro: A nota deve estar entre 0,0 e 10,0. Tente novamente.\n");
            }

        } while (resultado != 1 || notas[i] < 0.0 || notas[i] > 10.0);

        limpar_buffer();  
    }
}

// Função para calcular a média central (excluindo a maior e menor nota)
float calcular_nota(float *notas, int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0.0;

    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }

    return (soma - maior - menor) / (tamanho - 2);
}

// Função para inserir os dados de um candidato
void inserir_candidato(struct Candidato **inicio) {
    struct Candidato *novoCandidato = (struct Candidato*)malloc(sizeof(struct Candidato));
    if (novoCandidato == NULL) {
        printf("Erro ao alocar memória para o candidato!\n");
        return;
    }

    printf("\nNome do candidato: ");
    scanf(" %[^\n]", novoCandidato->nome);  // Leitura do nome do candidato

    inserir_notas(novoCandidato->PE, 4, "Prova Escrita (PE)");
    inserir_notas(novoCandidato->AC, 5, "Análise Curricular (AC)");
    inserir_notas(novoCandidato->PP, 10, "Prova Prática (PP)");
    inserir_notas(novoCandidato->EB, 3, "Entrevista em Banca Avaliadora (EB)");

    // Cálculo da nota final com base nas médias
    float nota_PE = calcular_nota(novoCandidato->PE, 4);
    float nota_AC = calcular_nota(novoCandidato->AC, 5);
    float nota_PP = calcular_nota(novoCandidato->PP, 10);
    float nota_EB = calcular_nota(novoCandidato->EB, 3);

    novoCandidato->nota_final = (nota_PE * 0.3) + (nota_AC * 0.1) + (nota_PP * 0.4) + (nota_EB * 0.2);

    // Inserção do candidato no início da lista encadeada
    novoCandidato->prox = *inicio;
    *inicio = novoCandidato;
}

// Função para classificar os candidatos por nota final (Bubble Sort)
void classificar_candidatos(struct Candidato *inicio) {
    struct Candidato *i, *j;
    float tempNF;
    char tempNome[100];

    for (i = inicio; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (i->nota_final < j->nota_final) {
                tempNF = i->nota_final;
                i->nota_final = j->nota_final;
                j->nota_final = tempNF;

                strcpy(tempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, tempNome);
            }
        }
    }
}

// Função para exibir a classificação dos candidatos
void exibir_classificacao(struct Candidato *inicio) {
    struct Candidato *ptr = inicio;
    printf("\n--- Classificação Final ---\n");
    int i = 0;

    while (ptr != NULL && i < 5) {
        printf("%dº - %s | Nota Final: %.2f\n", i + 1, ptr->nome, ptr->nota_final);
        ptr = ptr->prox;
        i++;
    }
}

int main() {
    struct Candidato *inicio = NULL;
    int num_candidatos = 0;
    char continuar;

    printf("=== SISTEMA DE SELEÇÃO PARA RESIDÊNCIA MÉDICA ===\n");

    do {
        inserir_candidato(&inicio);
        num_candidatos++;

        if (num_candidatos >= MAX_CANDIDATOS) {
            printf("\nNúmero máximo de candidatos atingido!\n");
            break;
        }

        printf("\nDeseja inserir outro candidato? (digite 's' ou 'n'): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    if (num_candidatos > 0) {
        classificar_candidatos(inicio);
        exibir_classificacao(inicio);
    } else {
        printf("Nenhum candidato foi inserido.\n");
    }

    // Libera a memória alocada para os candidatos
    struct Candidato *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }

    return 0;
}

