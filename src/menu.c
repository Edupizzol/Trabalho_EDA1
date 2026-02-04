#include "../include/menu.h"
#include "../include/salvamento.h"
Menu menu;

static int center_x(int width) {
    return (SCREEN_WIDTH - width) / 2;
}

static int center_text_x(const char* text, int fontSize) {
    return (SCREEN_WIDTH - MeasureText(text, fontSize)) / 2;
}

static int center_pair_x(int width, int gap) {
    return (SCREEN_WIDTH - (width * 2 + gap)) / 2;
}

void tela_menu_principal() {
    DrawText("========== MENU PRINCIPAL ==========", center_text_x("========== MENU PRINCIPAL ==========", 25), 30, 25, VERDE);

    int largura = 300;
    int coluna_gap = 50;
    int col_total = largura * 2 + coluna_gap;
    int botao_x = center_x(col_total);
    int botao_y = 100;
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
    
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y, largura, altura }, "07: Listar Produtos")) {
        menu.tela = 7;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y + espacamento, largura, altura }, "08: Remover Produto")) {
        menu.tela = 8;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y + espacamento * 2, largura, altura }, "09: Editar Produto")) {
        menu.tela = 9;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y + espacamento * 3, largura, altura }, "10: Buscar Produto")) {
        menu.tela = 16;
        limpar_inputs(&menu);
    }


    if (GuiButton((Rectangle){ botao_x, botao_y + espacamento * 6, col_total, 80 }, "INICIAR COMPRAS")) {
        menu.tela = 10;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y + espacamento * 4, largura, altura }, "11: Ver Histórico")) {
        menu.tela = 11;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ botao_x + largura + coluna_gap, botao_y + espacamento * 5, largura, altura }, "00: Sair")) {
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
            case 17:
                tela_resumo_compras();
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
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 100, largura_forma, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ forma_x, 170, largura_forma, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ forma_x, 240, largura_forma, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ forma_x, 310, largura_forma, 35 });
        menu.inputs[4] = criar_botao((Rectangle){ forma_x, 380, largura_forma, 35 });
        menu.inputs[5] = criar_botao((Rectangle){ forma_x, 450, largura_forma, 35 });
        menu.input_cont = 6;
    }

    DrawText("CADASTRO DE CLIENTE", center_text_x("CADASTRO DE CLIENTE", 25), 20, 25, AMARELO);
    
    //lembrando que o q ta em aspas e o label/titulo do bottao
    frontend_scanf(&menu.inputs[0], "Nome:");
    frontend_scanf(&menu.inputs[1], "CPF (11 digitos):");
    frontend_scanf(&menu.inputs[2], "Telefone:");
    frontend_scanf(&menu.inputs[3], "Senha:");
    frontend_scanf(&menu.inputs[4], "Data Nascimento (DD/MM/AAAA):");
    frontend_scanf(&menu.inputs[5], "Email:");

    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 580;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Salvar")){

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
    
    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_busca_cliente(){
    if(menu.input_cont==0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0]=criar_botao((Rectangle){ forma_x, 150, largura_forma, 35});
        menu.input_cont=1;
    }

    DrawText("BUSCAR CLIENTE", center_text_x("BUSCAR CLIENTE", 25), 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40}, "Buscar")){
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
                const char* nome_text = TextFormat("Nome: %s", dados->dados.nome);
                const char* email_text = TextFormat("Email: %s", dados->dados.email);
                DrawText(nome_text, center_text_x(nome_text, 20), 350, 20, BLACK);
                DrawText(email_text, center_text_x(email_text, 20), 380, 20, DARKGRAY);
            }
        } 
        else{
            cor=RED;
            msg="Cliente não encontrado!";
        }
        DrawText(msg, center_text_x(msg, 20), 320, 20, cor);
    }

    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")){
        menu.tela = 0;
        menu.resultado_visivel = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_edita_cliente() {
    if(menu.input_cont == 0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 100, largura_forma, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ forma_x, 170, largura_forma, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ forma_x, 240, largura_forma, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ forma_x, 310, largura_forma, 35 });
        menu.inputs[4] = criar_botao((Rectangle){ forma_x, 380, largura_forma, 35 });
        menu.inputs[5] = criar_botao((Rectangle){ forma_x, 450, largura_forma, 35 });
        menu.inputs[6] = criar_botao((Rectangle){ forma_x, 520, largura_forma, 35 });
        menu.input_cont = 7;
    }

    DrawText("EDITAR CLIENTE", center_text_x("EDITAR CLIENTE", 25), 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF Original:");
    frontend_scanf(&menu.inputs[1], "Novo Nome:");
    frontend_scanf(&menu.inputs[2], "Novo Telefone:");
    frontend_scanf(&menu.inputs[3], "Nova Senha:");
    frontend_scanf(&menu.inputs[4], "Nova Data (DD/MM/AAAA):");
    frontend_scanf(&menu.inputs[5], "Novo Email:");
    frontend_scanf(&menu.inputs[6], "Novo CPF:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 580;

    if (GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Atualizar")) {
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
    
    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")){
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}


void tela_deleta_cliente() {
    if(menu.input_cont == 0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.input_cont = 1;
    }

    DrawText("DELETAR CLIENTE", center_text_x("DELETAR CLIENTE", 25), 20, 25, AMARELO);
    
    frontend_scanf(&menu.inputs[0], "CPF:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Deletar")) {
        if(remover_cliente(&menu.cliente, menu.inputs[0].texto)){
            salvar_clientes(menu.cliente, CLIENTES_FILE);
            adicionar_registro(menu.historico, "Cliente removido.");
            menu.tela = 0;
            limpar_inputs(&menu);
        }
    }
    
    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }

}


void tela_listar_clientes(){
    int largura_lista = 940;
    int lista_x = center_x(largura_lista);

    DrawText("LISTA DE CLIENTES", center_text_x("LISTA DE CLIENTES", 25), 20, 25, AMARELO);

    int y = 80;
    NodeCliente* atual = menu.cliente;
    while(atual != NULL && y < 600) {
        DrawText(TextFormat("Nome: %s | CPF: %s | Tel: %s | Data: %s | Senha: %s", atual->dados.nome, atual->dados.cpf, atual->dados.telefone, atual->dados.dataDeNascimento, atual->dados.senha), lista_x, y, 12, BLACK);
        y += 25;
        atual = atual->prox;
    }
    
    adicionar_registro(menu.historico, "Lista de clientes exibida.");
    
    if (GuiButton((Rectangle){ center_x(100), 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }

}

void tela_cadastro_produto() {
    if (menu.input_cont == 0) {
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 100, largura_forma, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ forma_x, 170, largura_forma, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ forma_x, 240, largura_forma, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ forma_x, 310, largura_forma, 35 });
        menu.input_cont = 4;
    }

    DrawText("CADASTRO DE PRODUTO", center_text_x("CADASTRO DE PRODUTO", 25), 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    frontend_scanf(&menu.inputs[1], "Nome:");
    frontend_scanf(&menu.inputs[2], "Preco:");
    frontend_scanf(&menu.inputs[3], "Quantidade:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 380;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Salvar")){

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
    
    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_listar_produtos() {
    int largura_lista = 900;
    int lista_x = center_x(largura_lista);

    DrawText("LISTA DE PRODUTOS", center_text_x("LISTA DE PRODUTOS", 25), 20, 25, VERMELHO);

    int y = 80;
    Produto* atual = menu.produto;
    while (atual != NULL && y < 600){

        DrawText(TextFormat("Codigo: %s | Nome: %s | Preco: R$%.2f | Qtd: %d", 
        atual->codigo, atual->nome, atual->preco, atual->quantidade), lista_x, y, 15, BLACK);
        y += 30;
        atual = atual->next;

    }
    
    adicionar_registro(menu.historico, "Lista de produtos exibida.");
    
    if (GuiButton((Rectangle){ center_x(100), 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }
    
}

void tela_edita_produto() {
    if (menu.input_cont == 0) {
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 100, largura_forma, 35 });
        menu.inputs[1] = criar_botao((Rectangle){ forma_x, 170, largura_forma, 35 });
        menu.inputs[2] = criar_botao((Rectangle){ forma_x, 240, largura_forma, 35 });
        menu.inputs[3] = criar_botao((Rectangle){ forma_x, 310, largura_forma, 35 });
        menu.input_cont = 4;
    }

    DrawText("EDITAR PRODUTO", center_text_x("EDITAR PRODUTO", 25), 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    frontend_scanf(&menu.inputs[1], "Novo Nome:");
    frontend_scanf(&menu.inputs[2], "Novo Preco:");
    frontend_scanf(&menu.inputs[3], "Nova Quantidade:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 380;

    if (GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Atualizar")) {
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
    
    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}


void tela_remove_produto() {
    static bool resultado_visivel = false;
    static bool resultado_sucesso = false;
    static char resultado_msg[128];

    if (menu.input_cont == 0) {
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.input_cont = 1;
        resultado_visivel = false;
        resultado_sucesso = false;
        memset(resultado_msg, 0, sizeof(resultado_msg));
    }

    DrawText("REMOVER PRODUTO", center_text_x("REMOVER PRODUTO", 25), 20, 25, VERMELHO);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if (GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Remover")) {
        if (strlen(menu.inputs[0].texto) > 0) {
            if (removerProduto(&menu.produto, menu.inputs[0].texto)) {
                salvar_produtos(menu.produto, PRODUTOS_FILE);
                adicionar_registro(menu.historico, "Produto removido.");
                resultado_visivel = true;
                resultado_sucesso = true;
                strncpy(resultado_msg, "Produto removido com sucesso!", sizeof(resultado_msg) - 1);
                menu.tela = 0;
                limpar_inputs(&menu);
            } 
            else{
                resultado_visivel = true;
                resultado_sucesso = false;
                strncpy(resultado_msg, "Produto nao encontrado!", sizeof(resultado_msg) - 1);
            }
        } 
        else{
            resultado_visivel = true;
            resultado_sucesso = false;
            strncpy(resultado_msg, "Informe o codigo do produto.", sizeof(resultado_msg) - 1);
        }
    }

    if (resultado_visivel) {
        Color cor = resultado_sucesso ? GREEN : VERMELHO;
        DrawText(resultado_msg, center_text_x(resultado_msg, 18), 320, 18, cor);
    }
    
    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_buscar_produto() {
    static Produto* produto_encontrado = NULL;
    static bool busca_realizada = false;
    
    if (menu.input_cont == 0) {
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.input_cont = 1;
        produto_encontrado = NULL;
        busca_realizada = false;
    }

    DrawText("BUSCAR PRODUTO", center_text_x("BUSCAR PRODUTO", 25), 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if (GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Buscar")) {
        if (strlen(menu.inputs[0].texto) > 0) {
            produto_encontrado = buscarProduto(menu.produto, menu.inputs[0].texto);
            busca_realizada = true;
        }
    }
    
    if (busca_realizada) {
        if (produto_encontrado != NULL) {
            DrawText("Produto encontrado:", center_text_x("Produto encontrado:", 18), 320, 18, VERDE);
            {
                const char* nome_text = TextFormat("Nome: %s", produto_encontrado->nome);
                const char* preco_text = TextFormat("Preco: R$ %.2f", produto_encontrado->preco);
                const char* qtd_text = TextFormat("Quantidade: %d", produto_encontrado->quantidade);
                DrawText(nome_text, center_text_x(nome_text, 16), 350, 16, DARKGRAY);
                DrawText(preco_text, center_text_x(preco_text, 16), 380, 16, DARKGRAY);
                DrawText(qtd_text, center_text_x(qtd_text, 16), 410, 16, DARKGRAY);
            }
        } else {
            DrawText("Produto nao encontrado!", center_text_x("Produto nao encontrado!", 18), 320, 18, VERMELHO);
        }
    }

    if (GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
        produto_encontrado = NULL;
        busca_realizada = false;
    }
}

void tela_historico() {
    int largura_lista = 900;
    int lista_x = center_x(largura_lista);

    DrawText("HISTORICO DE OPERACOES", center_text_x("HISTORICO DE OPERACOES", 25), 20, 25, GREEN);
    {
        const char* total_text = TextFormat("Total: %d operacoes", menu.historico->total);
        DrawText(total_text, center_text_x(total_text, 15), 50, 15, GRAY);
    }

    int y = 100;
    int max_visible = 12;
    int contador = 0;
    
    NoHistorico* atual = menu.historico->inicio;
    while(atual != NULL && contador < max_visible) {
        DrawText(TextFormat("[%s] %s", atual->dados.timestamp, atual->dados.operacao), lista_x, y, 14, BLACK);
        y += 30;
        atual = atual->proximo;
        contador++;
    }
    
    if (menu.historico->total == 0) {
        DrawText("Historico vazio", center_text_x("Historico vazio", 14), 100, 14, GRAY);
    }
    
    if (GuiButton((Rectangle){ center_x(100), 650, 100, 40 }, "Voltar")) {
        menu.tela = 0;
    }
    
}

void tela_login(){

    if(menu.input_cont==0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0]=criar_botao((Rectangle){ forma_x,150,largura_forma,35});
        menu.inputs[1]=criar_botao((Rectangle){ forma_x,250,largura_forma,35});
        menu.input_cont=2;
    }

    DrawText("LOGIN - COMPRAS", center_text_x("LOGIN - COMPRAS", 25), 20, 25, VERDE);

    frontend_scanf(&menu.inputs[0], "CPF:");
    frontend_scanf(&menu.inputs[1], "Senha:");

    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 350;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Entrar")){
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
    
    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }

}

void tela_carrinho_menu(){
    DrawText("CARRINHO DE COMPRAS", center_text_x("CARRINHO DE COMPRAS", 25), 20, 25, VERDE);

    int botao_x = center_x(300);
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
        menu.tela = 17;
        limpar_inputs(&menu);
    }
}

void tela_resumo_compras(){
    DrawText("RESUMO DAS COMPRAS", center_text_x("RESUMO DAS COMPRAS", 25), 20, 25, VERDE);

    int y = 80;
    float total = 0.0f;

    int table_width = 700;
    int table_x = center_x(table_width);
    int col_prod = table_x;
    int col_qtd = table_x + 370;
    int col_preco = table_x + 470;

    DrawText("Produto", col_prod, y, 16, DARKGRAY);
    DrawText("Qtd", col_qtd, y, 16, DARKGRAY);
    DrawText("Preco", col_preco, y, 16, DARKGRAY);
    y += 25;

    if(menu.carrinho == NULL || menu.carrinho->produto == NULL){
        DrawText("Carrinho vazio.", center_text_x("Carrinho vazio.", 16), y, 16, VERMELHO);
        y += 25;
    }
    else{
        Produto* atual = menu.carrinho->produto;
        while(atual != NULL) {
            DrawText(TextFormat("%s", atual->nome), col_prod, y, 16, BLACK);
            DrawText(TextFormat("%d", atual->quantidade), col_qtd, y, 16, BLACK);
            DrawText(TextFormat("R$ %.2f", atual->preco), col_preco, y, 16, BLACK);
            total += atual->preco * atual->quantidade;
            y += 25;
            atual = atual->next;
        }
    }

    {
        const char* total_text = TextFormat("Total: R$ %.2f", total);
        DrawText(total_text, center_text_x(total_text, 18), y + 20, 18, VERDE);
    }

    if(GuiButton((Rectangle){ center_x(200), y + 60, 200, 40 }, "Voltar ao Menu")) {
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
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0] = criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.input_cont = 1;
    }

    DrawText("PROCURAR PRODUTO:", center_text_x("PROCURAR PRODUTO:", 25), 20, 25, VERDE);
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");

    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Procurar")){
        if(strlen(menu.inputs[0].texto)>0){
            Produto* encontrado = procura_produto_no_carrinho(menu.carrinho, menu.inputs[0].texto);
            if(encontrado != NULL){

                const char* prod_text = TextFormat("Produto: %s", encontrado->nome);
                const char* preco_text = TextFormat("Preco: R$ %.2f", encontrado->preco);
                const char* qtd_text = TextFormat("Quantidade: %d", encontrado->quantidade);
                DrawText(prod_text, center_text_x(prod_text, 16), 350, 16, VERDE);
                DrawText(preco_text, center_text_x(preco_text, 16), 380, 16, BLACK);
                DrawText(qtd_text, center_text_x(qtd_text, 16), 410, 16, BLACK);
                adicionar_registro(menu.historico, "Produto buscado no carrinho.");

            } 
            else{
                DrawText("Produto nao encontrado no carrinho!", center_text_x("Produto nao encontrado no carrinho!", 16), 350, 16, VERMELHO);
            }
        }
    }

    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }

}

void tela_adicionar_produto_carrinho(){

    if(menu.input_cont==0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0]=criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.inputs[1]=criar_botao((Rectangle){ forma_x, 220, largura_forma, 35 });
        menu.input_cont=2;
    }

    DrawText("ADICIONAR PRODUTO", center_text_x("ADICIONAR PRODUTO", 25), 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    frontend_scanf(&menu.inputs[1], "Quantidade:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 320;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Adicionar")) {
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
    
    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }

}

void tela_procurar_produto_carrinho(){
    static Produto* produto_encontrado = NULL;
    static bool busca_realizada = false;

    if(menu.input_cont==0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0]=criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.input_cont=1;
        produto_encontrado = NULL;
        busca_realizada = false;
    }

    DrawText("PROCURAR PRODUTO NO CARRINHO", center_text_x("PROCURAR PRODUTO NO CARRINHO", 25), 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 250;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Procurar")){
        if(strlen(menu.inputs[0].texto)>0){
            produto_encontrado = procura_produto_no_carrinho(menu.carrinho, menu.inputs[0].texto);
            busca_realizada = true;
        }
    }
    
    if(busca_realizada){
        if(produto_encontrado != NULL) {
            const char* found_text = "Produto encontrado no carrinho!";
            const char* qtd_text = TextFormat("Quantidade: %d", produto_encontrado->quantidade);
            DrawText(found_text, center_text_x(found_text, 16), 320, 16, VERDE);
            DrawText(qtd_text, center_text_x(qtd_text, 16), 350, 16, VERDE);
        } 
        else{
            DrawText("Produto nao encontrado no carrinho!", center_text_x("Produto nao encontrado no carrinho!", 16), 320, 16, VERMELHO);
        }
    }

    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
        produto_encontrado = NULL;
        busca_realizada = false;
    }

}

void tela_remover_produto_carrinho(){

    if(menu.input_cont==0){
        int largura_forma = 300;
        int forma_x = center_x(largura_forma);
        menu.inputs[0]=criar_botao((Rectangle){ forma_x, 150, largura_forma, 35 });
        menu.inputs[1]=criar_botao((Rectangle){ forma_x, 220, largura_forma, 35 });
        menu.input_cont=2;
    }

    DrawText("REMOVER PRODUTO", center_text_x("REMOVER PRODUTO", 25), 20, 25, VERDE);
    
    frontend_scanf(&menu.inputs[0], "Codigo do Produto:");
    frontend_scanf(&menu.inputs[1], "Quantidade a Remover:");
    
    int largura_botao = 100;
    int espaco_botao = 30;
    int botao_x = center_pair_x(largura_botao, espaco_botao);
    int botao_y = 320;

    if(GuiButton((Rectangle){ botao_x, botao_y, largura_botao, 40 }, "Remover")) {
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
    
    if(GuiButton((Rectangle){ botao_x + largura_botao + espaco_botao, botao_y, largura_botao, 40 }, "Voltar")) {
        menu.tela = 12;
        limpar_inputs(&menu);
    }
}

