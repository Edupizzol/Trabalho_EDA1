#include "include/clientes.h"
#include <stdio.h>
#include <stdlib.h>

char* copy_string(char* string){
    
    int i=0;
    int memory_size=0;
    char* new_string = NULL;

    while(string[i]!='\0'){

        if(i==memory_size){

            memory_size+=10;

            char* temp = realloc(new_string,memory_size*sizeof(char));
            if(temp==NULL){
                printf("Erro durante a alocação de memória do nome do cliente!\n");
                exit(EXIT_FAILURE);
            }

            new_string = temp;

            }

        new_string[i]=string[i];
        i++;

    }

    char* temp = realloc(new_string,i+1);
    if(temp==NULL){
        printf("Erro durante a alocação de memória do nome do cliente!\n");
        exit(EXIT_FAILURE);
    }
    new_string = temp;
    
    new_string[i]='\0';
    return new_string;

}

int ordem_alfabetica(char* string1, char* string2){

    int i=0;

    while(string1[i]!='\0' && string2[i]!='\0'){

        if(string1[i]!=string2[i]){
            if(string1[i]<string2[i]){
                return 1;
            }
            else if(string1[i]>string2[i]){
                return 2;
            }
        }

        i++;

    }

    if(string1[i] == '\0' && string2[i] != '\0') return 1;
    if(string2[i] == '\0' && string1[i] != '\0') return 2;

    return 0;

}

Cliente* criar_cliente(char* nome, char* cpf, char* telefone){

    Cliente* new_cliente = malloc(sizeof(Cliente));
    if(new_cliente==NULL){
        printf("Erro ao alocar memória para Cliente!");
        exit(EXIT_FAILURE);
    }

    new_cliente->cpf = copy_string(cpf);
    new_cliente->nome = copy_string(nome);
    new_cliente->telefone = copy_string(telefone);

    return new_cliente;
    
}

void cadastrar_cliente(NodeCliente** lista, char* nome, char* cpf, char* telefone){



}