#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"

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
        printf(VERMELHO "Erro: Dados invalidos para cadastro do produto.\n" RESET);
        return head;
    }    
    if(buscarProduto(head, codigo) != NULL) {
        printf(VERMELHO "Erro: Produto com esse codigo %s ja esta cadastrado.\n" RESET, codigo);
        return head;
    }

    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    if(novoProduto == NULL) {
        printf(VERMELHO "Erro: Falha na alocacao de memoria para novo produto.\n" RESET);
        return head;
    }

    novoProduto->codigo = alocarTexto(codigo);
    novoProduto->nome = alocarTexto(nome);

    if(novoProduto->codigo == NULL || novoProduto->nome == NULL) {
        printf(VERMELHO "Erro: Falha na alocacao de memoria para dados do produto.\n" RESET);
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
        printf(VERMELHO "Nenhum produto cadastrado.\n" RESET);
        return;
    }
    while (atual != NULL) {
        printf(VERMELHO "-------Produtos-------\n" RESET);
        printf(VERMELHO "Codigo: %s\nNome: %s\nPreco: %.2f\nQuantidade: %d\n" RESET, atual->codigo, atual->nome, atual->preco, atual->quantidade);
        printf(VERMELHO "----------------------\n" RESET);
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
            printf(VERMELHO "Produto %s atualizado com sucesso!\n" RESET, codigo);
            return; 
        }

        atual=atual->next;
    }

    printf(VERMELHO "Erro: Produto com codigo %s nao encontrado.\n" RESET, codigo);
    return;

}

int removerProduto(Produto** head, char* codigo) {
    Produto* atual = *head;
    Produto* anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf(VERMELHO "Produto com codigo %s nao encontrado.\n" RESET, codigo);
        return 0;
    }

    if (anterior == NULL) {
        *head = atual->next;
    } else {
        anterior->next = atual->next;
    }

    free(atual->codigo);
    free(atual->nome);
    free(atual); // libera o espaco q o produto ocupava
    printf(VERMELHO "Produto com codigo %s removido.\n" RESET, codigo);
    return 1;
}

void incrementarEstoque(Produto* produto, int quantidade) { // n precisa do codigo como parametro
    if (produto == NULL || quantidade < 0) {
        printf(VERMELHO "Erro: Produto invalido ou quantidade negativa para incremento.\n" RESET);
        return;
    }
    produto->quantidade += quantidade;
    printf(VERMELHO "Estoque do produto %s incrementado em %d. Novo estoque: %d\n" RESET, produto->codigo, quantidade, produto->quantidade);
}
void liberar_todos_produtos(Produto** head){
    
    if(head == NULL || *head == NULL){
        return;
    }

    Produto* atual = *head;
    Produto* proximo = NULL;

    while(atual != NULL){
        proximo = atual->next;
        
        free(atual->codigo);
        free(atual->nome);
        
        free(atual);
        
        atual = proximo;
    }

    *head = NULL;
}
int decrementarEstoque(Produto* produto, int quantidade) {
    if (produto == NULL || quantidade < 0) {
        printf(VERMELHO "Erro: Produto invalido ou quantidade negativa para decremento.\n" RESET);
        return 0;
    }
    if (produto->quantidade < quantidade) {
        printf(VERMELHO "Erro: Estoque insuficiente para o produto %s. Estoque atual: %d, Tentativa de decremento: %d\n" RESET, produto->codigo, produto->quantidade, quantidade);
        return 0;
    }
    produto->quantidade -= quantidade;
    printf(VERMELHO "Estoque do produto %s decrementado em %d. Novo estoque: %d\n" RESET, produto->codigo, quantidade, produto->quantidade);
    return 1;
}