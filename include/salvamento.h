#ifndef SALVAMENTO_H
#define SALVAMENTO_H
#include "../include/clientes.h"
#include"../include/produtos.h"

int salvar_clientes(NodeCliente *root, const char *filename);
NodeCliente* carregar_clientes(const char *filename);
int salvar_produtos(Produto* produto, const char *filename);
Produto* carregar_produtos(const char *filename);

#endif