#include "../include/carrinho.h"
#include <stdio.h>
#include <stdlib.h>

Carrinho* criar_carrinho(){

    Carrinho* carrinho = malloc(sizeof(Carrinho));
    if(carrinho==NULL){
        printf("Erro ao criar carrinho!\n");
        return NULL;
    }

    carrinho->cliente=NULL;
    carrinho->produto=NULL;
    return carrinho;

}

void adicionar_dono_do_carrinho(Carrinho* carrinho, Cliente* cliente){

    if(cliente==NULL){
        printf("Cliente não existe!\n");
        return;
    }
    if(carrinho==NULL){
        printf("Carrinho não existe!\n");
        return;
    }

    carrinho->cliente = cliente;
    return;

}

void adicionar_produto_ao_carrinho(Carrinho* carrinho, Produto* produto){

    if(produto==NULL){
        printf("Produto não existe!\n");
        return;
    }
    if(carrinho==NULL){
        printf("Carrinho não existe!\n");
        return;
    }

    Produto* novo = malloc(sizeof(Produto));
    if(novo==NULL){
        printf("Erro ao alocar memoria para o Produto!\n");
        exit(EXIT_FAILURE);
    }

    novo->nome = copy_string(produto->nome);
    novo->codigo = copy_string(produto->codigo);
    novo->preco = produto->preco;
    novo->next = NULL;

    if(carrinho->produto == NULL){
        carrinho->produto = novo;
        return;
    }

    Produto* atual = carrinho->produto;
    while(atual->next != NULL){
        atual = atual->next;
    }

    atual->next = novo;

}