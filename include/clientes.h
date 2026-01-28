#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct Cliente{
    char* nome;
    char* cpf;
    char* telefone;
}Cliente;

typedef struct NodeCliente{
    Cliente dados;
    struct NodeCliente* prox;
}NodeCliente;

Cliente* criar_cliente(char* nome, char* cpf, char* telefone);
char* copy_string(char* string);
int ordem_alfabetica(char* string1, char* string2);
void cadastrar_cliente(NodeCliente** lista, char* nome, char* cpf, char* telefone);
void listar_clientes(NodeCliente *root);
Cliente* busca_cliente(NodeCliente *root, char* cpf);
void editar_cliente(NodeCliente *root, char* cpf);
void remover_cliente(NodeCliente **root, char* cpf);

#endif