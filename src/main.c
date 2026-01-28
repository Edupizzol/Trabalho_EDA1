#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/clientes.h"
#include "../src/clientes.c"

void menu(){
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Listar Clientes\n");
    printf("3. Buscar Cliente por CPF\n");
    printf("4. Remover Cliente\n");
    printf("5. Sair\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
}

int main(){
    NodeCliente* lista_clientes = NULL;
    int opcao;
    char nome[100];
    char cpf[20];
    char telefone[20];

    while(1){
        menu();
        scanf("%d", &opcao);
        getchar(); // consume newline

        switch(opcao){
            case 1:
                printf("\n--- Cadastrar Cliente ---\n");
                printf("Digite o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // remove newline

                printf("Digite o CPF do cliente: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0;

                printf("Digite o telefone do cliente: ");
                fgets(telefone, sizeof(telefone), stdin);
                telefone[strcspn(telefone, "\n")] = 0;

                cadastrar_cliente(&lista_clientes, nome, cpf, telefone);
                printf("Cliente cadastrado com sucesso!\n");
                break;

            case 2:
                printf("\n--- Listar Clientes ---\n");
                listar_clientes(lista_clientes);
                break;

            case 3:
                printf("\n--- Buscar Cliente ---\n");
                printf("Digite o CPF do cliente a buscar: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0;

                busca_cliente(lista_clientes, cpf);
                break;

            case 4:
                printf("\n--- Remover Cliente ---\n");
                printf("Digite o CPF do cliente a remover: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0;

                remover_cliente(&lista_clientes, cpf);
                printf("Cliente removido!\n");
                break;

            case 5:
                printf("Encerrando programa...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}