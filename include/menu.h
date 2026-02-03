#ifndef MENU_H
#define MENU_H

#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/carrinho.h"
#include "../include/historico.h"
#include "../include/salvamento.h"

void finalizar(NodeCliente* cliente, Produto* produto, Historico* historico, char* cpf, char* nome, char* senha);
void cadastra_cliente_menu(NodeCliente** cliente, Historico* historico, char* nome, char* cpf, char* senha, char* telefone, char* dataDeNascimento, char* email);
void busca_cliente_menu(NodeCliente* cliente, Historico* historico, char* cpf);
int edita_cliente_menu(NodeCliente* cliente, Historico* historico, char* nome, char* cpf, char* senha, char* dataDeNascimento, char* email);
void listar_clientes_menu(NodeCliente* cliente, Historico* historico);
void deletar_clientes_menu(NodeCliente** cliente, Historico* historico, char* cpf);
void cadastrar_produto_menu(Produto** produto, Historico* historico, char* senha, char* nome, float preco, int quantidade);
void listar_produtos_menu(Produto* produto, Historico* historico);
void remover_produto_menu(Produto** produto, Historico* historico, char* senha);
void editar_produto_menu(Produto* produto, Historico* historico, char* senha, char* nome);
int iniciar_compras_menu(NodeCliente* cliente, Historico* historico, Produto* produto, char* cpf, char* senha);
#endif