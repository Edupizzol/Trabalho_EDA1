#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#ifndef TextToFloat
    #define TextToFloat atof
#endif
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "../include/menu.h"

static const char* CLIENTES_FILE = "clientes.csv";
static const char* PRODUTOS_FILE = "produtos.csv";

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
#define VERDE (Color){0, 200, 0, 255}
#define ROXO (Color){128, 0, 128, 255}
#define AMARELO (Color){255, 255, 0, 255}
#define VERMELHO (Color){255, 0, 0, 255}

typedef struct texto{
    char texto[300];
    bool ativo;
    Rectangle limites;
}texto;

typedef struct estado{
    int tela;
    NodeCliente* cliente;
    Produto* produto;
    Historico* historico;
    texto inputs[10];
    int input_cont;
}estado;

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


