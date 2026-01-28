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

int compara_strings(char* string1, char* string2){

    int i=0;
    while(string1[i]!='\0' && string2[i]!='\0'){
        if(string1[i]!=string2[i]){
            return 1;
        }
        i++;
    }

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

    Cliente* new_cliente = criar_cliente(nome,cpf,telefone);
    NodeCliente* new_node = malloc(sizeof(NodeCliente));

    if(new_node==NULL){
        printf("Erro ao alocar memória para o nó do Cliente!\n");
        exit(EXIT_FAILURE);
    }

    new_node->dados = *new_cliente;

    free(new_cliente);

    if(*lista==NULL){
        *lista = new_node;
        return;
    }

    if(ordem_alfabetica(new_node->dados.nome,(*lista)->dados.nome)==1){
        new_node->prox = *lista;
        *lista = new_node;
        return;
    }

    //percorre a lista pra encontrar posicao correta
    NodeCliente* atual = *lista;
    while(atual->prox != NULL && ordem_alfabetica(new_node->dados.nome, atual->prox->dados.nome) != 1){
        atual = atual->prox;
    }

    new_node->prox = atual->prox;
    atual->prox = new_node;
    
}

void listar_clientes(NodeCliente *root){

    if(root==NULL){
        printf("Não há clientes cadastrados!\n");
        return;
    }

    while(root!=NULL){

        printf("---------------------------------------\n");
        printf("Nome do Cliente: %s\n", root->dados.nome);
        printf("CPF do Cliente: %s\n", root->dados.cpf);
        printf("Telefone do Cliente: %s\n", root->dados.telefone);
        printf("---------------------------------------\n");
        root=root->prox;

    }

    return;

}

Cliente* busca_cliente(NodeCliente *root, char* cpf){

    if(root==NULL){
        printf("Não há clientes cadastrados!\n");
        return NULL;
    }

    while(root!=NULL){
        if(compara_strings(root->dados.cpf,cpf)==0){
            printf("-------Dados do Cliente-------\n");
            printf("Nome: %s\n", root->dados.nome);
            printf("CPF: %s\n", root->dados.cpf);
            printf("Telefone: %s\n", root->dados.telefone);
            printf("-----------------------------\n");
            return root;
        }
        root=root->prox;
    }

    printf("O cliente não está cadastrado\n");
    return NULL;

}

void remover_cliente(NodeCliente **root, char* cpf){

    NodeCliente *temp = *root;
    NodeCliente *previous = NULL;

    if(temp!=NULL && compara_strings(temp->dados.cpf,cpf)==0){
        *root=temp->prox;
        free(temp);
        return;
    }

    while(temp!=NULL && compara_strings(temp->dados.cpf,cpf)!=0){

        previous=temp;
        temp=temp->prox;

    }

    if(temp==NULL){
        printf("Cliente nao encontrado!\n");
        return;
    }

    //desconectar o no que vai ser removido
    previous->prox = temp->prox;

    free(temp);

}
