#include "frontend.h"

Menu menu;

void tela_menu_principal() {
    
    Drawtexto("========== MENU PRINCIPAL ==========", 200, 30, 25, VERDE);
    
    int button_x = 150;
    int button_y = 100;
    int button_width = 300;
    int button_height = 40;
    int spacing = 50;
    
    if (GuiButton((Rectangle){ button_x, button_y, button_width, button_height }, "01: Cadastrar Cliente")) {
        menu.tela = 1;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x, button_y + spacing, button_width, button_height }, "02: Buscar Cliente")) {
        menu.tela = 2;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x, button_y + spacing * 2, button_width, button_height }, "03: Editar Cliente")) {
        menu.tela = 3;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x, button_y + spacing * 3, button_width, button_height }, "04: Listar Clientes")) {
        menu.tela = 4;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x, button_y + spacing * 4, button_width, button_height }, "05: Deletar Cliente")) {
        menu.tela = 5;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x, button_y + spacing * 5, button_width, button_height }, "06: Cadastrar Produto")) {
        menu.tela = 6;
        limpar_inputs(&menu);
    }
    
    if (GuiButton((Rectangle){ button_x + 350, button_y, button_width, button_height }, "07: Listar Produtos")) {
        menu.tela = 7;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x + 350, button_y + spacing, button_width, button_height }, "08: Remover Produto")) {
        menu.tela = 8;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x + 350, button_y + spacing * 2, button_width, button_height }, "09: Editar Produto")) {
        menu.tela = 9;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x + 350, button_y + spacing * 3, button_width, button_height }, "10: Começar Compras")) {
        menu.tela = 10;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x + 350, button_y + spacing * 4, button_width, button_height }, "11: Ver Histórico")) {
        menu.tela = 11;
        limpar_inputs(&menu);
    }
    if (GuiButton((Rectangle){ button_x + 350, button_y + spacing * 5, button_width, button_height }, "00: Sair")) {
        menu.tela = -1;
    }
    
}

void tela_cadastro_cliente(){
    //preparando as caixinhas 
    if(menu.input_cont==0){
        menu.inputs[0] = criar_input((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_input((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_input((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_input((Rectangle){ 200, 310, 300, 35 });
        menu.inputs[4] = criar_input((Rectangle){ 200, 380, 300, 35 });
        menu.inputs[5] = criar_input((Rectangle){ 200, 450, 300, 35 });
        menu.input_cont = 6;
    }

    DrawText("CADASTRO DE CLIENTE", 150, 20, 25, AMARELO);
    
    //lembrando que o q ta em aspas e o label/titulo do bottao
    desenhar_input_em_texto(&menu.inputs[0], "Nome:");
    desenhar_input_em_texto(&menu.inputs[1], "CPF (11 digitos):");
    desenhar_input_em_texto(&menu.inputs[2], "Telefone:");
    desenhar_input_em_texto(&menu.inputs[3], "Senha:");
    desenhar_input_em_texto(&menu.inputs[4], "Data Nascimento (DD/MM/AAAA):");
    desenhar_input_em_texto(&menu.inputs[5], "Email:");

    if(GuiButton((Rectangle){200,580,100,40}, "Salvar")){

        if(strlen(menu.inputs[0].texto)>0 && strlen(menu.inputs[1].texto)>0){
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
    
    if (GuiButton((Rectangle){ 350, 580, 100, 40 }, "Voltar")) {
        menu.tela = 0;
        limpar_inputs(&menu);
    }
    
}

void tela_busca_cliente(){
    if(menu.input_cont==0){
        menu.inputs[0]=criar_input((Rectangle){200, 150, 300, 35});
        menu.input_cont=1;
    }
    
    DrawText("BUSCAR CLIENTE", 150, 20, 25, AMARELO);
    
    desenhar_input_em_texto(&menu.inputs[0], "CPF:");
    
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
        menu.inputs[0] = criar_input((Rectangle){ 200, 100, 300, 35 });
        menu.inputs[1] = criar_input((Rectangle){ 200, 170, 300, 35 });
        menu.inputs[2] = criar_input((Rectangle){ 200, 240, 300, 35 });
        menu.inputs[3] = criar_input((Rectangle){ 200, 310, 300, 35 });
        menu.inputs[4] = criar_input((Rectangle){ 200, 380, 300, 35 });
        menu.inputs[5] = criar_input((Rectangle){ 200, 450, 300, 35 });
        menu.inputs[6] = criar_input((Rectangle){ 200, 520, 300, 35 });
        menu.input_cont = 7;
    }
    
    DrawText("EDITAR CLIENTE", 150, 20, 25, AMARELO);
    
    desenhar_input_em_texto(&menu.inputs[0], "CPF Original:");
    desenhar_input_em_texto(&menu.inputs[1], "Novo Nome:");
    desenhar_input_em_texto(&menu.inputs[2], "Novo Telefone:");
    desenhar_input_em_texto(&menu.inputs[3], "Nova Senha:");
    desenhar_input_em_texto(&menu.inputs[4], "Nova Data (DD/MM/AAAA):");
    desenhar_input_em_texto(&menu.inputs[5], "Novo Email:");
    desenhar_input_em_texto(&menu.inputs[6], "Novo CPF:");
    
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







