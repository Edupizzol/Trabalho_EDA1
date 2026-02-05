#include "../include/carrinho.h"
#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>

#define ROXO "\x1b[35m"
#define RESET "\x1b[0m"

Carrinho* criar_carrinho(){

    Carrinho* carrinho = malloc(sizeof(Carrinho));
    if(carrinho==NULL){
        printf(ROXO "Erro ao criar carrinho!\n" RESET);
        return NULL;
    }

    carrinho->cliente=NULL;
    carrinho->produto=NULL;
    return carrinho;

}

void adicionar_dono_do_carrinho(Carrinho* carrinho, Cliente* cliente){

    if(cliente==NULL){
        printf(ROXO "Cliente nao existe!\n" RESET);
        return;
    }
    if(carrinho==NULL){
        printf(ROXO "Carrinho nao existe!\n" RESET);
        return;
    }

    carrinho->cliente = cliente;
    return;

}

int adicionar_produto_ao_carrinho(Carrinho* carrinho, Produto* produto, int quantidade){

    if(produto==NULL){
        printf(ROXO "Produto nao existe!\n" RESET);
        return 0;
    }
    if(carrinho==NULL){
        printf(ROXO "Carrinho nao existe!\n" RESET);
        return 0;
    }
    if(quantidade <= 0){
        printf(ROXO "Quantidade invalida!\n" RESET);
        return 0;
    }

    Produto* existe = procura_produto_no_carrinho(carrinho, produto->codigo);
    if(existe != NULL){
        if(!decrementarEstoque(produto, quantidade)){
            return 0;
        }
        existe->quantidade += quantidade;
        printf(ROXO "%dx '%s' adicionado ao existente no carrinho!\n" RESET, quantidade, produto->nome);
        return 1;
    }

    if(!decrementarEstoque(produto, quantidade)){
        return 0;
    }

    Produto* novo = malloc(sizeof(Produto));
    if(novo==NULL){
        printf(ROXO "Erro ao alocar memoria para o Produto!\n" RESET);
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
        printf(ROXO "\nO seu carrinho esta vazio!\n" RESET);
        return;
    }

    printf(ROXO "\n============================== SEU CARRINHO ==============================\n" RESET);
    printf(ROXO "Cliente: %s\n" RESET, carrinho->cliente->nome);
    printf(ROXO "---------------------------------------------------------------------------\n" RESET);

    float total = 0;
    Produto* atual = carrinho->produto;

    while(atual!=NULL){
        printf(ROXO "Codigo: %-5s | %-15s | R$ %7.2f | Quantidade: %d\n" RESET, atual->codigo, atual->nome, atual->preco, atual->quantidade);
        
        total += atual->preco * atual->quantidade;
        atual = atual->next;  
    }

    printf(ROXO "---------------------------------------------------------------------------\n" RESET);
    printf(ROXO "VALOR TOTAL:                      R$ %7.2f\n" RESET, total);
    printf(ROXO "===========================================================================\n\n" RESET);
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
        printf(ROXO "Carrinho ou produto invalido!\n" RESET);
        return NULL;
    }

    if(quantidade <= 0){
        printf(ROXO "Quantidade invalida!\n" RESET);
        return NULL;
    }

    Produto* atual=carrinho->produto;
    Produto* anterior=NULL;

    while(atual!=NULL && compara_strings(atual->codigo, produto->codigo)!=0){
        anterior=atual;
        atual=atual->next;
    }

    if(atual==NULL){
        printf(ROXO "Produto nao encontrado no carrinho!\n" RESET);
        return NULL;
    }

    if(quantidade > atual->quantidade){
        printf(ROXO "Quantidade superior ao carrinho! Max: %d\n" RESET, atual->quantidade);
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
        printf(ROXO "Produto '%s' removido completamente do carrinho!\n" RESET, atual->nome);
        return atual;
    }

    printf(ROXO "%d unidades de '%s' removidas do carrinho!\n" RESET, quantidade, atual->nome);
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
