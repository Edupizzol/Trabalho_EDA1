#include <stdio.h>
#include <stdlib.h>
#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/carrinho.h"

void exibir_menu(){

    printf("00 : Terminar Execução\n");
    printf("01 : Cadastrar Novo Cliente\n");
    printf("02 : Buscar Cliente\n");
    printf("03 : Editar Dados do Cliente:\n");
    printf("04 : Listar Clientes\n");
    printf("05 : Deletar Cliente\n");
    printf("06 : Cadastrar Novo Produto\n");
    printf("07 : Listar Produtos\n");
    printf("08 : Remover Produto\n");
    printf("09 : Editar Produto\n");
    printf("10 : Começar as Compras\n");

}

int main(){

    NodeCliente* cliente = NULL;
    Produto* produto = NULL;

    int n;
    char* cpf = malloc(12*sizeof(char));
    if(cpf==NULL){printf("Erro de alocação de memória\n");return 1;}
    char* nome = malloc(100*sizeof(char));
    if(nome==NULL){printf("Erro de alocação de memória\n");return 1;}
    char* senha = malloc(20*sizeof(char));
    if(senha==NULL){printf("Erro de alocação de memória\n");return 1;}
    
    while(1){

        exibir_menu();
        scanf("%d", &n);
        getchar();

        if(n==0){
            printf("Execução Finalizada!\n");
            free(cpf);free(nome);free(senha);
            return 0;
        }

        switch (n)
        {
        case 1:

            char* telefone =  malloc(15*sizeof(char));
            if(telefone==NULL){printf("Erro de alocação de memória\n");free(cpf);free(nome);free(senha);return 1;}
            char* dataDeNascimento = malloc(15*sizeof(char));
            if(dataDeNascimento==NULL){printf("Erro de alocação de memória\n");free(telefone);free(cpf);free(nome);free(senha);return 1;}
            char* email = malloc(100*sizeof(char));
            if(email==NULL){printf("Erro de alocação de memória\n");free(telefone);free(dataDeNascimento);free(cpf);free(nome);free(senha);return 1;}

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

            free(telefone);free(dataDeNascimento);free(email);

            break;

        case 2:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);

            busca_cliente(cliente,cpf);

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
                if(cpfNovo==NULL){printf("Erro de alocação de memória\n");break;}
                scanf("%s", cpfNovo);
                edita_cpf(cliente,cpfNovo,cpf);
                free(cpfNovo);
            }
            else if(numero==3){
                char* telefone = malloc(15*sizeof(char));
                if(telefone==NULL){printf("Erro de alocação de memória\n");break;}
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
                if(dataDeNascimento==NULL){printf("Erro de alocação de memória\n");break;}
                printf("Digite a Nova Data de Nascimento:\n");
                scanf("%s", dataDeNascimento);
                edita_data_de_nascimento(cliente,dataDeNascimento,cpf);
                free(dataDeNascimento);
            }
            else if(numero==6){
                char* email = malloc(100*sizeof(char));
                if(email==NULL){printf("Erro de alocação de memória\n");break;}
                printf("Digite o Novo email:\n");
                scanf("%s", email);
                edita_email(cliente,email,cpf);
                free(email);
            }
            printf("Dados Atualizados com Sucesso\n");

            break;

        case 4:

            listar_clientes(cliente);

            break;

        case 5:

            printf("Digite o CPF do Cliente:\n");
            scanf("%s", cpf);
            remover_cliente(&cliente,cpf);

            printf("Cliente Eliminado!\n");

            break;

        case 6:

            float preco;
            
            printf("Digite o Código do Produto:\n");
            scanf("%s", senha);
            printf("Digite o Nome do Produto:\n");
            scanf(" %[^\n]", nome);
            printf("Digite o Preco do Produto:\n");
            scanf("%f", &preco);
            getchar();
            produto = cadastrarProduto(produto,senha,nome,preco);

            printf("Produto Cadastrado!\n");

            break;

        case 7:

            listarProdutos(produto);

            break;

        case 8:

            printf("Digite o Código do Produto:\n");
            scanf("%s", senha);
            removerProduto(&produto,senha);

            printf("Produto Removido!\n");

            break;

        case 9:

            printf("Digite o Código do Produto!\n");
            scanf("%s", senha);

            printf("Digite o Novo Preco e o Novo Nome:\n");
            
            scanf("%f", &preco);
            getchar();
            scanf("%s", nome);

            editarDadosProduto(produto,senha,nome,preco);

            printf("Produto Editado com Sucesso!\n");

        default:
            break;
        }

        if(n==10){

            printf("Digite o CPF do seu Usuário!\n");
            scanf("%s", cpf);
            getchar();
            printf("Digite a Senha do seu Usuário:\n");
            scanf("%s", senha);

            if(login(cliente,cpf,senha)==1){
                //volta pro inicio do loop
                continue;
            }

            printf("Login Realizado!\n");

            Carrinho *carrinho = criar_carrinho();

            NodeCliente* novo_cliente = busca_cliente(cliente,cpf);

            if(novo_cliente!=NULL){
                adicionar_dono_do_carrinho(carrinho, &(novo_cliente->dados));
            } 
            else{
                printf("Cliente Nao Existe!");
                free(carrinho); 
                continue;
            }

            while(3==3){

                printf("O que Deseja Fazer:\n");
                printf("0 : Fechar Aba\n");
                printf("1 : Adicionar Produtos no Carrinho:\n");
                printf("2 : Procurar Produto no Carrinho:\n");
                printf("3 : Remover Produtos no Carrinho:\n");
                int escolha;

                scanf("%d", &escolha);
                getchar();

                if(escolha==0){
                    printf("Fechando\n");
                    break;
                }

                if(escolha==1){

                    while(2==2){

                        printf("Insira o Código do Produto que Voce Deseja Adicionar ao Carrinho ou 0 Para Fechar esse Menu\n");
                        listarProdutos(produto);
                        scanf("%s", senha);

                        if(senha[0]=='0' && senha[1]=='\0'){
                            break;
                        }

                        Produto* new_produto = buscarProduto(produto,senha);
                        if(new_produto!=NULL){
                            adicionar_produto_ao_carrinho(carrinho, new_produto);
                            printf("Produto %s adicionado!\n", new_produto->nome);
                        } 
                        else{
                            printf("Código inválido! Tente novamente.\n");
                        }

                    }

                }
                else if(escolha==2){

                    printf("Insira o Código do Produto que Voce Deseja Buscar no Carrinho\n");
                    scanf("%s", senha);
                    procura_produto_no_carrinho(carrinho,senha);

                }
                else if(escolha==3){

                    while(2==2){

                        printf("Insira o Código do Produto que Voce Deseja Remover do Carrinho ou 0 Para Fechar esse Menu\n");
                        scanf("%s", senha);

                        if(senha[0]=='0' && senha[1]=='\0'){
                            break;
                        }

                        Produto* new_produto = buscarProduto(produto,senha);
                        if(new_produto!=NULL){
                            remove_produto_do_carrinho(carrinho, new_produto);
                            printf("Produto %s removido!\n", new_produto->nome);
                        } 
                        else{
                            printf("Código inválido! Tente novamente.\n");
                        }

                    }

                }
            }

            printf("Dados do Carrinho:\n");
            ver_produtos_no_carrinho(carrinho);
            free(carrinho);

        }

    }

    return 0;
}

