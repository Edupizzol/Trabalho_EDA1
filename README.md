# Trabalho EDA1 

## Descrição
Este projeto implementa um sistema de gerenciamento de clientes e produtos utilizando **listas encadeadas** em C.  
O sistema oferece funcionalidades básicas de **CRUD** (Criar, Ler, Atualizar e Deletar) para clientes, produtos e carrinhos de compra, operando diretamente no terminal.

---

## Funcionalidades

### Gerenciamento de Clientes
- Cadastrar cliente (nome, CPF e telefone)
- Listar todos os clientes
- Buscar cliente pelo CPF
- Editar dados de um cliente
- Remover cliente
- Mantém os clientes **ordenados alfabeticamente pelo nome**

### Gerenciamento de Produtos
- Cadastrar produto (código único, nome e preço)
- Listar todos os produtos
- Buscar produto pelo código
- Editar dados do produto
- Remover produto

### Modo Compra
- Permite que um cliente adicione produtos no carrinho
- Listar produtos no carrinho
- Remover produtos do carrinho

---

## Estrutura do Projeto
<pre>
├── README.md
├── include
│   ├── carrinho.h
│   ├── clientes.h
│   └── produtos.h
└── src
    ├── carrinho.c
    ├── clientes.c
    ├── main
    ├── main.c
    └── produtos.c
</pre>

## Como Rodar
<pre>
gcc main.c clientes.c produtos.c carrinho.c -o programa
./programa
</pre>

