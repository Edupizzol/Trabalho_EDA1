#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#ifndef TextToFloat
    #define TextToFloat atof
#endif
#include "raygui.h"
#include "../include/carrinho.h"
#include "../include/historico.h"

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

typedef struct Menu{
    int tela;
    NodeCliente* cliente;
    Produto* produto;
    Historico* historico;
    texto inputs[10];
    Carrinho* carrinho;
    NodeCliente* cliente_logado;
    int input_cont;
    bool resultado_visivel;
    bool resultado_sucesso;
    bool aviso_visivel;
    char aviso_mensagem[256];
    float aviso_tempo;
}Menu;

texto criar_botao(Rectangle bounds);
void frontend_scanf(texto* input, char* label);
void limpar_inputs(Menu* e);
void mostrar_aviso(Menu* menu, const char* mensagem);
void desenhar_aviso(Menu* menu);

#endif

