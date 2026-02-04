# Trabalho EDA1 

![C](https://img.shields.io/badge/%20-C-00599C?style=for-the-badge&logo=probot&logoColor=white&labelColor=555555)
![EDA1](https://img.shields.io/badge/Conceito-EDA1-FF6B6B?style=for-the-badge&logo=databricks&logoColor=white)
![Status](https://img.shields.io/badge/Status-Concluído-success?style=for-the-badge&logo=checkmarx&logoColor=white)

## Descrição
Este projeto implementa um sistema de gerenciamento de clientes e produtos utilizando **listas encadeadas** em C.  
O sistema oferece funcionalidades básicas de **CRUD** (Criar, Ler, Atualizar e Deletar) para clientes, produtos e carrinhos de compra, operando diretamente no terminal.

---

## Funcionalidades

### Gerenciamento de Clientes
- Cadastrar `cliente` (nome, CPF e telefone)
- Listar todos os `clientes`
- Buscar `cliente` pelo CPF
- Editar dados de um `cliente`
- Remover `cliente`
- Mantém os `clientes` **ordenados alfabeticamente pelo nome**

### Gerenciamento de Produtos
- Cadastrar `produto` (código único, nome, preço e quantidade)
- Listar todos os `produtos`
- Buscar `produto` pelo seu código
- Editar dados do `produto`
- Remover `produto`

### Modo Compra
- Permite que um `cliente` adicione `produtos` no `carrinho`
- Listar produtos no `carrinho`
- Remover produtos do `carrinho`

### Histórico de Operações
- Lista e atualiza todas as opções escolhidas até o término do programa
- Os `registros` são acompanhados de "TimeStamps" e um contador de operações realizadas

### Persistência de dados
- Armazena os cadastros de `clientes e produtos` em um `CSV`
- Toda vez que fechar a aplicação os dados ainda estarão intactos (a não ser que o `hard reset` seja utilizado)

### Hard Reset (Reiniciar aplicação)
- Libera todos os `clientes` e `produtos` da aplicação
- Depois apaga todos os dados salvos pela persistência
- Inicializa os `CSV` sem nada salvo

---

## Estrutura do Projeto
<pre>
├── README.md
├── clientes.csv
├── produtos.csv
├── include
│   ├── carrinho.h
│   ├── clientes.h
│   ├── historico.h
│   ├── menu.h
│   ├── produtos.h
│   └── salvamento.h
└── src
    ├── carrinho.c
    ├── clientes.c
    ├── historico.c
    ├── main.c
    ├── menu.c
    ├── produtos.c
    └── salvamento.c
</pre>

## Requisitos
- **Compilador C** (GCC, Clang ou compatível)
- **Sistema Operacional**: Windows, Linux ou macOS

## Como Rodar

```bash
gcc src/*.c -I include -o programa.exe
./programa.exe
```

## Autores
Desenvolvido por Eduardo Jesus e Matheus Moretti Soares como trabalho prático da disciplina **EDA1** - Estrutura de Dados 1

* Sinta-se à vontade para sugestões ou reports no código!