#include <stdio.h>
#define TAMCli 5
#define TAMProd 5
#define TAMVend 100

typedef struct
{
    int id;
    char nome[20];
    int quantidade;
    float valor;
} Produto;

typedef struct
{
    int id;
    char nome[20];
} Cliente;

typedef struct
{
    int idCliente;
    int idProduto;
    int quantProduto;
    float valorTotal;
} Venda;

void cadastrarCliente(Cliente c[], int qtdCli)
{
    printf("Cliente %d, Primeiro Nome: ", qtdCli + 1);
    scanf("%s", c[qtdCli].nome);
    c[qtdCli].id = qtdCli + 1;
}
void cadastrarProduto(Produto p[], int qtdProd)
{
    printf("\nNome do Produto %d: ", qtdProd + 1);
    scanf("%s", p[qtdProd].nome);
    printf("Quantidade: ");
    scanf("%d", &p[qtdProd].quantidade);
    printf("Valor R$: ");
    scanf("%f", &p[qtdProd].valor);
    p[qtdProd].id = qtdProd + 1;
}
void consultarCliente(Cliente c[], int qtdCli)
{
    for (int i = 0; i < qtdCli; i++)
    {
        printf("\nId Cliente: %d", c[i].id);
        printf("\nPrimeiro Nome: %s", c[i].nome);
        printf("\n----------------------");
    }
    printf("\n\n");
}
void consultarProduto(Produto p[], int qtdProd)
{
    for (int i = 0; i < qtdProd; i++)
    {
        printf("\nId Produto: %d.", p[i].id);
        printf("\nNome Produto: %s.", p[i].nome);
        printf("\nQuantidade: %d.", p[i].quantidade);
        printf("\nValor: %.2f.", p[i].valor);
        printf("\n----------------------------------");
    }
    printf("\n\n");
}
void consultarVendas(Venda v[], int qtdVendas)
{
    printf("\n>>>> Vendas Realizadas <<<< ");
    for (int i = 0; i < qtdVendas; i++)
    {
        printf("\n%d. Cliente: %d\nProduto: %d | Quantidade: %d\nValor Total R$: %.2f", (i + 1), v[i].idCliente, v[i].idProduto, v[i].quantProduto, v[i].valorTotal);
        printf("\n");
    }
}
int contarProdutosComUmItem(Produto prod[], int qtdProd)
{
    int quantProdUmItem = 0;
    for (int i = 0; i < qtdProd; i++)
    {
        if (prod[i].quantidade == 1)
        {
            quantProdUmItem++;
        }
    }
    return quantProdUmItem;
}
int realizarVenda(Cliente c[], Produto p[], Venda v[], int qtdCli, int qtdProd, int qtdVendas)
{
    int codCli, achouCli = 0;
    printf("\nCódigo do Cliente: ");
    scanf("%d", &codCli);
    for (int i = 0; i < qtdCli; i++)
    {
        if (c[i].id == codCli)
        {
            achouCli = 1;
        }
    }
    if (achouCli != 1)
    {
        printf("Cliente não encontrado");
        return 0;
    }

    int indiceProd, codProd, achouProd = 0;
    printf("\nCódigo do produto: ");
    scanf("%d", &codProd);
    for (int i = 0; i < qtdProd; i++)
    {
        if (p[i].id == codProd)
        {
            achouProd = 1;
            indiceProd = i;
        }
    }
    if (achouProd != 1)
    {
        printf("Produto não encontrado!");
        return 0;
    }

    if (achouCli == 1 && achouProd == 1)
    {
        int quantProd;
        printf("\nInforme a quantidade desejada: ");
        scanf("%d", &quantProd);

        if (quantProd > 0)
        {
            if (quantProd <= p[indiceProd].quantidade)
            {
                if (qtdVendas < TAMVend)
                {
                    v[qtdVendas].idCliente = codCli;
                    v[qtdVendas].idProduto = codProd;
                    v[qtdVendas].quantProduto = quantProd;
                    v[qtdVendas].valorTotal = (quantProd * p[indiceProd].valor);
                    if (v[qtdVendas].valorTotal > 100)
                    {
                        v[qtdVendas].valorTotal = v[qtdVendas].valorTotal - (v[qtdVendas].valorTotal * 0.05);
                        printf("\n\tDesconto de 5%% aplicado!\n\tValor Total: %.2f", v[qtdVendas].valorTotal);
                    }
                    p[indiceProd].quantidade = p[indiceProd].quantidade - quantProd;
                    printf("\n\nVenda Realizada com Sucesso!");
                    return 1;
                }
                else
                {
                    printf("\n\nNão há mais espaços para mais vendas!");
                }
            }
            else
            {
                printf("Esta quantidade não está disponível no estoque.\nEstoque Disponível: %d\n", p[indiceProd].quantidade);
            }
        }
        else
        {
            printf("Quantidade inválida!\n");
        }
    }
    return 0;
}
void alterarEstoque(Produto p[])
{
    int codProd, qtdProd = 0;
    printf("\nDigite o código do produto: ");
    scanf("%d", &codProd);

    if (codProd == p[codProd - 1].id)
    {
        printf("\nProduto: %s\nEstoque atual: %d", p[codProd - 1].nome, p[codProd - 1].quantidade);
        printf("\nQuantos unidades possui em estoque: ");
        scanf("%d", &qtdProd);

        if (qtdProd >= 0)
        {
            p[codProd - 1].quantidade = qtdProd;
            printf("\nEstoque atualizado, total em estoque: %d", p[codProd - 1].quantidade);
        }
        else
        {
            printf("\nQuantidade Invalida!");
        }
    }
    else
    {
        printf("\nProduto não encontrado!");
    }
}

int main()
{
    int opcao, sair = 0; // sair inicialmente falso
    Cliente clientes[TAMCli];
    Produto produtos[TAMProd];
    Venda vendas[TAMVend];

    // usadas como indices  nos vetores. Isto �, controla o armazenamentos
    int quantVendasRealizadas = 0, quantClientes = 0, quantProd = 0;

    do
    {
        printf("\n\n>>>> Sistema de Vendas <<<<");
        printf("\n\t1 - Cadastrar Clientes");
        printf("\n\t2 - Cadastrar Produtos");
        printf("\n\t3 - Consultar Clientes");
        printf("\n\t4 - Consultar Produtos");
        printf("\n\t5 - Vender");
        printf("\n\t6 - Consultar Vendas");
        printf("\n\t7 - Alterar Estoque");
        printf("\n\t8 - Sair\n\t>>>> ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            if (quantClientes < TAMCli)
            {
                cadastrarCliente(clientes, quantClientes);
                quantClientes++;
            }
            else
            {
                printf("\n\nNão há mais espaço!!!");
            }
        }
        else if (opcao == 2)
        {
            if (quantProd < TAMProd)
            {
                cadastrarProduto(produtos, quantProd);
                quantProd++;
            }
            else
            {
                printf("\n\nNão há mais espaço!!!");
            }
        }
        else if (opcao == 3)
        {
            if (quantClientes > 0)
            {
                consultarCliente(clientes, quantClientes);
            }
            else
            {
                printf("\n\nNão há clientes!");
            }
        }
        else if (opcao == 4)
        {
            if (quantProd > 0)
            {
                consultarProduto(produtos, quantProd);
            }
            else
            {
                printf("\n\nNão há produtos!");
            }
        }
        else if (opcao == 5)
        {
            printf("\n\t\tVendas já realizadas: %d\n", quantVendasRealizadas);
            int vendaFoiRealizada = 0;
            int vendaRealizada = realizarVenda(clientes, produtos, vendas, quantClientes, quantProd, quantVendasRealizadas);

            if (vendaRealizada == 1)
            {
                quantVendasRealizadas++;
            }
            else
            {
                printf("\n\nVenda não Realizada!");
            }
        }
        else if (opcao == 6)
        {
            if (quantVendasRealizadas > 0)
            {
                consultarVendas(vendas, quantVendasRealizadas);
            }
            else
            {
                printf("\n\nNenhuma venda realizada... !");
            }
        }
        else if (opcao == 7)
        {
            alterarEstoque(produtos);
        }
        else if (opcao == 8)
        {
            sair = 1;
        }
        else
        {
            printf("\n\nOpção Invalida!");
        }
    } while (sair != 1);

    return 0;
}
