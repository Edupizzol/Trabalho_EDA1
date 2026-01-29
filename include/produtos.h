#ifndef PRODUTOS_H
#define PRODUTOS_H
typedef struct Produto{

    char* codigo;
    char* nome;
    float preco;
    int quantidade;
    struct Produto* next;
}Produto;

Produto* cadastrarProduto(Produto*head, char* codigo, char* nome, float preco, int quantidade);
void listarProdutos(Produto* head);
Produto* buscarProduto(Produto* head, char* codigo);
void editarDadosProduto(Produto* head, char* codigo, char* novoNome, float novoPreco, int novaQuantidade);
void removerProduto(Produto** head, char* codigo);
void incrementarEstoque(Produto* produto, int quantidade);
void decrementarEstoque(Produto* produto, int quantidade);
#endif