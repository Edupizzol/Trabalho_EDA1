#include "../include/frontend.h"

texto criar_botao(Rectangle bounds){
    texto input = {0};
    input.limites = bounds;
    input.ativo = false;
    memset(input.texto, 0, 256);
    //só pra limpar se tiver problema de alguma coisa q ficou perdida ai ou seila
    return input;
}

void frontend_scanf(texto* input, char* label){

    Color corFundo;
    Color corBorda;

    if (input->ativo) {
        corFundo = LIGHTGRAY;
        corBorda = BLUE;    
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125)){
                int len = strlen(input->texto);
                input->texto[len] = (char)key;
                input->texto[len + 1] = '\0';
            }
            key = GetCharPressed();
        }
        
        if (IsKeyPressed(KEY_BACKSPACE)) {
            int len = strlen(input->texto);
            if (len > 0) input->texto[len - 1] = '\0';
        }  
    }
    else{
        corFundo = WHITE;     
        corBorda = GRAY;      
    }

    DrawRectangleRec(input->limites, corFundo);
    //lembrando que o 2 e pq essa e a grossura da bordinha da caixa
    DrawRectangleLinesEx(input->limites, 2, corBorda);

    //essas funcoes sao simplesmente pra fazer o texto aparecer, bom lembrar que por algum motivo quem 
    //criou isso fez o y comecar pra baixo, entao subtrair 25 move 25 unidades pra cima e vice versa
    DrawText(label, input->limites.x, input->limites.y - 25, 15, BLACK);
    DrawText(input->texto, input->limites.x + 5, input->limites.y + 8, 15, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), input->limites) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        input->ativo = true;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        input->ativo = false;
    }

}

void limpar_inputs(Menu* e){
    for (int i = 0; i < e->input_cont; i++) {
        memset(e->inputs[i].texto, 0, 300); 
        e->inputs[i].ativo = false;
    }
    e->input_cont = 0;
}

void mostrar_aviso(Menu* menu, const char* mensagem) {
    menu->aviso_visivel = true;
    strncpy(menu->aviso_mensagem, mensagem, 199);
    menu->aviso_mensagem[199] = '\0';
    menu->aviso_tempo = 2.0f; //coloquei 2 segundos mas da pra mudar depois
}

void desenhar_aviso(Menu* menu) {
    if(!menu->aviso_visivel){return;};
    menu->aviso_tempo -= GetFrameTime();
    
    if (menu->aviso_tempo <= 0) {
        menu->aviso_visivel = false;
        menu->tela = 0;
        limpar_inputs(menu);
        return;
    }
    
    //coloca um fundo escuro
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 150});
    
    //desenha a caixinha com as bordas vermelhas
    Rectangle aviso_box = (Rectangle){200, 250, 600, 150};
    DrawRectangleRec(aviso_box, WHITE);
    DrawRectangleLinesEx(aviso_box, 3, VERMELHO);
    
    //aqui novamente adaptacao do printf pro frontend
    DrawText("AVISO!", 450, 280, 25, VERMELHO);
    DrawText(menu->aviso_mensagem, 220, 330, 18, BLACK);
    DrawText(TextFormat("Retornando em %.1f s", menu->aviso_tempo), 350, 370, 14, GRAY);
}
