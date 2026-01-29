#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* alocarTexto(char* textoOriginal){
    if(textoOriginal == NULL){
        return NULL;
    }
    char* copia = malloc(strlen(textoOriginal) + 1);
    if (copia != NULL) {
        strcpy(copia, textoOriginal);
    }
    return copia;
}

Produto* cadastrarProduto(Produto* head, char* codigo, char* nome, float preco, int quantidade) {
    if (codigo == NULL || nome == NULL || preco < 0 || quantidade < 0){
        printf("Erro: Dados invalidos para cadastro do produto.\n");
        return head;
    }    
    if(buscarProduto(head, codigo) != NULL) {
        printf("Erro: Produto com esse codigo %s ja esta cadastrado.\n", codigo);
        return head;
    }

    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    if(novoProduto == NULL) {
        printf("Erro: Falha na alocacao de memoria para novo produto.\n");
        return head;
    }

    novoProduto->codigo = alocarTexto(codigo);
    novoProduto->nome = alocarTexto(nome);

    if(novoProduto->codigo == NULL || novoProduto->nome == NULL) {
        printf("Erro: Falha na alocacao de memoria para dados do produto.\n");
        free(novoProduto->codigo);
        free(novoProduto->nome);
        free(novoProduto);
        return head;
    }
    novoProduto->preco = preco;
    novoProduto->quantidade = quantidade;
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
        printf("Codigo: %s\nNome: %s\nPreco: %.2f\nQuantidade: %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);
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

void editarDadosProduto(Produto* head, char* codigo, char* novoNome, float novoPreco, int novaQuantidade) {

    Produto* atual=head;
    while(atual!=NULL) {

        if(strcmp(atual->codigo, codigo)==0){
            
            free(atual->nome);
            atual->nome = alocarTexto(novoNome);
            atual->preco = novoPreco;
            atual->quantidade = novaQuantidade;
            printf("Produto %s atualizado com sucesso!\n", codigo);
            return; 
        }

        atual=atual->next;
    }

    printf("Erro: Produto com codigo %s nao encontrado.\n", codigo);
    return;

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

void incrementarEstoque(Produto* produto, int quantidade) { // n precisa do codigo como parametro
    if (produto == NULL || quantidade < 0) {
        printf("Erro: Produto invalido ou quantidade negativa para incremento.\n");
        return;
    }
    produto->quantidade += quantidade;
    printf("Estoque do produto %s incrementado em %d. Novo estoque: %d\n", produto->codigo, quantidade, produto->quantidade);
}

void decrementarEstoque(Produto* produto, int quantidade) {
    if (produto == NULL || quantidade < 0) {
        printf("Erro: Produto invalido ou quantidade negativa para decremento.\n");
        return;
    }
    if (produto->quantidade < quantidade) {
        printf("Erro: Estoque insuficiente para o produto %s. Estoque atual: %d, Tentativa de decremento: %d\n", produto->codigo, produto->quantidade, quantidade);
        return;
    }
    produto->quantidade -= quantidade;
    printf("Estoque do produto %s decrementado em %d. Novo estoque: %d\n", produto->codigo, quantidade, produto->quantidade);
}