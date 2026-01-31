#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/historico.h"

Historico* criar_historico() {
    Historico* hist = malloc(sizeof(Historico));
    if(hist == NULL) return NULL;
    hist->inicio = NULL;
    hist->total = 0;
    return hist;
}

void adicionar_registro(Historico* hist, const char* operacao) {
    if(hist == NULL) return;

    NoHistorico* novo = malloc(sizeof(NoHistorico));
    if(novo == NULL) return;

    time_t agora = time(NULL);
    struct tm* info = localtime(&agora);
    strftime(novo->dados.timestamp, 20, "%H:%M:%S", info);

    strncpy(novo->dados.operacao, operacao, 199);
    novo->dados.operacao[199] = '\0';
    novo->proximo = NULL;

    novo->proximo = hist->inicio;
    hist->inicio = novo;
    hist->total++;
}

void exibir_historico(Historico* hist) {
    if(hist == NULL || hist->total == 0) {
        printf("\nHistorico vazio!\n");
        return;
    }

    printf("\n========== HISTORICO DE OPERACOES ==========\n");
    printf("Total de operacoes: %d\n\n", hist->total);

    NoHistorico* atual = hist->inicio;
    int contador = 1;

    while(atual != NULL) {
        printf("%d. [%s] %s\n", contador, atual->dados.timestamp, atual->dados.operacao);
        atual = atual->proximo;
        contador++;
    }

    printf("==========================================\n");
}

void limpar_historico(Historico* hist) {
    if(hist == NULL) return;

    NoHistorico* atual = hist->inicio;
    while(atual != NULL) {
        NoHistorico* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    hist->inicio = NULL;
    hist->total = 0;
}