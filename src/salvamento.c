#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/salvamento.h"

int salvar_clientes(NodeCliente *root, const char *filename) {
    FILE *fp = fopen(filename, "w"); 
    if(fp==NULL){return 0;};

    NodeCliente *atual = root;
    while (atual != NULL) {
        
        fprintf(fp, "%s;%s;%s;%s;%s;%s\n", 
        atual->dados.nome, 
        atual->dados.cpf, 
        atual->dados.telefone, 
        atual->dados.senha, 
        atual->dados.dataDeNascimento, 
        atual->dados.email);
        atual = atual->prox;
    }

    fclose(fp);
    return 1;
}


NodeCliente* carregar_clientes(const char *filename) {
    FILE *fp = fopen(filename, "r"); 
    if(fp==NULL){return NULL;};

    NodeCliente *root = NULL;
    NodeCliente *atual = NULL;
    
    // Buffers para ler cada coluna (ajuste o tamanho se necessário)
    char* cpf = malloc(12*sizeof(char));
    if(cpf==NULL){printf("Erro de alocacao de memoria\n");fclose(fp);return NULL;}
    char* nome = malloc(100*sizeof(char));
    if(nome==NULL){printf("Erro de alocacao de memoria\n");free(cpf);fclose(fp);return NULL;}
    char* senha = malloc(20*sizeof(char));
    if(senha==NULL){printf("Erro de alocacao de memoria\n");free(cpf);free(nome);fclose(fp);return NULL;}
    char* telefone =  malloc(15*sizeof(char));
    if(telefone==NULL){printf("Erro de alocacao de memoria\n");free(cpf);free(nome);free(senha);fclose(fp);return NULL;}
    char* dataDeNascimento = malloc(15*sizeof(char));
    if(dataDeNascimento==NULL){printf("Erro de alocacao de memoria\n");free(cpf);free(nome);free(senha);free(telefone);fclose(fp);return NULL;}
    char* email = malloc(100*sizeof(char));
    if(email==NULL){printf("Erro de alocacao de memoria\n");free(cpf);free(nome);free(senha);free(telefone);free(dataDeNascimento);fclose(fp);return NULL;}

    
    while (fscanf(fp, " %99[^;];%11[^;];%19[^;];%14[^;];%14[^;];%99[^\n]\n", nome, cpf, senha, telefone, dataDeNascimento, email) == 6){
        NodeCliente *novo = (NodeCliente*)malloc(sizeof(NodeCliente));
        
        novo->dados.nome = copy_string(nome);
        novo->dados.cpf = copy_string(cpf);
        novo->dados.telefone = copy_string(telefone);
        novo->dados.senha = copy_string(senha);
        novo->dados.dataDeNascimento = copy_string(dataDeNascimento);
        novo->dados.email = copy_string(email);
        novo->prox = NULL;

        if(root==NULL){
            root=novo;
            atual=novo;
        }
        else{ 
            atual->prox=novo;
            atual=novo;
        }
    }

    free(cpf);
    free(nome);
    free(senha);
    free(telefone);
    free(dataDeNascimento);
    free(email);
    fclose(fp);
    return root;
}

int salvar_produtos(Produto* produto, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if(fp==NULL){return 0;}

    Produto *atual = produto;
    while(atual != NULL){
        fprintf(fp, "%s;%s;%.2f;%d\n",
        atual->codigo,
        atual->nome,
        atual->preco,
        atual->quantidade);
        atual = atual->next;
    }

    fclose(fp);
    return 1;
}

Produto* carregar_produtos(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { return NULL; }

    Produto *head = NULL;
    Produto *atual = NULL;

    char *codigo=malloc(20*sizeof(char));
    if(codigo==NULL){ printf("Erro de alocacao de memoria\n"); fclose(fp); return NULL;}
    char *nome = malloc(100 * sizeof(char));
    if(nome==NULL){printf("Erro de alocacao de memoria\n"); free(codigo); fclose(fp); return NULL;}
    float preco = 0.0f;
    int quantidade = 0;

    while(fscanf(fp, " %19[^;];%99[^;];%f;%d\n", codigo, nome, &preco, &quantidade)==4){
        Produto *novo=(Produto*)malloc(sizeof(Produto));
        if(novo==NULL){printf("Erro de alocacao de memoria\n");break;}

        novo->codigo = copy_string(codigo);
        novo->nome = copy_string(nome);
        novo->preco = preco;
        novo->quantidade = quantidade;
        novo->next = NULL;

        if(head==NULL){
            head=novo;
            atual=novo;
        }
        else{
            atual->next = novo;
            atual = novo;
        }
    }

    free(codigo);
    free(nome);
    fclose(fp);
    return head;
}
