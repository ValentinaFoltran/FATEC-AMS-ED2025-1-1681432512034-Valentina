/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-3                                 */
/*             Objetivo: << Maipulação de Lista Ligada >>                           */
/*                                                                                  */
/*                                  Autor: Valentina Foltran Carvalho               */
/*                                                                  Data:23/03/2025 */
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

void inserirPedido(Pedido **lista, Pedido *novo) {
    novo->proximo = *lista;
    *lista = novo;
}

Pedido* buscarPedido(Pedido *lista, int numero) {
    while (lista != NULL) {
        if (lista->numero == numero) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}

void atualizarStatus(Pedido *lista, int numero, char novoStatus[]) {
    Pedido *pedido = buscarPedido(lista, numero);
    if (pedido != NULL) {
        strcpy(pedido->status, novoStatus);
        printf("Status do pedido %d atualizado para: %s\n", numero, novoStatus);
    } else {
        printf("Pedido não encontrado!\n");
    }
}

void removerPedido(Pedido **lista, int numero) {
    Pedido *atual = *lista, *anterior = NULL;
    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Pedido não encontrado!\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Pedido %d removido com sucesso!\n", numero);
}

void listarPedidos(Pedido *lista) {
    if (lista == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    while (lista != NULL) {
        printf("Pedido #%d | Cliente: %s | Prato: %s | Qtd: %d | Status: %s\n", 
               lista->numero, lista->cliente, lista->descricao, lista->quantidade, lista->status);
        lista = lista->proximo;
    }
}

void liberarLista(Pedido **lista) {
    Pedido *atual = *lista;
    while (atual != NULL) {
        Pedido *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}

//Ler string com espaços
void lerString(char *str, int tamanho) { 
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0'; 
}

// Validar um número inteiro 
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
    Pedido *lista = NULL;
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20];

    do {
        printf("\nSistema de Gerenciamento de Pedidos - Restaurante Alecrim\n");
        printf("1 - Inserir Pedido\n");
        printf("2 - Buscar Pedido\n");
        printf("3 - Atualizar Status\n");
        printf("4 - Remover Pedido\n");
        printf("5 - Listar Pedidos\n");
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
                inserirPedido(&lista, criarPedido(numero, cliente, descricao, quantidade, status));
                printf("\nPedido #%d de %s inserido com sucesso!\n", numero, cliente);
                break;

            case 2:
                numero = lerInteiro("Número do Pedido para buscar: ");
                Pedido *p = buscarPedido(lista, numero);
                if (p != NULL) {
                    printf("Pedido encontrado: Cliente: %s | Prato: %s | Quantidade: %d | Status: %s\n",
                           p->cliente, p->descricao, p->quantidade, p->status);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;

            case 3:
                numero = lerInteiro("Número do Pedido para atualizar: ");
                selecionarStatus(status);  
                atualizarStatus(lista, numero, status);
                break;

            case 4:
                numero = lerInteiro("Número do Pedido para remover: ");
                removerPedido(&lista, numero);
                break;

            case 5:
                listarPedidos(lista);
                break;

            case 0:
                liberarLista(&lista);
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida! Escolha uma opção do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}
