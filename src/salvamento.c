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

int remover_cliente_arquivo(const char *filename, char* cpf) {
    FILE *fp = fopen(filename, "r");
    if (fp==NULL){return 0;};

    FILE *temp = fopen("temp.csv", "w");
    if(temp==NULL){fclose(fp);return 0;}
    
    char *linha = malloc(1000*sizeof(char));
    if(linha==NULL){printf("Erro de alocacao de memoria\n");fclose(fp);fclose(temp);return 0;}
    char *linha_copia = malloc(1000*sizeof(char));
    if(linha_copia==NULL){printf("Erro de alocacao de memoria\n");free(linha);fclose(fp);fclose(temp);return 0;}
    int encontrado = 0;

    while (fgets(linha, 1000, fp)) {
        strcpy(linha_copia, linha);

        strtok(linha, ";"); //pula o nome
        char *cpf_linha = strtok(NULL, ";"); //pega o CPF

        if(cpf_linha && strcmp(cpf_linha, cpf)==0){
            encontrado=1; 
        } 
        else{
            fputs(linha_copia, temp); 
        }
    }

    fclose(fp);
    fclose(temp);

    free(linha);
    free(linha_copia);

    remove(filename);
    rename("temp.csv", filename);
    return encontrado;

}
