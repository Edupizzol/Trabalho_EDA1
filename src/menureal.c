#define RAYGUI_NO_IMPLEMENTATION
#include "frontend.h"

void tela_menu_principal();
void tela_cadastro_cliente();
void tela_busca_cliente();
void tela_edita_cliente();
void tela_listar_clientes();
void tela_deleta_cliente();
void tela_cadastro_produto();
void tela_listar_produtos();
void tela_edita_produto();
void tela_remove_produto();
void tela_buscar_produto();
void tela_historico();
void tela_login();
void tela_carrinho_menu();
void tela_adicionar_produto_carrinho();
void tela_procurar_produto_carrinho();
void tela_remover_produto_carrinho();

Menu menu;

void tela_menu_principal() {
    
    DrawText("========== MENU PRINCIPAL ==========", 200, 30, 25, VERDE);
    
    int botao_x = 150;
    int botao_y = 100;
    int largura = 300;
    int altura = 40;
    int espacamento = 50;
    
    if (GuiButton((Rectangle){ botao_x, botao_y, largura, altura }, "01: Cadastrar Cliente")) {
        menu.tela = 1;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento, largura, altura }, "02: Buscar Cliente")) {
        menu.tela = 2;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 2, largura, altura }, "03: Editar Cliente")) {
        menu.tela = 3;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 3, largura, altura }, "04: Listar Clientes")) {
        menu.tela = 4;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 4, largura, altura }, "05: Deletar Cliente")) {
        menu.tela = 5;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 5, largura, altura }, "06: Cadastrar Produto")) {
        menu.tela = 6;
        limpar_inputs(&menu);
    }
    
    if (GuiButton((Rectangle){ botao_x + 350, botao_y, largura, altura }, "07: Listar Produtos")) {
        menu.tela = 7;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + 350, botao_y + espacamento, largura, altura }, "08: Remover Produto")) {
        menu.tela = 8;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + 350, botao_y + espacamento * 2, largura, altura }, "09: Editar Produto")) {
        menu.tela = 9;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + 350, botao_y + espacamento * 3, largura, altura }, "10: Buscar Produto")) {
        menu.tela = 16;
        limpar_inputs(&menu);
    }


    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 6, 650, 80 }, "INICIAR COMPRAS")) {
        menu.tela = 10;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + 350, botao_y + espacamento * 4, largura, altura }, "11: Ver Histórico")) {
        menu.tela = 11;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + 350, botao_y + espacamento * 5, largura, altura }, "00: Sair")) {
        menu.tela = -1;
    }
    
}

int menu_real() {
    menu.tela = 0;
    menu.cliente = carregar_clientes(CLIENTES_FILE);
    menu.produto = carregar_produtos(PRODUTOS_FILE);
    menu.historico = criar_historico();
    menu.input_cont = 0;
    menu.aviso_visivel = false;
    menu.aviso_tempo = 0;
    memset(menu.aviso_mensagem, 0, 200);
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sistema de Gestao - Interface Grafica");
    SetTargetFPS(60);
    
    while(!WindowShouldClose() && menu.tela != -1){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (menu.tela) {
            case 0:
                tela_menu_principal();
                break;
            case 1:
                tela_cadastro_cliente();
                break;
            case 2:
                tela_busca_cliente();
                break;
            case 3:
                tela_edita_cliente();
                break;
            case 4:
                tela_listar_clientes();
                break;
            case 5:
                tela_deleta_cliente();
                break;
            case 6:
                tela_cadastro_produto();
                break;
            case 7:
                tela_listar_produtos();
                break;
            case 8:
                tela_remove_produto();
                break;
            case 9:
                tela_edita_produto();
                break;
            case 10:
                tela_login();
                break;
            case 11:
                tela_historico();
                break;
            case 12:
                tela_carrinho_menu();
                break;
            case 13:
                tela_adicionar_produto_carrinho();
                break;
            case 14:
                tela_procurar_produto_carrinho();
                break;
            case 15:
                tela_remover_produto_carrinho();
                break;
            case 16:
                tela_buscar_produto();
                break;
            default:
                tela_menu_principal();
        }
        
        //desenha o aviso
        desenhar_aviso(&menu);

        EndDrawing();
    }
    
    salvar_clientes(menu.cliente, CLIENTES_FILE);
    salvar_produtos(menu.produto, PRODUTOS_FILE);
    limpar_historico(menu.historico);
    free(menu.historico);
    liberar_todos_clientes(&menu.cliente);
    liberar_todos_produtos(&menu.produto);
    
    CloseWindow();
    return 0;
}

void tela_cadastro_cliente(){
    //preparando as caixinhas 
    if(menu.input_cont==0){
        menu.inputs[0] = criar_botao((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ 200, 310, 300, 35 });
        menu.inputs[4] = criar_botao((Rectangle){ 200, 380, 300, 35 });
        menu.inputs[5] = criar_botao((Rectangle){ 200, 450, 300, 35 });
        menu.input_cont = 6;
    }

    DrawText("CADASTRO DE CLIENTE", 150, 20, 25, AMARELO);
    
    //lembrando que o q ta em aspas e o label/titulo do bottao
    frontend_scanf(&menu.inputs[0], "Nome:");
    frontend_scanf(&menu.inputs[1], "CPF (11 digitos):");
    frontend_scanf(&menu.inputs[2], "Telefone:");
    frontend_scanf(&menu.inputs[3], "Senha:");
    frontend_scanf(&menu.inputs[4], "Data Nascimento (DD/MM/AAAA):");
    frontend_scanf(&menu.inputs[5], "Email:");

    if(GuiButton((Rectangle){200,580,100,40}, "Salvar")){

        if(strlen(menu.inputs[0].texto)>0 && strlen(menu.inputs[1].texto)>0){
            //AVISO PRA SE AJ TIVER UM CLIENTE CSDASTRADO
            if(busca_cliente(menu.cliente, menu.inputs[1].texto) != NULL) {
                mostrar_aviso(&menu, "CPF ja cadastrado! Tente novamente.");
            } 
            else{
                cadastrar_cliente(&menu.cliente,
                    menu.inputs[0].texto,
                    menu.inputs[1].texto,
                    menu.inputs[2].texto,
                    menu.inputs[3].texto,
                    menu.inputs[4].texto,
                    menu.inputs[5].texto);
                salvar_clientes(menu.cliente, CLIENTES_FILE);
                adicionar_registro(menu.historico, "Novo cliente cadastrado.");
                menu.tela = 0;
                limpar_inputs(&menu);
            }
        }
    }
    
    if (GuiButton((Rectangle){ 350, 580, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_busca_cliente(){
    if(menu.input_cont==0){
        menu.inputs[0]=criar_botao((Rectangle){200, 150, 300, 35});
        menu.input_cont=1;
    }
    
    DrawText("BUSCAR CLIENTE", 150, 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF:");
    
    if(GuiButton((Rectangle){200, 250, 100, 40}, "Buscar")){
        NodeCliente* encontrado = busca_cliente(menu.cliente, menu.inputs[0].texto);
        if(encontrado != NULL){
            adicionar_registro(menu.historico, "Cliente buscado.");
            menu.resultado_visivel = true;
            menu.resultado_sucesso = true;
        } 
        else{
            menu.resultado_visivel = true;
            menu.resultado_sucesso = false;
        }
    }
    
    if(menu.resultado_visivel){
        Color cor;
        const char* msg;

        if(menu.resultado_sucesso){
            cor=GREEN;
            msg="Cliente encontrado!";
            NodeCliente* dados = busca_cliente(menu.cliente, menu.inputs[0].texto);
            if(dados != NULL){
                DrawText(TextFormat("Nome: %s", dados->dados.nome), 200, 350, 20, BLACK);
                DrawText(TextFormat("Email: %s", dados->dados.email), 200, 380, 20, DARKGRAY);
            }
        } 
        else{
            cor=RED;
            msg="Cliente não encontrado!";
        }
        DrawText(msg, 200, 320, 20, cor);
    }
    
    if(GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")){
        menu.tela = 0;
        menu.resultado_visivel = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_edita_cliente() {
    if(menu.input_cont == 0){
        menu.inputs[0] = criar_botao((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ 200, 310, 300, 35 });
        menu.inputs[4] = criar_botao((Rectangle){ 200, 380, 300, 35 });
        menu.inputs[5] = criar_botao((Rectangle){ 200, 450, 300, 35 });
        menu.inputs[6] = criar_botao((Rectangle){ 200, 520, 300, 35 });
        menu.input_cont = 7;
    }
    
    DrawText("EDITAR CLIENTE", 150, 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF Original:");
    frontend_scanf(&menu.inputs[1], "Novo Nome:");
    frontend_scanf(&menu.inputs[2], "Novo Telefone:");
    frontend_scanf(&menu.inputs[3], "Nova Senha:");
    frontend_scanf(&menu.inputs[4], "Nova Data (DD/MM/AAAA):");
    frontend_scanf(&menu.inputs[5], "Novo Email:");
    frontend_scanf(&menu.inputs[6], "Novo CPF:");
    
    if (GuiButton((Rectangle){ 200, 580, 100, 40 }, "Atualizar")) {
        if (strlen(menu.inputs[0].texto) > 0) {
            if(strlen(menu.inputs[1].texto) > 0){
                edita_nome(menu.cliente, menu.inputs[1].texto, menu.inputs[0].texto);
            }
            if(strlen(menu.inputs[2].texto) > 0){
                edita_telefone(menu.cliente, menu.inputs[2].texto, menu.inputs[0].texto);
            }
            if(strlen(menu.inputs[3].texto) > 0){
                edita_senha(menu.cliente, menu.inputs[3].texto, menu.inputs[0].texto);
            }
            if(strlen(menu.inputs[4].texto) > 0){
                edita_data_de_nascimento(menu.cliente, menu.inputs[4].texto, menu.inputs[0].texto);
            }
            if(strlen(menu.inputs[5].texto) > 0){
                edita_email(menu.cliente, menu.inputs[5].texto, menu.inputs[0].texto);
            }
            if(strlen(menu.inputs[6].texto) > 0){
                edita_cpf(menu.cliente, menu.inputs[6].texto, menu.inputs[0].texto);
            }
            salvar_clientes(menu.cliente, CLIENTES_FILE);
            adicionar_registro(menu.historico, "Dados do cliente editados.");
            menu.tela = 0;
            limpar_inputs(&menu);
        }
    }
    
    if(GuiButton((Rectangle){ 350, 580, 100, 40 }, "Voltar")){
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}


void tela_deleta_cliente() {
    if(menu.input_cont == 0){
        menu.inputs[0] = criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.input_cont = 1;
    }
    
    DrawText("DELETAR CLIENTE", 150, 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF:");
    
    if(GuiButton((Rectangle){ 200, 250, 100, 40 }, "Deletar")) {
        if(remover_cliente(&menu.cliente, menu.inputs[0].texto)){
            salvar_clientes(menu.cliente, CLIENTES_FILE);
            adicionar_registro(menu.historico, "Cliente removido.");
            menu.tela = 0;
            limpar_inputs(&menu);
        }
    }
    
    if (GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }

}


void tela_listar_clientes(){
    
    DrawText("LISTA DE CLIENTES", 150, 20, 25, AMARELO);
    
    int y = 80;
    NodeCliente* atual = menu.cliente;
    while(atual != NULL && y < 600) {
        DrawText(TextFormat("Nome: %s | CPF: %s", atual->dados.nome, atual->dados.cpf), 50, y, 15, BLACK);
        y += 30;
        atual = atual->prox;
    }
    
    adicionar_registro(menu.historico, "Lista de clientes exibida.");
    
    if (GuiButton((Rectangle){ 200, 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }

}

void tela_cadastro_produto() {
    if (menu.input_cont == 0) {
        menu.inputs[0] = criar_botao((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ 200, 310, 300, 35 });
        menu.input_cont = 4;
    }
    
    DrawText("CADASTRO DE PRODUTO", 150, 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    frontend_scanf(&menu.inputs[1], "Nome:");
    frontend_scanf(&menu.inputs[2], "Preco:");
    frontend_scanf(&menu.inputs[3], "Quantidade:");
    
    if(GuiButton((Rectangle){ 200, 380, 100, 40 }, "Salvar")){

        if (strlen(menu.inputs[0].texto) > 0) {
            // Verificar se o codigo ja existe
            if(buscarProduto(menu.produto, menu.inputs[0].texto) != NULL) {
                mostrar_aviso(&menu, "Codigo de produto ja cadastrado! Tente novamente.");
            } else {
                float preco = TextToFloat(menu.inputs[2].texto);
                int quantidade = atoi(menu.inputs[3].texto);
                menu.produto = cadastrarProduto(
                    menu.produto,
                    menu.inputs[0].texto,
                    menu.inputs[1].texto,
                    preco,
                    quantidade
                );
                salvar_produtos(menu.produto, PRODUTOS_FILE);
                adicionar_registro(menu.historico, "Produto cadastrado.");
                menu.tela = 0;
                limpar_inputs(&menu);
            }
        }

    }
    
    if (GuiButton((Rectangle){ 350, 380, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_listar_produtos() {
    
    DrawText("LISTA DE PRODUTOS", 150, 20, 25, VERMELHO);
    
    int y = 80;
    Produto* atual = menu.produto;
    while (atual != NULL && y < 600){

        DrawText(TextFormat("Codigo: %s | Nome: %s | Preco: R$%.2f | Qtd: %d", 
        atual->codigo, atual->nome, atual->preco, atual->quantidade), 50, y, 15, BLACK);
        y += 30;
        atual = atual->next;

    }
    
    adicionar_registro(menu.historico, "Lista de produtos exibida.");
    
    if (GuiButton((Rectangle){ 200, 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }
    
}

void tela_edita_produto() {
    if (menu.input_cont == 0) {
        menu.inputs[0] = criar_botao((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ 200, 310, 300, 35 });
        menu.input_cont = 4;
    }
    
    DrawText("EDITAR PRODUTO", 150, 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    frontend_scanf(&menu.inputs[1], "Novo Nome:");
    frontend_scanf(&menu.inputs[2], "Novo Preco:");
    frontend_scanf(&menu.inputs[3], "Nova Quantidade:");
    
    if (GuiButton((Rectangle){ 200, 380, 100, 40 }, "Atualizar")) {
        if (strlen(menu.inputs[0].texto) > 0) {
            float preco = TextToFloat(menu.inputs[2].texto);
            int quantidade = atoi(menu.inputs[3].texto);
            editarDadosProduto(menu.produto, menu.inputs[0].texto,
                menu.inputs[1].texto, preco, quantidade);
            salvar_produtos(menu.produto, PRODUTOS_FILE);
            adicionar_registro(menu.historico, "Dados do produto editados.");
            menu.tela = 0;
            limpar_inputs(&menu);
        }
    }
    
    if (GuiButton((Rectangle){ 350, 380, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}


void tela_remove_produto() {
    if (menu.input_cont == 0) {
        menu.inputs[0] = criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.input_cont = 1;
    }
    
    DrawText("REMOVER PRODUTO", 150, 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    
    if (GuiButton((Rectangle){ 200, 250, 100, 40 }, "Remover")) {
        if (removerProduto(&menu.produto, menu.inputs[0].texto)) {
            salvar_produtos(menu.produto, PRODUTOS_FILE);
            adicionar_registro(menu.historico, "Produto removido.");
            menu.tela = 0;
            limpar_inputs(&menu);
        }
    }
    
    if (GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_buscar_produto() {
    static Produto* produto_encontrado = NULL;
    static bool busca_realizada = false;
    
    if (menu.input_cont == 0) {
        menu.inputs[0] = criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.input_cont = 1;
        produto_encontrado = NULL;
        busca_realizada = false;
    }
    
    DrawText("BUSCAR PRODUTO", 150, 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    
    if (GuiButton((Rectangle){ 200, 250, 100, 40 }, "Buscar")) {
        if (strlen(menu.inputs[0].texto) > 0) {
            produto_encontrado = buscarProduto(menu.produto, menu.inputs[0].texto);
            busca_realizada = true;
        }
    }
    
    if (busca_realizada) {
        if (produto_encontrado != NULL) {
            DrawText("Produto encontrado:", 200, 320, 18, VERDE);
            DrawText(TextFormat("Nome: %s", produto_encontrado->nome), 200, 350, 16, DARKGRAY);
            DrawText(TextFormat("Preco: R$ %.2f", produto_encontrado->preco), 200, 380, 16, DARKGRAY);
            DrawText(TextFormat("Quantidade: %d", produto_encontrado->quantidade), 200, 410, 16, DARKGRAY);
        } else {
            DrawText("Produto nao encontrado!", 200, 320, 18, VERMELHO);
        }
    }
    
    if (GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
        produto_encontrado = NULL;
        busca_realizada = false;
    }
}

void tela_historico() {

    DrawText("HISTORICO DE OPERACOES", 150, 20, 25, GREEN);
    DrawText(TextFormat("Total: %d operacoes", menu.historico->total), 150, 50, 15, GRAY);
    
    int y = 100;
    int max_visible = 12;
    int contador = 0;
    
    NoHistorico* atual = menu.historico->inicio;
    while(atual != NULL && contador < max_visible) {
        DrawText(TextFormat("[%s] %s", atual->dados.timestamp, atual->dados.operacao), 50, y, 14, BLACK);
        y += 30;
        atual = atual->proximo;
        contador++;
    }
    
    if (menu.historico->total == 0) {
        DrawText("Historico vazio", 50, 100, 14, GRAY);
    }
    
    if (GuiButton((Rectangle){ 200, 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }
    
}

void tela_login(){

    if(menu.input_cont==0){
        menu.inputs[0]=criar_botao((Rectangle){200,150,300,35});
        menu.inputs[1]=criar_botao((Rectangle){200,250,300,35});
        menu.input_cont=2;
    }

    DrawText("LOGIN - COMPRAS", 150, 20, 25, VERDE);

    frontend_scanf(&menu.inputs[0], "CPF:");
    frontend_scanf(&menu.inputs[1], "Senha:");

    if(GuiButton((Rectangle){ 200, 350, 100, 40 }, "Entrar")){
        if(strlen(menu.inputs[0].texto)>0 && strlen(menu.inputs[1].texto)>0){
            NodeCliente* cliente_encontrado = busca_cliente(menu.cliente, menu.inputs[0].texto);
            
            if(cliente_encontrado != NULL){
                if(login(menu.cliente, menu.inputs[0].texto, menu.inputs[1].texto) == 0){

                    menu.cliente_logado = cliente_encontrado;
                    menu.carrinho = criar_carrinho();
                    adicionar_dono_do_carrinho(menu.carrinho, &cliente_encontrado->dados);
                    adicionar_registro(menu.historico, "Usuario fez login no modo compra.");
                    menu.tela = 12;
                    limpar_inputs(&menu);

                }
                else{
                    mostrar_aviso(&menu, "Senha incorreta!");
                }
            }
            else {
                mostrar_aviso(&menu, "CPF nao encontrado!");
            }
        }
    }
    
    if(GuiButton((Rectangle){ 350, 350, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }

}

void tela_carrinho_menu(){
    DrawText("CARRINHO DE COMPRAS", 150, 20, 25, VERDE);
    
    int botao_x = 150;
    int botao_y = 100;
    int largura = 300;
    int altura = 60;
    int espacamento = 80;
    
    if(GuiButton((Rectangle){ botao_x, botao_y, largura, altura }, "Colocar no Carrinho")) {
        menu.tela = 13;
        limpar_inputs(&menu);
    }
    
    if(GuiButton((Rectangle){ botao_x, botao_y + espacamento, largura, altura }, "Buscar no Carrinho")) {
        menu.tela = 14;
        limpar_inputs(&menu);
    }
    
    if(GuiButton((Rectangle){ botao_x, botao_y + espacamento*2, largura, altura }, "Remover do Carrinho")) {
        menu.tela = 15;
        limpar_inputs(&menu);
    }
    
    if(GuiButton((Rectangle){ botao_x, botao_y + espacamento*3, largura, altura }, "Voltar")) {
        if(menu.carrinho != NULL) {
            liberar_carrinho(&menu.carrinho);
        }
        menu.cliente_logado = NULL;
        menu.tela = 0;
        limpar_inputs(&menu);
    }
}

void tela_adicionar_produto_no_carrinho(){

    if(menu.input_cont==0){
        menu.inputs[0] = criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.input_cont = 1;
    }

    DrawText("PROCURAR PRODUTO:", 150, 20, 25, VERDE);
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");

    if(GuiButton((Rectangle){ 200, 250, 100, 40 }, "Procurar")){
        if(strlen(menu.inputs[0].texto)>0){
            Produto* encontrado = procura_produto_no_carrinho(menu.carrinho, menu.inputs[0].texto);
            if(encontrado != NULL){

                DrawText(TextFormat("Produto: %s", encontrado->nome), 200, 350, 16, VERDE);
                DrawText(TextFormat("Preco: R$ %.2f", encontrado->preco), 200, 380, 16, BLACK);
                DrawText(TextFormat("Quantidade: %d", encontrado->quantidade), 200, 410, 16, BLACK);
                adicionar_registro(menu.historico, "Produto buscado no carrinho.");

            } 
            else{
                DrawText("Produto nao encontrado no carrinho!", 200, 350, 16, VERMELHO);
            }
        }
    }
    
    if(GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }

}

void tela_adicionar_produto_carrinho(){

    if(menu.input_cont==0){
        menu.inputs[0]=criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.inputs[1]=criar_botao((Rectangle){ 200, 220, 300, 35 });
        menu.input_cont=2;
    }
    
    DrawText("ADICIONAR PRODUTO", 150, 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    frontend_scanf(&menu.inputs[1], "Quantidade:");
    
    if(GuiButton((Rectangle){ 200, 320, 100, 40 }, "Adicionar")) {
        if(strlen(menu.inputs[0].texto)>0 && strlen(menu.inputs[1].texto)>0){

            Produto* produto_db = buscarProduto(menu.produto, menu.inputs[0].texto);
            if(produto_db != NULL) {

                int quantidade = atoi(menu.inputs[1].texto);
                if(quantidade > 0 && quantidade <= produto_db->quantidade) {
                    adicionar_produto_ao_carrinho(menu.carrinho, produto_db, quantidade);
                    adicionar_registro(menu.historico, "Produto adicionado ao carrinho.");
                    salvar_produtos(menu.produto, PRODUTOS_FILE);
                    menu.tela = 12;
                    limpar_inputs(&menu);
                }
                else {
                    mostrar_aviso(&menu, "Quantidade invalida!");
                }

            } 
            else{
                mostrar_aviso(&menu, "Produto nao encontrado!");
            }
        }
    }
    
    if(GuiButton((Rectangle){ 350, 320, 100, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }

}

void tela_procurar_produto_carrinho(){
    static Produto* produto_encontrado = NULL;
    static bool busca_realizada = false;

    if(menu.input_cont==0){
        menu.inputs[0]=criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.input_cont=1;
        produto_encontrado = NULL;
        busca_realizada = false;
    }
    
    DrawText("PROCURAR PRODUTO NO CARRINHO", 100, 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    
    if(GuiButton((Rectangle){ 200, 250, 100, 40 }, "Procurar")) {
        if(strlen(menu.inputs[0].texto)>0){
            produto_encontrado = procura_produto_no_carrinho(menu.carrinho, menu.inputs[0].texto);
            busca_realizada = true;
        }
    }
    
    if(busca_realizada) {
        if(produto_encontrado != NULL) {
            DrawText("Produto encontrado no carrinho!", 200, 320, 16, VERDE);
            DrawText(TextFormat("Quantidade: %d", produto_encontrado->quantidade), 200, 350, 16, VERDE);
        } 
        else{
            DrawText("Produto nao encontrado no carrinho!", 200, 320, 16, VERMELHO);
        }
    }
    
    if(GuiButton((Rectangle){ 350, 250, 100, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
        produto_encontrado = NULL;
        busca_realizada = false;
    }

}

void tela_remover_produto_carrinho(){

    if(menu.input_cont==0){
        menu.inputs[0]=criar_botao((Rectangle){ 200, 150, 300, 35 });
        menu.inputs[1]=criar_botao((Rectangle){ 200, 220, 300, 35 });
        menu.input_cont=2;
    }
    
    DrawText("REMOVER PRODUTO", 150, 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    frontend_scanf(&menu.inputs[1], "Quantidade a Remover:");
    
    if(GuiButton((Rectangle){ 200, 320, 100, 40 }, "Remover")) {
        if(strlen(menu.inputs[0].texto)>0 && strlen(menu.inputs[1].texto)>0){

            Produto* produto_carrinho = procura_produto_no_carrinho(menu.carrinho, menu.inputs[0].texto);
            if(produto_carrinho != NULL) {

                int qtd_remover = atoi(menu.inputs[1].texto);
                Produto* produto_db = buscarProduto(menu.produto, menu.inputs[0].texto);

                if(remove_produto_do_carrinho(menu.carrinho, produto_db, qtd_remover) != NULL){
                    adicionar_registro(menu.historico, "Produto removido do carrinho.");
                    salvar_produtos(menu.produto, PRODUTOS_FILE);
                    menu.tela = 12;
                    limpar_inputs(&menu);
                }

            } 
            else{
                mostrar_aviso(&menu, "Produto nao encontrado no carrinho!");
            }
        }
    }
    
    if(GuiButton((Rectangle){ 350, 320, 100, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }
}

