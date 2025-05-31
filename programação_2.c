#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40

typedef struct {
    int codigo;
    char descricao[100];
    float valor_unitario;
    int quantidade;
} Produto;

Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;

void cadastrarProduto() {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &produtos[total_produtos].codigo);
    printf("Descricao: ");
    getchar();
    fgets(produtos[total_produtos].descricao, 100, stdin);
    produtos[total_produtos].descricao[strcspn(produtos[total_produtos].descricao, "\n")] = 0;
    printf("Valor unitario: ");
    scanf("%f", &produtos[total_produtos].valor_unitario);
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[total_produtos].quantidade);

    total_produtos++;
    printf("Produto cadastrado com sucesso!\n");
}

int encontrarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void alterarValorUnitario(int codigo) {
    int i = encontrarProdutoPorCodigo(codigo);
    if (i != -1) {
        printf("Novo valor unitario: ");
        scanf("%f", &produtos[i].valor_unitario);
        printf("Valor atualizado com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

float obterValorUnitario(int codigo) {
    int i = encontrarProdutoPorCodigo(codigo);
    if (i != -1) {
        return produtos[i].valor_unitario;
    }
    return -1;
}

int obterQuantidadeEstoque(int codigo) {
    int i = encontrarProdutoPorCodigo(codigo);
    if (i != -1) {
        return produtos[i].quantidade;
    }
    return -1;
}

void venderProduto(int codigo, int quantidade_desejada) {
    int i = encontrarProdutoPorCodigo(codigo);
    if (i == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    if (produtos[i].quantidade == 0) {
        printf("Produto sem estoque.\n");
        return;
    }

    if (quantidade_desejada < produtos[i].quantidade) {
        produtos[i].quantidade -= quantidade_desejada;
        float total = quantidade_desejada * produtos[i].valor_unitario;
        printf("Compra realizada. Total a pagar: R$ %.2f\n", total);
    } else if (quantidade_desejada == produtos[i].quantidade) {
        produtos[i].quantidade = 0;
        float total = quantidade_desejada * produtos[i].valor_unitario;
        printf("Compra realizada. Total a pagar: R$ %.2f\n", total);
    } else {
        printf("Estoque insuficiente. Deseja comprar os %d restantes? (1 - Sim / 0 - Nao): ", produtos[i].quantidade);
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            float total = produtos[i].quantidade * produtos[i].valor_unitario;
            produtos[i].quantidade = 0;
            printf("Compra parcial realizada. Total a pagar: R$ %.2f\n", total);
        } else {
            printf("Compra cancelada.\n");
        }
    }
}

void atualizarEstoque(int codigo, int nova_quantidade) {
    int i = encontrarProdutoPorCodigo(codigo);
    if (i != -1) {
        produtos[i].quantidade = nova_quantidade;
        printf("Estoque atualizado.\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void listarProdutos() {
    for (int i = 0; i < total_produtos; i++) {
        printf("Codigo: %d - Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void listarProdutosSemEstoque() {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade == 0) {
            printf("Codigo: %d - Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
        }
    }
}

void menu() {
    int opcao, codigo, quantidade;
    float valor;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Alterar valor unitario\n");
        printf("3 - Consultar valor unitario\n");
        printf("4 - Consultar quantidade em estoque\n");
        printf("5 - Vender produto\n");
        printf("6 - Atualizar estoque\n");
        printf("7 - Listar produtos\n");
        printf("8 - Listar produtos com estoque zero\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                alterarValorUnitario(codigo);
                break;
            case 3:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                valor = obterValorUnitario(codigo);
                if (valor != -1)
                    printf("Valor unitario: R$ %.2f\n", valor);
                else
                    printf("Produto nao encontrado.\n");
                break;
            case 4:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                quantidade = obterQuantidadeEstoque(codigo);
                if (quantidade != -1)
                    printf("Quantidade em estoque: %d\n", quantidade);
                else
                    printf("Produto nao encontrado.\n");
                break;
            case 5:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                printf("Quantidade desejada: ");
                scanf("%d", &quantidade);
                venderProduto(codigo, quantidade);
                break;
            case 6:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                printf("Nova quantidade em estoque: ");
                scanf("%d", &quantidade);
                atualizarEstoque(codigo, quantidade);
                break;
            case 7:
                listarProdutos();
                break;
            case 8:
                listarProdutosSemEstoque();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

int main() {
    menu();
    return 0;
}
