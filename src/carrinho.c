#include "../include/carrinho.h"
#include "../include/produtos.h"
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

void ver_produtos_no_carrinho(Carrinho* carrinho){

    if(carrinho == NULL || carrinho->produto == NULL){
        printf("\nO seu carrinho está vazio!\n");
        return;
    }

    printf("\n========== SEU CARRINHO ==========\n");
    printf("Cliente: %s\n", carrinho->cliente->nome);
    printf("----------------------------------\n");

    float total = 0;
    Produto* atual = carrinho->produto;

    while(atual!=NULL){
        printf("Codigo: %-5s | %-15s | R$ %7.2f\n", atual->codigo, atual->nome, atual->preco);
        
        total += atual->preco;
        atual = atual->next;  
    }

    printf("----------------------------------\n");
    printf("VALOR TOTAL:             R$ %7.2f\n", total);
    printf("==================================\n\n");
}

Produto* procura_produto_no_carrinho(Carrinho* carrinho, char* codigo){

    if(carrinho==NULL){
        printf("Carrinho não existe!\n");
        return NULL;
    }

    Produto* dummy = carrinho->produto;
    while(dummy!=NULL){
        if(compara_strings(dummy->codigo,codigo)==0){
            printf("Produto encontrado!\n");
            printf("Codigo: %s\nNome: %s\nPreco: %.2f\n", dummy->codigo, dummy->nome, dummy->preco);
            return dummy;
        }
        dummy=dummy->next;
    }
    printf("Produto nao encontrado!\n");
    return NULL;

}

Produto* remove_produto_do_carrinho(Carrinho* carrinho, Produto* produto){

    if(carrinho==NULL || produto==NULL){
        printf("Carrinho ou produto inválido!\n");
        return NULL;
    }

    Produto* atual=carrinho->produto;
    Produto* anterior=NULL;

    if(atual!=NULL && compara_strings(atual->codigo, produto->codigo)==0){
        carrinho->produto=atual->next;
        atual->next=NULL; 
        return atual;
    }
    while(atual!=NULL && compara_strings(atual->codigo, produto->codigo)!=0){
        anterior=atual;
        atual=atual->next;
    }

    if(atual==NULL){
        printf("Produto não encontrado no carrinho!\n");
        return NULL;
    }

    anterior->next=atual->next;
    atual->next=NULL;

    return atual;

}

