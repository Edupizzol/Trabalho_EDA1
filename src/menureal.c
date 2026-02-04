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