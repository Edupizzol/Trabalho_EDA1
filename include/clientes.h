#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct Cliente{
    char* nome;
    char* cpf;
    char* telefone;
    char* senha;
    char* dataDeNascimento;
    char* email;
}Cliente;

typedef struct NodeCliente{
    Cliente dados;
    struct NodeCliente* prox;
}NodeCliente;

Cliente* criar_cliente(char* nome, char* cpf, char* telefone, char* senha, char* dataDeNascimento, char* email);
int login(NodeCliente* root, char* nome, char* senha);
char* copy_string(char* string);
int ordem_alfabetica(char* string1, char* string2);
int compara_strings(char* string1, char* string2);
void cadastrar_cliente(NodeCliente** lista, char* nome, char* cpf, char* telefone, char* senha, char* dataDeNascimento, char* email);
void listar_clientes(NodeCliente *root);
NodeCliente* busca_cliente(NodeCliente *root, char* cpf);
void remover_cliente(NodeCliente **root, char* cpf);
void salvar_clientes(NodeCliente *root, const char *filename);

#endif