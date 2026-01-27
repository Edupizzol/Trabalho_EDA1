typedef struct Cliente{
    char* nome;
    char* cpf;
    char* telefone;
}Cliente;

typedef struct NodeCliente{
    Cliente dados;
    struct NodeCliente* prox;
}NodeCliente;

