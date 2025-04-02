/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: << Manipulação de Pilha - Implementado HP12c >>            */
/*                                                                                  */
/*                                  Autor: Valentina Foltran Carvalho               */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 4

typedef struct {
    double valores[MAX];
    char expressoes[MAX][50];
    int top;  
} Pilha;

Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    p->top = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->top == -1;
}

int cheia(Pilha* p) {
    return p->top == MAX - 1;
}

void push(Pilha* p, double valor, const char* expr) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->top++;
    p->valores[p->top] = valor;
    strcpy(p->expressoes[p->top], expr);
}

double pop(Pilha* p, char* expr) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, p->expressoes[p->top]);
    return p->valores[p->top--];
}

void calcularRPN(char* expressao) {
    Pilha* pilha = criarPilha();
    char expressaoOriginal[100];
    strcpy(expressaoOriginal, expressao);
    
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token);
            char temp[20];
            sprintf(temp, "%.2f", num);
            push(pilha, num, temp);
        } else {
            if (pilha->top < 1) {
                printf("Erro: Expressão inválida!\n");
                free(pilha);
                return;
            }
            char exprA[50], exprB[50];
            double X = pop(pilha, exprB);
            double Y = pop(pilha, exprA);
            double resultado;
            char operador = token[0];
            char novaExpr[150];
            
            switch (operador) {
                case '+': resultado = Y + X; break;
                case '-': resultado = Y - X; break;
                case '*': resultado = Y * X; break;
                case '/':
                    if (X == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(pilha);
                        return;
                    }
                    resultado = Y / X;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(pilha);
                    return;
            }
            
            snprintf(novaExpr, sizeof(novaExpr), "(%s %c %s)", exprA, operador, exprB);
            push(pilha, resultado, novaExpr);
        }
        token = strtok(NULL, " ");
    }
    
    if (pilha->top != 0) {
        printf("Erro: Expressão inválida!\n");
        free(pilha);
        return;
    }
    
    char resultadoExpr[100];
    double resultadoFinal = pop(pilha, resultadoExpr);
    
    printf("---------------------------------------------\n");
    printf("Expressão RPN: %s\n", expressaoOriginal);
    printf("Expressão algébrica: %s\n", resultadoExpr);
    printf("Resultado: %.2f\n", resultadoFinal);
    
    free(pilha);
}

int main() {
    Pilha* pilha = criarPilha();
    char expressao[100];
    int opcao;
    
    while (1) {
        printf("\nCalculadora RPN - \n\n");
        printf("Menu: \n");
        printf("1 - Calcular expressão RPN \n");
        printf("2 - Sair \n");
        printf("Digite uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada inválida! Tente novamente.\n");
            while(getchar() != '\n');
            continue;
        }
        
        getchar();
        
        switch (opcao) {
            case 1:
                printf("\nDigite a expressão em RPN: ");
                fgets(expressao, sizeof(expressao), stdin);
                expressao[strcspn(expressao, "\n")] = 0;  
                calcularRPN(expressao);
                break;
            
            case 2:
                free(pilha);
                return 0;
            
            default:
                printf("\nOpção inválida!\n");
        }
    }
}
