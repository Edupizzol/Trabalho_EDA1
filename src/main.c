#include <stdio.h>
#include <stdlib.h>
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

    NodeCliente* cliente = NULL;
    Produto* Produto = NULL;

    int n;
    char cpf[12];
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

            char telefone[15];

            printf("Digite o Nome:\n");
            scanf("%[^\n]", nome);
            printf("Digite o CPF:\n");
            scanf("%s", cpf);
            printf("Digite o Telefone:\n");
            scanf("%s", telefone);
            printf("Digite a Senha:\n");
            scanf("%s", senha);

            cadastrar_cliente(&cliente,nome,cpf,telefone,senha);

            printf("Cliente Cadastrado!\n");

            break;
        case 2:

            listar_clientes(cliente);

            break;

        case 3:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);
            remover_cliente(&cliente,cpf);

            printf("Cliente Eliminado!\n");

            break;

        case 4:

            float preco;
            
            printf("Digite o Código do Produto:\n");
            scanf("%s", senha);
            printf("Digite o Nome do Produto:\n");
            scanf("%[^\n]", nome);
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

        default:
            break;
        }

        if(n==8){

            printf("Digite o Nome do seu Usuário\n");
            scanf("%[^\n]", nome);
            printf("Digite o CPF do seu Usuário!\n");
            scanf("%s", cpf);
            printf("Digite a Senha do seu Usuário:\n");
            scanf("%s", senha);

            if(login(cliente,cpf,senha)==1){
                //volta pro inicio do loop
                continue;
            }

            printf("Login Realizado!\n");

            Carrinho *carrinho = criar_carrinho();

            NodeCliente* novo_cliente = busca_cliente(cliente,cpf);

            if(novo_cliente!=NULL){
                adicionar_dono_do_carrinho(carrinho, &(novo_cliente->dados));
            } 
            else{
                printf("Cliente Nao Existe!");
                free(carrinho); 
                continue;
            }

        }

    }

    return 0;
}

