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
        printf("Cliente nao existe!\n");
        return;
    }
    if(carrinho==NULL){
        printf("Carrinho nao existe!\n");
        return;
    }

    carrinho->cliente = cliente;
    return;

}

int adicionar_produto_ao_carrinho(Carrinho* carrinho, Produto* produto, int quantidade){

    if(produto==NULL){
        printf("Produto nao existe!\n");
        return 0;
    }
    if(carrinho==NULL){
        printf("Carrinho nao existe!\n");
        return 0;
    }
    if(quantidade <= 0){
        printf("Quantidade invalida!\n");
        return 0;
    }

    Produto* existe = procura_produto_no_carrinho(carrinho, produto->codigo);
    if(existe != NULL){
        if(!decrementarEstoque(produto, quantidade)){
            return 0;
        }
        existe->quantidade += quantidade;
        printf("%dx '%s' adicionado ao existente no carrinho!\n", quantidade, produto->nome);
        return 1;
    }

    // Check if stock decrement is possible before allocating memory
    if(!decrementarEstoque(produto, quantidade)){
        return 0;
    }

    Produto* novo = malloc(sizeof(Produto));
    if(novo==NULL){
        printf("Erro ao alocar memoria para o Produto!\n");
        exit(EXIT_FAILURE);
    }

    novo->nome = copy_string(produto->nome);
    novo->codigo = copy_string(produto->codigo);
    novo->preco = produto->preco;
    novo->quantidade = quantidade;
    novo->next = NULL;

    if(carrinho->produto == NULL){
        carrinho->produto = novo;
        return 1;
    }

    Produto* atual = carrinho->produto;
    while(atual->next != NULL){
        atual = atual->next;
    }

    atual->next = novo;
    return 1;

}

void ver_produtos_no_carrinho(Carrinho* carrinho){

    if(carrinho == NULL || carrinho->produto == NULL){
        printf("\nO seu carrinho esta vazio!\n");
        return;
    }

    printf("\n========== SEU CARRINHO ==========\n");
    printf("Cliente: %s\n", carrinho->cliente->nome);
    printf("----------------------------------\n");

    float total = 0;
    Produto* atual = carrinho->produto;

    while(atual!=NULL){
        printf("Codigo: %-5s | %-15s | R$ %7.2f | Quantidade: %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);
        
        total += atual->preco * atual->quantidade;
        atual = atual->next;  
    }

    printf("----------------------------------\n");
    printf("VALOR TOTAL:             R$ %7.2f\n", total);
    printf("==================================\n\n");
}

Produto* procura_produto_no_carrinho(Carrinho* carrinho, char* codigo){

    if(carrinho==NULL){
        return NULL;
    }

    Produto* dummy = carrinho->produto;
    while(dummy!=NULL){
        if(compara_strings(dummy->codigo,codigo)==0){
            return dummy;
        }
        dummy=dummy->next;
    }
    return NULL;

}

Produto* remove_produto_do_carrinho(Carrinho* carrinho, Produto* produto, int quantidade){

    if(carrinho==NULL || produto==NULL){
        printf("Carrinho ou produto invalido!\n");
        return NULL;
    }

    if(quantidade <= 0){
        printf("Quantidade invalida!\n");
        return NULL;
    }

    Produto* atual=carrinho->produto;
    Produto* anterior=NULL;

    while(atual!=NULL && compara_strings(atual->codigo, produto->codigo)!=0){
        anterior=atual;
        atual=atual->next;
    }

    if(atual==NULL){
        printf("Produto nao encontrado no carrinho!\n");
        return NULL;
    }

    if(quantidade > atual->quantidade){
        printf("Quantidade superior ao carrinho! Max: %d\n", atual->quantidade);
        return NULL;
    }

    incrementarEstoque(produto, quantidade);
    atual->quantidade -= quantidade;

    //caso remova completamente o produto, desliga o nó
    if(atual->quantidade == 0){
        if(anterior==NULL){
            carrinho->produto = atual->next;
        } else {
            anterior->next = atual->next;
        }
        printf("Produto '%s' removido completamente do carrinho!\n", atual->nome);
        return atual;
    }

    printf("%d unidades de '%s' removidas do carrinho!\n", quantidade, atual->nome);
    return atual;

}

void liberar_carrinho(Carrinho** carrinho){
    
    if(carrinho == NULL || *carrinho == NULL){
        return;
    }

    // Liberar a lista de produtos do carrinho
    Produto* atual = (*carrinho)->produto;
    Produto* proximo = NULL;

    while(atual != NULL){
        proximo = atual->next;
        
        // Liberar as strings do produto
        free(atual->codigo);
        free(atual->nome);
        
        // Liberar o produto
        free(atual);
        
        atual = proximo;
    }

    // Liberar o carrinho
    free(*carrinho);
    *carrinho = NULL;
}
