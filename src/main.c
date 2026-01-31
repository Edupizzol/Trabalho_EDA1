#include <stdio.h>
#include <stdlib.h>
#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/carrinho.h"
#include "../include/historico.h"
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(s) Sleep(s * 1000)
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
#endif


// printf("\033[H\033[2J");
void limpar_tela() {
    fflush(stdout);
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibir_menu(){

    printf("\n");
    printf("========== MENU PRINCIPAL ==========\n");
    printf("00 : Terminar Execucao\n");
    printf("01 : Cadastrar Novo Cliente\n");
    printf("02 : Buscar Cliente\n");
    printf("03 : Editar Dados do Cliente\n");
    printf("04 : Listar Clientes\n");
    printf("05 : Deletar Cliente\n");
    printf("06 : Cadastrar Novo Produto\n");
    printf("07 : Listar Produtos\n");
    printf("08 : Remover Produto\n");
    printf("09 : Editar Produto\n");
    printf("10 : Comecar as Compras\n");
    printf("11 : Ver Historico de Operacoes\n");
    printf("===================================\n");
    printf("Escolha uma opcao: ");

}

int main(){

    NodeCliente* cliente = NULL;
    Produto* produto = NULL;
    Historico* historico = criar_historico();
    
    int n;
    char* cpf = malloc(12*sizeof(char));
    if(cpf==NULL){printf("Erro de alocacao de memoria\n");return 1;}
    char* nome = malloc(100*sizeof(char));
    if(nome==NULL){printf("Erro de alocacao de memoria\n");return 1;}
    char* senha = malloc(20*sizeof(char));
    if(senha==NULL){printf("Erro de alocacao de memoria\n");return 1;}
    
    while(1){

        exibir_menu();
        scanf("%d", &n);
        getchar();

        if(n==0){
            printf("Execucao Finalizada!\n");
            free(cpf);free(nome);free(senha);
            return 0;
        }

        switch (n)
        {
        case 1:
        {
            char* telefone =  malloc(15*sizeof(char));
            if(telefone==NULL){printf("Erro de alocacao de memoria\n");free(cpf);free(nome);free(senha);return 1;}
            char* dataDeNascimento = malloc(15*sizeof(char));
            if(dataDeNascimento==NULL){printf("Erro de alocacao de memoria\n");free(telefone);free(cpf);free(nome);free(senha);return 1;}
            char* email = malloc(100*sizeof(char));
            if(email==NULL){printf("Erro de alocacao de memoria\n");free(telefone);free(dataDeNascimento);free(cpf);free(nome);free(senha);return 1;}
            printf("Digite o Nome:\n");
            scanf("%[^\n]", nome);
            printf("Digite o CPF:\n");
            scanf("%s", cpf);
            printf("Digite o Telefone:\n");
            scanf("%s", telefone);
            printf("Digite a Senha:\n");
            scanf("%s", senha);
            printf("Digite a Data de Nascimento:\n");
            scanf(" %[^\n]", dataDeNascimento);
            printf("Digite o seu Email:\n");
            scanf(" %s", email);

            cadastrar_cliente(&cliente,nome,cpf,telefone,senha,dataDeNascimento,email);

            printf("Cliente Cadastrado!\n");
            adicionar_registro(historico, "Novo cliente cadastrado.");

            free(telefone);free(dataDeNascimento);free(email);
            SLEEP(1.5);
            limpar_tela();
            break;
        }
        case 2:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);

            busca_cliente(cliente,cpf);
            adicionar_registro(historico, "Cliente buscado.");
            SLEEP(1.5);
            limpar_tela();
            break;


        case 3:

            printf("Qual Dado Deseja Editar:\n");
            printf("1: Nome\n");
            printf("2: CPF\n");
            printf("3: Telefone\n");
            printf("4: Senha\n");
            printf("5: Data de Nascimento\n");
            printf("6: email\n");

            int numero;
            scanf("%d", &numero);
            getchar();

            printf("Digite o CPF Original do Cliente:\n");
            scanf("%s", cpf);

            int verifica = verifica_cpf(cliente,cpf);
            if(verifica == 1){
                continue;
            }

            if(numero==1){
                printf("Digite o Novo Nome:\n");
                scanf("%s", nome);
                edita_nome(cliente,nome,cpf);
            }
            else if(numero==2){
                printf("Digite o Novo CPF:\n");
                char* cpfNovo = malloc(12*sizeof(char));
                if(cpfNovo==NULL){printf("Erro de alocacao de memoria\n");break;}
                scanf("%s", cpfNovo);
                edita_cpf(cliente,cpfNovo,cpf);
                free(cpfNovo);
            }
            else if(numero==3){
                char* telefone = malloc(15*sizeof(char));
                if(telefone==NULL){printf("Erro de alocacao de memoria\n");break;}
                printf("Digite o Novo Telefone:\n");
                scanf("%s", telefone);
                edita_telefone(cliente,telefone,cpf);
                free(telefone);
            }
            else if(numero==4){
                printf("Digite a Nova Senha:\n");
                scanf("%s", senha);
                edita_senha(cliente,senha,cpf);
            }
            else if(numero==5){
                char* dataDeNascimento = malloc(15*sizeof(char));
                if(dataDeNascimento==NULL){printf("Erro de alocacao de memoria\n");break;}
                printf("Digite a Nova Data de Nascimento:\n");
                scanf("%s", dataDeNascimento);
                edita_data_de_nascimento(cliente,dataDeNascimento,cpf);
                free(dataDeNascimento);
            }
            else if(numero==6){
                char* email = malloc(100*sizeof(char));
                if(email==NULL){printf("Erro de alocacao de memoria\n");break;}
                printf("Digite o Novo email:\n");
                scanf("%s", email);
                edita_email(cliente,email,cpf);
                free(email);
            }
            printf("Dados Atualizados com Sucesso\n");
            adicionar_registro(historico, "Dados do cliente editados.");

            SLEEP(1.5);
            limpar_tela();
            break;

        case 4:
            
            if(cliente==NULL){
                printf("Nao ha clientes cadastrados!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                limpar_tela();
                break;
            } else {
                listar_clientes(cliente);
            }

            adicionar_registro(historico, "Lista de clientes exibida.");
            SLEEP(1.5);
            limpar_tela();
            break;

        case 5:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);
            remover_cliente(&cliente,cpf);

            adicionar_registro(historico, "Cliente removido.");

            SLEEP(1.5);
            limpar_tela();
            break;

        case 6:
        {
            float preco;
            int quantidade;
            
            printf("Digite o Codigo do Produto:\n");
            scanf("%s", senha);
            printf("Digite o Nome do Produto:\n");
            scanf(" %[^\n]", nome);
            printf("Digite o Preco do Produto:\n");
            scanf("%f", &preco);
            printf("Digite a Quantidade do Produto:\n");
            scanf("%d", &quantidade);
            getchar();
            produto = cadastrarProduto(produto,senha,nome,preco,quantidade);

            printf("Produto Cadastrado!\n");
            adicionar_registro(historico, "Produto cadastrado.");

            SLEEP(1.5);
            limpar_tela();
            break;
        }
        case 7:

            listarProdutos(produto);
            adicionar_registro(historico, "Lista de produtos exibida.");

            SLEEP(2.5);
            limpar_tela();
            break;

        case 8:

            printf("Digite o Codigo do Produto:\n");
            scanf("%s", senha);
            removerProduto(&produto,senha);
            adicionar_registro(historico, "Produto removido.");

            SLEEP(1.5);
            limpar_tela();
            break;

        case 9:
        {
            float preco;
            int quantidade;

            printf("Digite o Codigo do Produto!\n");
            scanf("%s", senha);

            printf("Digite o Novo Preco e o Novo Nome:\n");
            
            scanf("%f", &preco);
            getchar();
            scanf("%s", nome);
            printf("Digite a Nova Quantidade:\n");
            scanf("%d", &quantidade);

            editarDadosProduto(produto,senha,nome,preco,quantidade);

            printf("Produto Editado com Sucesso!\n");
            adicionar_registro(historico, "Dados do produto editados.");

            SLEEP(1.5);
            limpar_tela();
            free(nome);
            free(senha);
            break;
        }

        case 10:
        {
            printf("\n========== LOGIN ==========\n");
            printf("Digite o CPF do seu Usuario: ");
            scanf("%s", cpf);
            getchar();
            printf("Digite a Senha do seu Usuario: ");
            scanf("%s", senha);

            if(login(cliente,cpf,senha)==1){
                //volta pro inicio do loop
                continue;
            }

            printf("\nLogin Realizado com Sucesso!\n");

            SLEEP(1.5);
            limpar_tela();

            Carrinho *carrinho = criar_carrinho();

            NodeCliente* novo_cliente = busca_cliente(cliente,cpf);

            if(novo_cliente!=NULL){
                adicionar_dono_do_carrinho(carrinho, &(novo_cliente->dados));
            } 
            else{
                printf("Cliente Nao Existe!\n");
                free(carrinho); 
                continue;
            }

            while(3==3){

                printf("\n========== CARRINHO DE COMPRAS ==========\n");
                printf("1 : Adicionar Produtos\n");
                printf("2 : Procurar Produto\n");
                printf("3 : Remover Produtos\n");
                printf("0 : Finalizar Compras\n");
                printf("========================================\n");
                printf("Escolha uma opcao: ");
                int escolha;

                scanf("%d", &escolha);
                getchar();

                if(escolha==0){
                    printf("\nFinalizando compras...\n");

                    SLEEP(1.5);
                    limpar_tela();
                    break;
                }

                if(escolha==1){

                    printf("\n--- Adicionar ao Carrinho ---\n");
                    while(2==2){

                        printf("Produtos Disponiveis:\n");
                        listarProdutos(produto);
                        printf("Digite o Codigo (ou '0' para voltar): ");
                        scanf("%s", senha);

                        if(senha[0]=='0' && senha[1]=='\0'){
                            printf("Voltando...\n");
                            SLEEP(1.5);
                            limpar_tela();
                            break;
                        }

                        Produto* new_produto = buscarProduto(produto,senha);
                        if(new_produto!=NULL){
                            int qtd;
                            printf("Digite a Quantidade Desejada: ");
                            scanf("%d", &qtd);
                            getchar();
                            adicionar_produto_ao_carrinho(carrinho, new_produto, qtd);
                            printf("%dx Produto '%s' adicionado ao carrinho!\n\n", qtd, new_produto->nome);
                            
                            SLEEP(1.5);
                            limpar_tela();
                        } 
                        else{
                            printf("Codigo invalido! Tente novamente.\n\n");
                            SLEEP(1.5);
                            limpar_tela();
                        }

                    }

                }
                else if(escolha==2){

                    printf("\n--- Procurar Produto no Carrinho ---\n");
                    printf("Digite o Codigo do Produto: ");
                    scanf("%s", senha);
                    procura_produto_no_carrinho(carrinho,senha);

                    SLEEP(1.5);
                    limpar_tela();
                }
                else if(escolha==3){

                    printf("\n--- Remover do Carrinho ---\n");
                    while(2==2){

                        printf("Digite o Codigo (ou '0' para voltar): ");
                        scanf("%s", senha);

                        if(senha[0]=='0' && senha[1]=='\0'){
                            printf("Voltando...\n");

                            SLEEP(1.5);
                            limpar_tela();
                            break;
                        }

                        Produto* new_produto = buscarProduto(produto,senha);
                        if(new_produto!=NULL){
                            remove_produto_do_carrinho(carrinho, new_produto);
                            printf("Produto '%s' removido do carrinho!\n\n", new_produto->nome);
                            SLEEP(1.5);
                            limpar_tela();
                        } 
                        else{
                            printf("Codigo invalido! Tente novamente.\n\n");
                            SLEEP(1.5);
                            limpar_tela();
                        }

                    }

                }
            }

            printf("\n============= RESUMO DO CARRINHO =============\n");
            ver_produtos_no_carrinho(carrinho);
            printf("===============================================\n");
            free(carrinho);
            SLEEP(1.5);
            limpar_tela();

            break;
        }

        case 11:
        {
            exibir_historico(historico);
            SLEEP(3);
            limpar_tela();
            break;
        }


        default:
            break;
        }

    }
    limpar_historico(historico);
    free(historico);

    return 0;
}

