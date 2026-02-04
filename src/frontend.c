#include "../include/frontend.h"

texto criar_input(Rectangle bounds){
    texto input = {0};
    input.limites = bounds;
    input.ativo = false;
    memset(input.texto, 0, 256);
    //só pra limpar se tiver problema de alguma coisa q ficou perdida ai ou seila
    return input;
}

void desenhar_input_em_texto(texto* input, char* label){

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

void limpar_inputs(estado* e){
    for (int i = 0; i < e->input_cont; i++) {
        memset(e->inputs[i].texto, 0, 300); 
        e->inputs[i].ativo = false;
    }
    e->input_cont = 0;
}
