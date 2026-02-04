#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

static const char* CLIENTES_FILE = "clientes.csv";
static const char* PRODUTOS_FILE = "produtos.csv";

#define VERDE "\x1b[32m"
#define RESET "\x1b[0m"

// printf("\033[H\033[2J");
void limpar_tela() {
    fflush(stdout);
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

static void aguardar_enter_e_limpar() {
    printf(VERDE "\nPressione Enter para continuar..." RESET);
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    limpar_tela();
}

void exibir_menu(){

    printf(VERDE "\n" RESET);
    printf(VERDE "========== MENU PRINCIPAL ==========\n" RESET);
    printf(VERDE "00 : Terminar Execucao\n" RESET);
    printf(VERDE "01 : Cadastrar Novo Cliente\n" RESET);
    printf(VERDE "02 : Buscar Cliente\n" RESET);
    printf(VERDE "03 : Editar Dados do Cliente\n" RESET);
    printf(VERDE "04 : Listar Clientes\n" RESET);
    printf(VERDE "05 : Deletar Cliente\n" RESET);
    printf(VERDE "06 : Cadastrar Novo Produto\n" RESET);
    printf(VERDE "07 : Listar Produtos\n" RESET);
    printf(VERDE "08 : Remover Produto\n" RESET);
    printf(VERDE "09 : Editar Produto\n" RESET);
    printf(VERDE "10 : Comecar as Compras\n" RESET);
    printf(VERDE "11 : Ver Historico de Operacoes\n" RESET);
    printf(VERDE "===================================\n" RESET);
    printf(VERDE "Escolha uma opcao: " RESET);

}

int menu(){

    NodeCliente* cliente = carregar_clientes(CLIENTES_FILE);
    Produto* produto = carregar_produtos(PRODUTOS_FILE);
    Historico* historico = criar_historico();
    
    int n, quantidade;
    float preco;
    char* cpf = malloc(12*sizeof(char));
    if(cpf==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    char* nome = malloc(100*sizeof(char));
    if(nome==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    char* senha = malloc(20*sizeof(char));
    if(senha==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    char* telefone =  malloc(15*sizeof(char));
    if(telefone==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    char* dataDeNascimento = malloc(15*sizeof(char));
    if(dataDeNascimento==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    char* email = malloc(100*sizeof(char));
    if(email==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
    
    while(1){
        exibir_menu();
        scanf("%d", &n);
        getchar();

        switch (n)
        {
        case 0:
            printf(VERDE "Execucao Finalizada!\n" RESET);
            salvar_clientes(cliente, CLIENTES_FILE);
            salvar_produtos(produto, PRODUTOS_FILE);
            limpar_historico(historico);
            free(historico);
            liberar_todos_clientes(&cliente);
            liberar_todos_produtos(&produto);
            free(cpf);free(nome);free(senha);free(telefone);free(dataDeNascimento);free(email);
            return 0;
        case 1:
            cadastra_cliente_menu(&cliente, historico, nome, cpf, senha, telefone ,dataDeNascimento, email);
            break;
        case 2:
            busca_cliente_menu(cliente, historico, cpf);
            break;
        case 3:
            if(edita_cliente_menu(cliente, historico, nome, cpf, senha, dataDeNascimento, email) == 1){
                continue;
            }
            break;
        case 4:
            listar_clientes_menu(cliente, historico);
            break;
        case 5:
            deletar_clientes_menu(&cliente, historico, cpf);
            break;
        case 6:
            cadastrar_produto_menu(&produto, historico, senha, nome, preco, quantidade);
            break;
        case 7:
            listar_produtos_menu(produto,historico);
            break;
        case 8:
            remover_produto_menu(&produto, historico, senha);
            break;
        case 9:
            editar_produto_menu(produto, historico, senha, nome);
            break;
        case 10:
            if(iniciar_compras_menu(cliente, historico, produto, cpf, senha) == 1){
                continue;
            }
            break;
        case 11:
            exibir_historico(historico);
            aguardar_enter_e_limpar();
            break;
        default:
            printf(VERDE "Opcao Invalida! Tente Novamente.\n" RESET);
            aguardar_enter_e_limpar();
            break;
        }

    }

    return 0;
}

void finalizar(NodeCliente* cliente, Produto* produto, Historico* historico, char* cpf, char* nome, char* senha){
    return;
}

void cadastra_cliente_menu(NodeCliente** cliente, Historico* historico, char* nome, char* cpf, char* senha, char* telefone, char* dataDeNascimento, char* email){

    printf(VERDE "Digite o Nome:\n" RESET);
    scanf(" %99[^\n]", nome);
    getchar();
    printf(VERDE "Digite o CPF (11 digitos):\n" RESET);
    scanf("%11s", cpf);
    getchar();
    
    if(verifica_cpf(*cliente, cpf) == 0){
        printf(VERDE "Erro: CPF ja cadastrado!\n" RESET);
        aguardar_enter_e_limpar();
        return;
    }
    
    printf(VERDE "Digite o Telefone:\n" RESET);
    scanf("%14s", telefone);
    getchar();
    printf(VERDE "Digite a Senha:\n" RESET);
    scanf("%19s", senha);
    getchar();
    printf(VERDE "Digite a Data de Nascimento (DD/MM/AAAA):\n" RESET);
    scanf(" %14[^\n]", dataDeNascimento);
    getchar();
    printf(VERDE "Digite o seu Email:\n" RESET);
    scanf("%99s", email);
    getchar();

    cadastrar_cliente(cliente,nome,cpf,telefone,senha,dataDeNascimento,email);
    salvar_clientes(*cliente, CLIENTES_FILE);

    printf(VERDE "Cliente Cadastrado!\n" RESET);
    adicionar_registro(historico, "Novo cliente cadastrado.");

    aguardar_enter_e_limpar();
}

void busca_cliente_menu(NodeCliente* cliente, Historico* historico, char* cpf){
    printf(VERDE "Digite o CPF do Cliente:\n" RESET);
    scanf("%s", cpf);
    getchar();
    
    NodeCliente* encontrado = busca_cliente(cliente,cpf);
    if(encontrado != NULL){
        adicionar_registro(historico, "Cliente buscado.");
    }
    
    aguardar_enter_e_limpar();
}

int edita_cliente_menu(NodeCliente* cliente, Historico* historico, char* nome, char* cpf, char* senha, char* dataDeNascimento, char* email){

    printf(VERDE "Qual Dado Deseja Editar:\n" RESET);
            printf(VERDE "1: Nome\n" RESET);
            printf(VERDE "2: CPF\n" RESET);
            printf(VERDE "3: Telefone\n" RESET);
            printf(VERDE "4: Senha\n" RESET);
            printf(VERDE "5: Data de Nascimento\n" RESET);
            printf(VERDE "6: email\n" RESET);

            int numero;
            scanf("%d", &numero);
            getchar();

            printf(VERDE "Digite o CPF Original do Cliente:\n" RESET);
            scanf("%s", cpf);

            int verifica = verifica_cpf(cliente,cpf);
            if(verifica == 1){
                return 1;
            }

            if(numero==1){
                printf(VERDE "Digite o Novo Nome:\n" RESET);
                scanf("%s", nome);
                edita_nome(cliente,nome,cpf);
            }
            else if(numero==2){
                printf(VERDE "Digite o Novo CPF:\n" RESET);
                char* cpfNovo = malloc(12*sizeof(char));
                if(cpfNovo==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
                scanf("%s", cpfNovo);
                edita_cpf(cliente,cpfNovo,cpf);
                free(cpfNovo);
            }
            else if(numero==3){
                char* telefone = malloc(15*sizeof(char));
                if(telefone==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
                printf(VERDE "Digite o Novo Telefone:\n" RESET);
                scanf("%s", telefone);
                edita_telefone(cliente,telefone,cpf);
                free(telefone);
            }
            else if(numero==4){
                printf(VERDE "Digite a Nova Senha:\n" RESET);
                scanf("%s", senha);
                edita_senha(cliente,senha,cpf);
            }
            else if(numero==5){
                char* dataDeNascimento = malloc(15*sizeof(char));
                if(dataDeNascimento==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
                printf(VERDE "Digite a Nova Data de Nascimento:\n" RESET);
                scanf("%s", dataDeNascimento);
                edita_data_de_nascimento(cliente,dataDeNascimento,cpf);
                free(dataDeNascimento);
            }
            else if(numero==6){
                char* email = malloc(100*sizeof(char));
                if(email==NULL){printf(VERDE "Erro de alocacao de memoria\n" RESET);return 1;}
                printf(VERDE "Digite o Novo email:\n" RESET);
                scanf("%s", email);
                edita_email(cliente,email,cpf);
                free(email);
            }
            salvar_clientes(cliente, CLIENTES_FILE);
            printf(VERDE "Dados Atualizados com Sucesso\n" RESET);
            adicionar_registro(historico, "Dados do cliente editados.");

            aguardar_enter_e_limpar();
            return 0;
}

void listar_clientes_menu(NodeCliente* cliente, Historico* historico){
    if(cliente==NULL){
        printf(VERDE "Nao ha clientes cadastrados!\n" RESET);
        printf(VERDE "\nPressione Enter para continuar..." RESET);
        getchar();
        limpar_tela();
        return;
    } 
    else{
        listar_clientes(cliente);
    }

    adicionar_registro(historico, "Lista de clientes exibida.");
    aguardar_enter_e_limpar();
    return;
}

void deletar_clientes_menu(NodeCliente** cliente, Historico* historico, char* cpf){
    printf(VERDE "Digite o CPF do Cliente:\n" RESET);
    scanf("%s", cpf);
    getchar();
    
    if(remover_cliente(cliente,cpf)){
        salvar_clientes(*cliente, CLIENTES_FILE);
        adicionar_registro(historico, "Cliente removido.");
    }

    aguardar_enter_e_limpar();
    return;
}

void cadastrar_produto_menu(Produto** produto, Historico* historico, char* senha, char* nome, float preco, int quantidade){
    
    printf(VERDE "Digite o Codigo do Produto:\n" RESET);
    scanf("%s", senha);
    printf(VERDE "Digite o Nome do Produto:\n" RESET);
    scanf(" %[^\n]", nome);
    printf(VERDE "Digite o Preco do Produto:\n" RESET);
    scanf("%f", &preco);
    printf(VERDE "Digite a Quantidade do Produto:\n" RESET);
    scanf("%d", &quantidade);
    getchar();
    *produto = cadastrarProduto(*produto,senha,nome,preco,quantidade);
    salvar_produtos(*produto, PRODUTOS_FILE);

    printf(VERDE "Produto Cadastrado!\n" RESET);
    adicionar_registro(historico, "Produto cadastrado.");

    aguardar_enter_e_limpar();
    return;
}

void listar_produtos_menu(Produto* produto, Historico* historico){
    listarProdutos(produto);
    adicionar_registro(historico, "Lista de produtos exibida.");

    aguardar_enter_e_limpar();
    return;
}

void remover_produto_menu(Produto** produto, Historico* historico, char* senha){
    printf(VERDE "Digite o Codigo do Produto:\n" RESET);
    scanf("%s", senha);
    getchar();
    
    if(removerProduto(produto,senha)){
        salvar_produtos(*produto, PRODUTOS_FILE);
        adicionar_registro(historico, "Produto removido.");
    }

    aguardar_enter_e_limpar();
    return;
}

void editar_produto_menu(Produto* produto, Historico* historico, char* senha, char* nome){
    float preco;
    int quantidade;

    printf(VERDE "Digite o Codigo do Produto!\n" RESET);
    scanf("%s", senha);

    printf(VERDE "Digite o Novo Preco e o Novo Nome:\n" RESET);
    
    scanf("%f", &preco);
    getchar();
    scanf("%s", nome);
    printf(VERDE "Digite a Nova Quantidade:\n" RESET);
    scanf("%d", &quantidade);

    editarDadosProduto(produto,senha,nome,preco,quantidade);
    salvar_produtos(produto, PRODUTOS_FILE);

    printf(VERDE "Produto Editado com Sucesso!\n" RESET);
    adicionar_registro(historico, "Dados do produto editados.");

    aguardar_enter_e_limpar();
    return;
}

int iniciar_compras_menu(NodeCliente* cliente, Historico* historico, Produto* produto, char* cpf, char* senha){
    
    printf(VERDE "\n========== LOGIN ==========\n" RESET);
    printf(VERDE "Digite o CPF do seu Usuario: " RESET);
    scanf("%s", cpf);
    getchar();
    printf(VERDE "Digite a Senha do seu Usuario: " RESET);
    scanf("%s", senha);

    if(login(cliente,cpf,senha)==1){
        return 1;
    }

    printf(VERDE "\nLogin Realizado com Sucesso!\n" RESET);
    adicionar_registro(historico, "Usuario fez login no modo compra.");

    aguardar_enter_e_limpar();

    Carrinho *carrinho = criar_carrinho();

    NodeCliente* novo_cliente = busca_cliente(cliente,cpf);

    if(novo_cliente!=NULL){
        adicionar_dono_do_carrinho(carrinho, &(novo_cliente->dados));
    } 
    else{
        printf(VERDE "Cliente Nao Existe!\n" RESET);
        free(carrinho); 
        return 1;
    }

    while(2==2){

        printf(VERDE "\n========== CARRINHO DE COMPRAS ==========\n" RESET);
        printf(VERDE "1 : Adicionar Produtos\n" RESET);
        printf(VERDE "2 : Procurar Produto\n" RESET);
        printf(VERDE "3 : Remover Produtos\n" RESET);
        printf(VERDE "0 : Finalizar Compras\n" RESET);
        printf(VERDE "========================================\n" RESET);
        printf(VERDE "Escolha uma opcao: " RESET);
        int escolha;

        scanf("%d", &escolha);
        getchar();

        if(escolha==0){
            printf(VERDE "\nFinalizando compras...\n" RESET);
            adicionar_registro(historico, "Compras finalizadas.");

            aguardar_enter_e_limpar();
            break;
        }

        if(escolha==1){

            printf(VERDE "\n--- Adicionar ao Carrinho ---\n" RESET);
            while(2==2){

                printf(VERDE "Produtos Disponiveis:\n" RESET);
                listarProdutos(produto);
                printf(VERDE "Digite o Codigo (ou '0' para voltar): " RESET);
                scanf("%s", senha);

                if(senha[0]=='0' && senha[1]=='\0'){
                    printf(VERDE "Voltando...\n" RESET);
                    aguardar_enter_e_limpar();
                    break;
                }

                Produto* new_produto = buscarProduto(produto,senha);
                if(new_produto!=NULL){
                    int qtd;
                    printf(VERDE "Digite a Quantidade Desejada: " RESET);
                    scanf("%d", &qtd);
                    getchar();
                    if(adicionar_produto_ao_carrinho(carrinho, new_produto, qtd)){
                        printf(VERDE "%dx Produto '%s' adicionado ao carrinho!\n\n" RESET, qtd, new_produto->nome);
                        adicionar_registro(historico, "Produto adicionado ao carrinho.");
                        salvar_produtos(produto, PRODUTOS_FILE);
                    }
                    
                    aguardar_enter_e_limpar();
                } 
                else{
                    printf(VERDE "Codigo invalido! Tente novamente.\n\n" RESET);
                    aguardar_enter_e_limpar();
                }

            }

        }
        else if(escolha==2){

            printf(VERDE "\n--- Procurar Produto no Carrinho ---\n" RESET);
            printf(VERDE "Digite o Codigo do Produto: " RESET);
            scanf("%s", senha);
            Produto* encontrado = procura_produto_no_carrinho(carrinho,senha);
            if(encontrado != NULL){
                printf(VERDE "Produto encontrado!\n" RESET);
                printf(VERDE "Codigo: %s\nNome: %s\nPreco: %.2f\nQuantidade: %d\n" RESET, 
                       encontrado->codigo, encontrado->nome, encontrado->preco, encontrado->quantidade);
                adicionar_registro(historico, "Produto buscado no carrinho.");
            } else {
                printf(VERDE "Produto nao encontrado no carrinho!\n" RESET);
            }

            aguardar_enter_e_limpar();
        }
        else if(escolha==3){

            printf(VERDE "\n--- Remover do Carrinho ---\n" RESET);
            while(2==2){

                printf(VERDE "Digite o Codigo (ou '0' para voltar): " RESET);
                scanf("%s", senha);

                if(senha[0]=='0' && senha[1]=='\0'){
                    printf(VERDE "Voltando...\n" RESET);

                    aguardar_enter_e_limpar();
                    break;
                }

                Produto* produto_carrinho = procura_produto_no_carrinho(carrinho, senha);
                if(produto_carrinho!=NULL){
                    int qtd_remover;
                    printf(VERDE "Quantidade no carrinho: %d\n" RESET, produto_carrinho->quantidade);
                    printf(VERDE "Digite a Quantidade a Remover: " RESET);
                    scanf("%d", &qtd_remover);
                    getchar();

                    Produto* new_produto = buscarProduto(produto, senha);
                    if(remove_produto_do_carrinho(carrinho, new_produto, qtd_remover) != NULL){
                        printf(VERDE "\n" RESET);
                        adicionar_registro(historico, "Produto removido do carrinho.");
                        salvar_produtos(produto, PRODUTOS_FILE);
                    }

                    aguardar_enter_e_limpar();
                } 
                else{
                    printf(VERDE "Codigo invalido! Tente novamente.\n\n" RESET);
                    aguardar_enter_e_limpar();
                }

            }

        }
    }

    printf(VERDE "\n============================ RESUMO DO CARRINHO ============================\n" RESET);
    ver_produtos_no_carrinho(carrinho);
    printf(VERDE "=============================================================================\n" RESET);
    liberar_carrinho(&carrinho);
    aguardar_enter_e_limpar();

    return 0;
}
