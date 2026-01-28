#include <stdio.h>

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

    int n;
    
    while(1){

        exibir_menu();
        scanf("%d", &n);
        getchar();

    }

    return 0;
}