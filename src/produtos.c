#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* alocarTexto(char* textoOriginal){
    char* copia = malloc(strlen(textoOriginal) + 1);
    if (copia != NULL) {
        strcpy(copia, textoOriginal);
    }
    return copia;
}

Produto* cadastrarProduto(Produto* head, char* codigo, char* nome, float preco) {
    if(buscarProduto(head, codigo) != NULL) {
        printf("Erro: Produto com esse codigo %s ja esta cadastrado.\n", codigo);
        return head;
    }

    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->codigo = alocarTexto(codigo);
    novoProduto->nome = alocarTexto(nome);
    novoProduto->preco = preco;
    novoProduto->next = NULL;

    if (head == NULL || strcmp(codigo, head->codigo) < 0) {
        novoProduto->next = head;
        return novoProduto;
    }

    Produto* atual = head;
    Produto* anterior = NULL;

    while(atual != NULL && strcmp(atual->codigo, codigo) < 0){
        anterior = atual;
        atual = atual->next;
    }

    anterior->next = novoProduto;
    novoProduto->next = atual;

    return head;
}

void listarProdutos(Produto* head) {
    Produto* atual = head;
    if (atual == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    while (atual != NULL) {
        printf("-------Produtos-------\n");
        printf("Codigo: %s\nNome: %s\nPreco: %.2f\n", atual->codigo, atual->nome, atual->preco);
        printf("----------------------\n");
        atual = atual->next;
    }
}

Produto* buscarProduto(Produto* head, char* codigo) {
    Produto* atual = head;
    while (atual != NULL) {
        if (strcmp(atual->codigo, codigo) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void editarDadosProduto(Produto* produto, char* nome, float preco) {
    if (produto != NULL) {
        free(produto->nome);
        produto->nome = alocarTexto(nome);
        produto->preco = preco;
    }
    else {
        printf("Produto nao encontrado.\n");
    }
}

void removerProduto(Produto** head, char* codigo) {
    Produto* atual = *head;
    Produto* anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Produto com codigo %s nao encontrado.\n", codigo);
        return;
    }

    if (anterior == NULL) {
        *head = atual->next;
    } else {
        anterior->next = atual->next;
    }

    free(atual->codigo);
    free(atual->nome);
    free(atual); // libera o espaco q o produto ocupava
    printf("Produto com codigo %s removido.\n", codigo);
}