#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/carrinho.h"

void exibir_menu(){

    printf("0 : Terminar Execução\n");
    printf("1 : Cadastrar Novo Cliente\n");
    printf("2 : Listar Clientes\n");
    printf("3 : Deletar Cliente\n");
    printf("4 : Cadastrar Novo Produto\n");
    printf("5 : Listar Produtos\n");
    printf("6 : Remover Produto\n");
    printf("7 : Editar Produto\n");
    printf("8 : Começar as Compras\n");

}

int main(){

    NodeCliente* Cliente = NULL;
    Produto* Produto = NULL;

    int n;
    char cpf[11];
    char nome[100];
    char senha[20];
    
    while(1){

        exibir_menu();
        scanf("%d", &n);
        getchar();

        if(n==0){
            printf("Execução Finalizada!\n");
            return 0;
        }

        switch (n)
        {
        case 1:

            char telefone[11];

            printf("Digite o Nome:\n");
            scanf("%[^\n]", nome);
            printf("Digite o CPF:\n");
            scanf("%s", cpf);
            printf("Digite o Telefone:\n");
            scanf("%s", telefone);
            printf("Digite a Senha:\n");
            scanf("%s", senha);

            cadastrar_cliente(&Cliente,nome,cpf,telefone,senha);

            printf("Cliente Cadastrado!\n");

            break;
        case 2:

            listar_clientes(Cliente);

            break;

        case 3:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);
            remover_cliente(&Cliente,cpf);

            printf("Cliente Eliminado!\n");

            break;

        case 4:

            float preco;
            
            printf("Digite o Código do Produto:\n");
            scanf("%s", senha);
            printf("Digite o Nome do Produto:\n");
            scanf("%s", nome);
            printf("Digite o Preco do Produto:\n");
            scanf("%f", &preco);
            Produto = cadastrarProduto(Produto,senha,nome,preco);

            printf("Produto Cadastrado!\n");

            break;

        case 5:

            listarProdutos(Produto);

            break;

        case 6:

            printf("Digite o Código do Produto:\n");
            scanf("%s", senha);
            removerProduto(&Produto,senha);

            printf("Produto Removido!\n");

            break;

        case 7:

            printf("Digite o Código do Produto!\n");
            scanf("%s", senha);

            printf("Digite o Novo Preco e o Novo Nome:\n");
            
            scanf("%f", &preco);
            getchar();
            scanf("%s", nome);

            editarDadosProduto(Produto,senha,nome,preco);

            printf("Produto Editado com Sucesso!\n");

        case 8:

            printf("Adicionado em Breve\n");

            break;

        default:
            break;
        }

    }

    return 0;
}

