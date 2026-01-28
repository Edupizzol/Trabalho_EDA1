Produto* cadastrarProduto(Produto* head, char* codigo, char* nome, float preco) {
    if(buscarProduto(head, codigo) != NULL) {
        printf("Erro: Produto com esse codigo %s ja esta cadastrado.\n", codigo);
        return head;
    }

    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->codigo = alocarTexto(codigo);
    novoProduto->nome = alocarTexto(nome);
    novoProduto->preco = preco;
    novoProduto->next = NULL;

    if (head == NULL || strcmp(codigo, head->codigo) < 0) {
        novoProduto->next = head;
        return novoProduto;
    }

    Produto* atual = head;
    Produto* anterior = NULL;

    while(atual != NULL && strcmp(atual->codigo, codigo) < 0){
        anterior = atual;
        atual = atual->next;
    }

    anterior->next = novoProduto;
    novoProduto->next = atual;

    return head;
}
