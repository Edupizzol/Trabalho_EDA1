#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"

typedef struct Carrinho{

    Cliente* cliente;
    Produto* produto;

}Carrinho;

Carrinho* criar_carrinho(Carrinho* carrinho);
void adicionar_dono_do_carrinho(Carrinho* carrinho, Cliente* cliente);
void adicionar_ao_carrinho(Carrinho* carrinho, Produto* produto);
Produto* procura_produto_no_carrinho(Carrinho* carrinho, Produto* produto);
Produto* remove_produto_do_carrinho(Carrinho* carrinho, Produto* produto);

