#ifndef SALVAMENTO_H
#define SALVAMENTO_H
#include "../include/clientes.h"
#include"../include/produtos.h"

int salvar_clientes(NodeCliente *root, const char *filename);
NodeCliente* carregar_clientes(const char *filename);
int remover_cliente_arquivo(const char *filename, char* cpf);
int salvar_produtos(Produto* produto, const char *filename);
Produto* carregar_produtos(const char *filename);
int remover_produto_arquivo(const char *filename, char* codigo);
int arquivo_existe(const char *filename);
void inicializar_arquivos(const char *clientes_file, const char *produtos_file);

#endif