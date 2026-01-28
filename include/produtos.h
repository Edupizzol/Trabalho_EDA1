#ifndef PRODUTOS_H
#define PRODUTOS_H
typedef struct Produto{

    char* codigo;
    char* nome;
    float preco;
    struct Produto* next;
}Produto;

Produto* cadastrarProduto(Produto*head, char* codigo, char* nome, float preco);
void listarProdutos(Produto* head);
Produto* buscarProduto(Produto* head, char* codigo);
void editarDadosProduto(Produto* head, char* codigo, char* novoNome, float novoPreco);
void removerProduto(Produto** head, char* codigo);

#endif