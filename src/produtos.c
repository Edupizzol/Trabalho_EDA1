#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>

Produto* cadastrarProduto(Produto* head, char* codigo, char* nome, float preco) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->codigo = codigo;
    novoProduto->nome = nome;
    novoProduto->preco = preco;
    novoProduto->next = head;
    return novoProduto;
}

void listarProdutos(Produto* head) {
    Produto* atual = head;
    while (atual != NULL) {
        printf("Codigo: %s, Nome: %s, Preco: %.2f\n", atual->codigo, atual->nome, atual->preco);
        atual = atual->next;
    }
}

Produto* buscarProduto(Produto* head, char* codigo) {
    Produto* atual = head;
    while (atual != NULL) {
        if (strcmp(atual->codigo, codigo) == 0) {
            return atual;
        }
        else {
            printf("Produto com codigo %s nao encontrado.\n", codigo);
        }
        atual = atual->next;
    }
    return NULL;
}

void editarDadosProduto(Produto* produto, char* nome, float preco) {
    if (produto != NULL) {
        produto->nome = nome;
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
}