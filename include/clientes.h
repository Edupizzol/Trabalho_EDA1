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
int login(NodeCliente* root, char* cpf, char* senha);
char* copy_string(char* string);
int ordem_alfabetica(char* string1, char* string2);
int compara_strings(char* string1, char* string2);
void cadastrar_cliente(NodeCliente** lista, char* nome, char* cpf, char* telefone, char* senha, char* dataDeNascimento, char* email);
void listar_clientes(NodeCliente *root);
NodeCliente* busca_cliente(NodeCliente *root, char* cpf);
void remover_cliente(NodeCliente **root, char* cpf);
void edita_nome(NodeCliente* root, char* nome, char* cpf);
void edita_cpf(NodeCliente* root, char* cpfnovo, char* cpfantigo);
void edita_telefone(NodeCliente* root, char* telefone, char* cpf);
void edita_senha(NodeCliente* root, char* senha, char* cpf);
void edita_data_de_nascimento(NodeCliente* root, char* dataDeNascimento, char* cpf);
void edita_email(NodeCliente* root, char* email, char* cpf);
int verifica_cpf(NodeCliente* root, char* string);
void liberar_todos_clientes(NodeCliente** root);

#endif