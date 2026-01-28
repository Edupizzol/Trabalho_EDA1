#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/carrinho.h"

void exibir_menu(){

    printf("1 : Cadastrar Novo Cliente\n");
    printf("2 : Listar Clientes\n");
    printf("3 : Deletar Cliente\n");
    printf("4 : Cadastrar Novo Produto\n");
    printf("5 : Listar Produtos\n");
    printf("6 : Listar Clientes\n");
    printf("7: Editar Produto\n");
    printf("8 : Começar as Compras\n");

}

int main(){

    NodeCliente* Cliente = NULL;
    Produto* Produto = NULL;
    int n;
    char cpf[11];
    
    while(1){

        exibir_menu();
        scanf("%d", &n);
        getchar();

        switch (n)
        {
        case 1:

            char nome[100];
            char telefone[11];
            char senha[20];

            printf("Digite o Nome:\n");
            scanf("%[^\n]", nome);
            printf("Digite o CPF:\n");
            scanf("%s", cpf);
            printf("Digite o Telefone:\n");
            scanf("%s", telefone);
            printf("Digite a Senha:\n");
            scanf("%s", senha);

            cadastrar_cliente(&Cliente,nome,cpf,telefone,senha);

            break;
        case 2:

            listar_clientes(Cliente);

            break;

        case 3:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);
            remover_cliente(&Cliente,cpf);

            break;

        default:
            break;
        }

    }

    return 0;
}