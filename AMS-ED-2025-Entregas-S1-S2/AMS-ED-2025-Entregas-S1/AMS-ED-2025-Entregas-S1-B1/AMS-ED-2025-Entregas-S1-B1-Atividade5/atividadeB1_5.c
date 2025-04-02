/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-5                                 */
/*             Objetivo: << Transforma Lista Ligada em Pilha >>                     */
/*                                                                                  */
/*                                    Autores:  Pedro Viterbo Zacchi,               */
/*                                              Rafael Nicolas Campos,              */
/*                                              Valentina Foltran Carvalho,         */
/*                                              Victor Hugo Gonçalves,              */
/*                                              Vinicius da Silva Ramos             */
/*                                                                                  */
/*                                                                                  */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[100];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido *proximo;
} Pedido;

typedef struct Pilha {
    Pedido *topo;
} Pilha;

Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

Pedido* Top(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Erro: a pilha está vazia\n");
        return NULL;
    }
    return pilha->topo;
}

Pedido* criarPedido(int numero, char cliente[], char descricao[], int quantidade, char status[]) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    strcpy(novo->status, status);
    novo->proximo = NULL;
    return novo;
}

void push(Pilha *p, Pedido *novo) {
    novo->proximo = p->topo;
    p->topo = novo;
}

Pedido* buscarPedido(Pilha *p, int numero) {
    Pedido *aux = p->topo;
    while (aux != NULL) {
        if (aux->numero == numero) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

void atualizarStatus(Pilha *p, int numero, char novoStatus[]) {
    Pedido *pedido = buscarPedido(p, numero);
    if (pedido != NULL) {
        strcpy(pedido->status, novoStatus);
        printf("Status do pedido %d atualizado para: %s\n", numero, novoStatus);
    } else {
        printf("Pedido não encontrado!\n");
    }
}

void pop(Pilha *p) {
    if (p->topo == NULL) {
        printf("Pilha vazia!\n");
        return;
    }
    Pedido *removido = p->topo;
    p->topo = removido->proximo;
    printf("Pedido #%d removido com sucesso!\n", removido->numero);
    free(removido);
}

void listarPedidos(Pilha *p) {
    if (p->topo == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    Pedido *aux = p->topo;
    while (aux != NULL) {
        printf("Pedido #%d | Cliente: %s | Prato: %s | Qtd: %d | Status: %s\n", 
               aux->numero, aux->cliente, aux->descricao, aux->quantidade, aux->status);
        aux = aux->proximo;
    }
}

void liberarPilha(Pilha *p) {
    while (p->topo != NULL) {
        pop(p);
    }
    free(p);
}

void lerString(char *str, int tamanho) { 
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0'; 
}

void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

int lerInteiro(const char *mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limparBuffer(); 
            return valor;
        } else {
            printf("Entrada inválida! Digite um número válido.\n");
            limparBuffer(); 
        }
    }
}

void selecionarStatus(char *status) {
    int opcao;
    printf("Status do pedido:\n");
    printf("1 - Pendente\n");
    printf("2 - Em preparo\n");
    printf("3 - Pronto\n");
    printf("4 - Entregue\n");
    
    do {
        opcao = lerInteiro("Escolha uma opção (1-4): ");
    } while (opcao < 1 || opcao > 4);

    switch (opcao) {
        case 1: strcpy(status, "pendente"); break;
        case 2: strcpy(status, "em preparo"); break;
        case 3: strcpy(status, "pronto"); break;
        case 4: strcpy(status, "entregue"); break;
    }
}

int main() {
    Pilha *pilha = criarPilha();
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20];

    do {
        printf("\nSistema de Gerenciamento de Pedidos - Restaurante\n");
        printf("1 - Inserir Pedido\n");
        printf("2 - Buscar Pedido\n");
        printf("3 - Atualizar Status\n");
        printf("4 - Remover Pedido\n");
        printf("5 - Listar Pedidos\n");
        printf("6 - Exibir Topo da Pilha\n");
        printf("0 - Sair\n");

        opcao = lerInteiro("Escolha uma opção: ");

        switch (opcao) {
            case 1:
                numero = lerInteiro("Número do Pedido: ");
                printf("Nome do Cliente: ");
                lerString(cliente, 50);
                printf("Descrição do Prato: ");
                lerString(descricao, 100);
                quantidade = lerInteiro("Quantidade: ");
                
                selecionarStatus(status); 
                push(pilha, criarPedido(numero, cliente, descricao, quantidade, status));
                printf("\nPedido #%d de %s inserido com sucesso!\n", numero, cliente);
                break;

            case 2: {
                numero = lerInteiro("Número do Pedido para buscar: ");
                Pedido *p = buscarPedido(pilha, numero);
                if (p != NULL) {
                    printf("Pedido encontrado: Cliente: %s | Prato: %s | Quantidade: %d | Status: %s\n",
                           p->cliente, p->descricao, p->quantidade, p->status);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;
            }
            
            case 3:
                numero = lerInteiro("Número do Pedido para atualizar: ");
                selecionarStatus(status);  
                atualizarStatus(pilha, numero, status);
                break;

            case 4:
                pop(pilha);
                break;

            case 5:
                listarPedidos(pilha);
                break;
                
            case 6: {
                Pedido *topo = Top(pilha);
                if (topo != NULL) {
                    printf("Topo da pilha: Pedido #%d | Cliente: %s | Prato: %s | Qtd: %d | Status: %s\n",
                           topo->numero, topo->cliente, topo->descricao, topo->quantidade, topo->status);
                }
                break;
            }
            
            case 0:
                liberarPilha(pilha);
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida! Escolha uma opção do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}
