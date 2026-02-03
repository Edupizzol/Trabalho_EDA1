#include "../include/clientes.h"
#include <stdio.h>
#include <stdlib.h>

char* copy_string(char* string){
    
    int i=0;
    int memory_size=0;
    char* new_string = NULL;

    while(string[i]!='\0'){

        if(i==memory_size){

            memory_size+=10;

            char* temp = realloc(new_string,memory_size*sizeof(char));
            if(temp==NULL){
                printf("Erro durante a alocação de memória do nome do cliente!\n");
                exit(EXIT_FAILURE);
            }

            new_string = temp;

            }

        new_string[i]=string[i];
        i++;

    }

    char* temp = realloc(new_string,i+1);
    if(temp==NULL){
        printf("Erro durante a alocação de memória do nome do cliente!\n");
        exit(EXIT_FAILURE);
    }
    new_string = temp;
    
    new_string[i]='\0';
    return new_string;

}

void vira_maiuscula(char* string){
    
    if(string == NULL) return;
    
    int i = 0;
    while(string[i] != '\0'){
        if(string[i] >= 'a' && string[i] <= 'z'){
            string[i] -= 32;
        }
        i++;
    }
}

int ordem_alfabetica(char* string1, char* string2){

    int i=0;
    
    while(string1[i]!='\0' && string2[i]!='\0'){

        char c1 = string1[i];
        char c2 = string2[i];

        if(c1 != c2){
            if(c1 < c2){
                return 1;
            }
            else if(c1 > c2){
                return 2;
            }
        }

        i++;

    }

    if(string1[i] == '\0' && string2[i] != '\0') return 1;
    if(string2[i] == '\0' && string1[i] != '\0') return 2;

    return 0;

}

int compara_strings(char* string1, char* string2){

    int i=0;
    while(string1[i]!='\0' && string2[i]!='\0'){
        if(string1[i]!=string2[i]){
            return 1;
        }
        i++;
    }

    if(string1[i] != string2[i]){
        return 1;
    }

    return 0;

}

Cliente* criar_cliente(char* nome, char* cpf, char* telefone, char* senha, char* dataDeNascimento, char* email){

    Cliente* new_cliente = malloc(sizeof(Cliente));
    if(new_cliente==NULL){
        printf("Erro ao alocar memória para Cliente!");
        exit(EXIT_FAILURE);
    }

    new_cliente->cpf = copy_string(cpf);
    new_cliente->nome = copy_string(nome);
    vira_maiuscula(new_cliente->nome); 
    new_cliente->telefone = copy_string(telefone);
    new_cliente->senha = copy_string(senha);
    new_cliente->dataDeNascimento = copy_string(dataDeNascimento);
    new_cliente->email = copy_string(email);

    return new_cliente;
    
}

void cadastrar_cliente(NodeCliente** lista, char* nome, char* cpf, char* telefone, char* senha, char* dataDeNascimento, char* email){

    Cliente* new_cliente = criar_cliente(nome,cpf,telefone,senha,dataDeNascimento,email);
    NodeCliente* new_node = malloc(sizeof(NodeCliente));

    if(new_node==NULL){
        printf("Erro ao alocar memória para o nó do Cliente!\n");
        exit(EXIT_FAILURE);
    }

    new_node->dados = *new_cliente;
    new_node->prox = NULL;

    free(new_cliente);

    if(*lista==NULL){
        *lista = new_node;
        return;
    }

    if(ordem_alfabetica(new_node->dados.nome,(*lista)->dados.nome)==1){
        new_node->prox = *lista;
        *lista = new_node;
        return;
    }

    //percorre a lista pra encontrar posicao correta
    NodeCliente* atual = *lista;
    while(atual->prox != NULL && ordem_alfabetica(new_node->dados.nome, atual->prox->dados.nome) != 1){
        atual = atual->prox;
    }

    new_node->prox = atual->prox;
    atual->prox = new_node;
    
}

int login(NodeCliente* root, char* cpf, char* senha){

    while(root!=NULL){
        if(compara_strings(cpf,root->dados.cpf)==0){
            if(compara_strings(senha,root->dados.senha)==0){
                printf("Logado!\n");
                return 0;
            }
            else{
                printf("Senha incorreta!\n");
                return 1;
            }
        }
        root=root->prox;
    }

    printf("Cliente nao encontrado!\n");
    return 1;

}

void listar_clientes(NodeCliente *root){

    if(root==NULL){
        printf("Nao ha clientes cadastrados!\n");
        return;
    }
    NodeCliente* atual = root;

    while(atual!=NULL){

        if(atual->dados.nome == NULL || atual->dados.cpf == NULL){
            printf("ERRO: Dados do cliente incompletos.\n");
            break;
        }
        printf("---------------------------------------\n");
        printf("Nome: %s\n", atual->dados.nome);
        printf("CPF: %s\n", atual->dados.cpf);
        printf("Telefone: %s\n", atual->dados.telefone);
        printf("Data de Nascimento: %s\n", atual->dados.dataDeNascimento);
        printf("Email: %s\n", atual->dados.email);
        printf("---------------------------------------\n");
        atual=atual->prox;

    }

    return;

}

NodeCliente* busca_cliente(NodeCliente *root, char* cpf){

    if(root==NULL){
        printf("Nao ha clientes cadastrados!\n");
        return NULL;
    }

    NodeCliente* atual = root;

    while(atual!=NULL){
        if(compara_strings(atual->dados.cpf,cpf)==0){
            printf("-------Dados do Cliente-------\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("CPF: %s\n", atual->dados.cpf);
            printf("Telefone: %s\n", atual->dados.telefone);
            printf("Data de Nascimento: %s\n", atual->dados.dataDeNascimento);
            printf("Email: %s\n", atual->dados.email);
            printf("-----------------------------\n");
            return atual;
        }
        atual=atual->prox;
    }

    printf("O cliente nao esta cadastrado\n");
    return NULL;

}

void remover_cliente(NodeCliente **root, char* cpf){

    NodeCliente *temp = *root;
    NodeCliente *previous = NULL;

    if(temp!=NULL && compara_strings(temp->dados.cpf,cpf)==0){
        *root=temp->prox;
        
        free(temp->dados.nome);
        free(temp->dados.cpf);
        free(temp->dados.telefone);
        free(temp->dados.senha);
        free(temp->dados.dataDeNascimento);
        free(temp->dados.email);
        free(temp);
        return;
    }

    while(temp!=NULL && compara_strings(temp->dados.cpf,cpf)!=0){

        previous=temp;
        temp=temp->prox;

    }

    if(temp==NULL){
        printf("Cliente nao encontrado!\n");
        return;
    } else {
        printf("Cliente removido!\n");
    }

    //desconectar o no que vai ser removido
    previous->prox = temp->prox;

    free(temp->dados.nome);
    free(temp->dados.cpf);
    free(temp->dados.telefone);
    free(temp->dados.senha);
    free(temp->dados.dataDeNascimento);
    free(temp->dados.email);
    free(temp);

}


//funcoes de edicao
void edita_nome(NodeCliente* root,char* nome, char* cpf){

    NodeCliente* cliente = root;
    while(cliente != NULL){
        if(compara_strings(cliente->dados.cpf, cpf) == 0){
            break;
        }
        cliente = cliente->prox;
    }

    if(cliente != NULL){
        free(cliente->dados.nome);
        cliente->dados.nome = copy_string(nome);
        vira_maiuscula(cliente->dados.nome);  

        printf("-------Dados do Cliente (Atualizado)-------\n");
        printf("Nome: %s\n", cliente->dados.nome);
        printf("CPF: %s\n", cliente->dados.cpf);
        printf("Telefone: %s\n", cliente->dados.telefone);
        printf("Data de Nascimento: %s\n", cliente->dados.dataDeNascimento);
        printf("Email: %s\n", cliente->dados.email);
        printf("------------------------------------------\n");
    } else {
        printf("Cliente nao encontrado!\n");
    }

}

void edita_cpf(NodeCliente* root, char* cpfnovo, char* cpfantigo){

    NodeCliente* cliente = busca_cliente(root,cpfantigo);

    if(cliente != NULL){
        free(cliente->dados.cpf);
        cliente->dados.cpf = copy_string(cpfnovo);
    }

}

void edita_telefone(NodeCliente* root, char* telefone, char* cpf){

    NodeCliente* cliente = busca_cliente(root,cpf);

    if(cliente != NULL){
        free(cliente->dados.telefone);
        cliente->dados.telefone = copy_string(telefone);
    }

}   

void edita_senha(NodeCliente* root, char* senha, char* cpf){

    NodeCliente* cliente = busca_cliente(root,cpf);

    if(cliente != NULL){
        free(cliente->dados.senha);
        cliente->dados.senha = copy_string(senha);
    }

}

void edita_data_de_nascimento(NodeCliente* root, char* dataDeNascimento, char* cpf){

    NodeCliente* cliente = busca_cliente(root,cpf);

    if(cliente != NULL){
        free(cliente->dados.dataDeNascimento);
        cliente->dados.dataDeNascimento = copy_string(dataDeNascimento);
    }

}

void edita_email(NodeCliente* root, char* email, char* cpf){

    NodeCliente* cliente = busca_cliente(root,cpf);

    if(cliente != NULL){
        free(cliente->dados.email);
        cliente->dados.email = copy_string(email);
    }

}

int verifica_cpf(NodeCliente* root, char* string){

    while(root!=NULL){
        if(compara_strings(root->dados.cpf, string)==0){
            return 0;
        }
        root=root->prox;
    }
    printf("Cliente com esse CPF nao Esta Cadastrado!\n");
    return 1;

}

void liberar_todos_clientes(NodeCliente** root){
    
    if(root == NULL || *root == NULL){
        return;
    }

    NodeCliente* atual = *root;
    NodeCliente* proximo = NULL;

    while(atual != NULL){
        proximo = atual->prox;
        
        free(atual->dados.nome);
        free(atual->dados.cpf);
        free(atual->dados.telefone);
        free(atual->dados.senha);
        free(atual->dados.dataDeNascimento);
        free(atual->dados.email);
        
        free(atual);
        
        atual = proximo;
    }

    *root = NULL;
}
