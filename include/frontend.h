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

texto criar_input(Rectangle bounds);
void desenhar_input_em_texto(texto* input, char* label);
void limpar_inputs(estado* e);

