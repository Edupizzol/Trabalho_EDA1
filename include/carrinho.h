#ifndef CARRINHO_H
#define CARRINHO_H
#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"

typedef struct Carrinho{

    Cliente* cliente;
    Produto* produto;

}Carrinho;

Carrinho* criar_carrinho();
void adicionar_dono_do_carrinho(Carrinho* carrinho, Cliente* cliente);
int adicionar_produto_ao_carrinho(Carrinho* carrinho, Produto* produto, int quantidade);
Produto* procura_produto_no_carrinho(Carrinho* carrinho, char* codigo);
Produto* remove_produto_do_carrinho(Carrinho* carrinho, Produto* produto, int quantidade);
void ver_produtos_no_carrinho(Carrinho* carrinho);

#endif