#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"

typedef struct Carrinho{

    Cliente* cliente;
    Produto* produto;

}Carrinho;

void adicionar_ao_carrinho(Carrinho* carrinho, Produto** produto);
Produto* procura_produto(Carrinho* carrinho, Produto* produto);

