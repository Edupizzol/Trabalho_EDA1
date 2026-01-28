#include <stdio.h>
#include "../include/clientes.h"
#include "../include/produtos.h"

typedef struct Carrinho{

    Cliente* cliente;
    Produto* produto;

}Carrinho;