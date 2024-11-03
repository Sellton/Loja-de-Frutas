#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar dados das frutas
typedef struct {
    int codigo;
    char nome[20];
    int quantidade;
    float preco;
} Fruta;

// Estrutura de nos para lista encadeada
typedef struct Nodo {
    Fruta fruta;
    struct Nodo *prox;
} Nodo;

// Função para cadastrar uma nova fruta
Nodo* cadastrarFruta(Nodo *inicio) {
    Fruta novaFruta;
    Nodo *atual = inicio;

    printf("Código da fruta: ");
    scanf("%d", &novaFruta.codigo);

    // Verificar se o código já existe
    while (atual != NULL) {
        if (atual->fruta.codigo == novaFruta.codigo) {
            printf("Código já cadastrado.\n");
            return inicio;
        }
        atual = atual->prox;
    }

    printf("Nome da fruta: ");
    scanf("%s", novaFruta.nome);
    printf("Quantidade: ");
    scanf("%d", &novaFruta.quantidade);
    printf("Preço: ");
    scanf("%f", &novaFruta.preco);

    // Inserir a nova fruta na lista
    Nodo *novoNodo = (Nodo*) malloc(sizeof(Nodo));
    novoNodo->fruta = novaFruta;
    novoNodo->prox = inicio;
    return novoNodo;
}

// Função para listar todas as frutas cadastradas
void listarFrutas(Nodo *inicio) {
    Nodo *atual = inicio;
    while (atual != NULL) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               atual->fruta.codigo, atual->fruta.nome, atual->fruta.quantidade, atual->fruta.preco);
        atual = atual->prox;
    }
}

// Função para vender uma fruta
void venderFruta(Nodo *inicio) {
    int codigo, quantidade;
    FILE *arquivo = fopen("vendas.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }

    printf("Código da fruta: ");
    scanf("%d", &codigo);
    printf("Quantidade a vender: ");
    scanf("%d", &quantidade);

    Nodo *atual = inicio;
    while (atual != NULL) {
        if (atual->fruta.codigo == codigo) {
            if (atual->fruta.quantidade >= quantidade) {
                atual->fruta.quantidade -= quantidade;
                fprintf(arquivo, "Código: %d, Nome: %s, Quantidade vendida: %d, Valor total: %.2f\n",
                        atual->fruta.codigo, atual->fruta.nome, quantidade, quantidade * atual->fruta.preco);
                printf("Venda realizada.\n");
            } else {
                printf("Estoque insuficiente.\n");
            }
            fclose(arquivo);
            return;
        }
        atual = atual->prox;
    }
    printf("Fruta não encontrada.\n");
    fclose(arquivo);
}

// Função para alterar os dados de uma fruta
void alterarFruta(Nodo *inicio) {
    int codigo;
    printf("Digite o código da fruta que deseja alterar: ");
    scanf("%d", &codigo);

    Nodo *atual = inicio;
    while (atual != NULL) {
        if (atual->fruta.codigo == codigo) {
            printf("Nova quantidade: ");
            scanf("%d", &atual->fruta.quantidade);
            printf("Novo preço: ");
            scanf("%f", &atual->fruta.preco);
            printf("Dados da fruta atualizados com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Fruta com código %d não encontrada.\n", codigo);
}

// Função para excluir uma fruta
Nodo* excluirFruta(Nodo *inicio) {
    int codigo;
    printf("Digite o código da fruta que deseja excluir: ");
    scanf("%d", &codigo);

    Nodo *atual = inicio;
    Nodo *anterior = NULL;

    while (atual != NULL) {
        if (atual->fruta.codigo == codigo) {
            if (atual->fruta.quantidade > 0) {
                printf("Não é possível excluir. A fruta ainda possui estoque.\n");
                return inicio;
            }
            if (anterior == NULL) {
                // Excluir o primeiro nó
                inicio = atual->prox;
            } else {
                // Excluir um nó intermediário ou final
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Fruta excluída com sucesso.\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Fruta com código %d não encontrada.\n", codigo);
    return inicio;
}

// Função para salvar as frutas cadastradas em um arquivo
void salvarFrutas(Nodo *inicio) {
    FILE *arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    Nodo *atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s %d %.2f\n", atual->fruta.codigo, atual->fruta.nome, atual->fruta.quantidade, atual->fruta.preco);
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso.\n");
}

// Função para carregar frutas
Nodo* carregarFrutas() {
    FILE *arquivo = fopen("Estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de frutas não encontrado ou vazio.\n");
        return NULL;
    }

    Nodo *inicio = NULL;
    Fruta fruta;
    while (fscanf(arquivo, "%d %s %d %f", &fruta.codigo, fruta.nome, &fruta.quantidade, &fruta.preco) != EOF) {
        Nodo *novoNodo = (Nodo*) malloc(sizeof(Nodo));
        novoNodo->fruta = fruta;
        novoNodo->prox = inicio;
        inicio = novoNodo;
    }

    fclose(arquivo);
    printf("Dados das frutas carregados com sucesso.\n");
    printf("\n           ,--./,-.\n");
    printf("          / #      \\\n");
    printf("         |   Menu   |\n");
    printf("          \\        / \n");
    printf("           `._,._,'\n");
    return inicio;
}

// Função do menu

int main() {
    int opcao;
    Nodo *inicio = carregarFrutas();

    do {

        printf("\n1. Cadastrar Nova Fruta No Estoque\n");
        printf("2. Vender Fruta\n");
        printf("3. Listar Estoque De Frutas\n");
        printf("4. Alterar Estoque\n");
        printf("5. Excluir Fruta Do Estoque\n");
        printf("6. Salvar Novos Dados da loja\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicio = cadastrarFruta(inicio);
                break;
            case 2:
                venderFruta(inicio);
                break;
            case 3:
                listarFrutas(inicio);
                break;
            case 4:
                alterarFruta(inicio);
                break;
            case 5:
                inicio = excluirFruta(inicio);
                break;
            case 6:
                salvarFrutas(inicio);
                break;
            case 7:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
