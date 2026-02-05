#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct {
    char operacao[200];
    char timestamp[20];
} Registro;

typedef struct NoHistorico {
    Registro dados;
    struct NoHistorico* proximo;
} NoHistorico;

typedef struct {
    NoHistorico* inicio;
    int total;
} Historico;

Historico* criar_historico();
void adicionar_registro(Historico* hist, const char* operacao);
void exibir_historico(Historico* hist);
void limpar_historico(Historico* hist);
NoHistorico* obter_ultimos_n_registros(Historico* hist, int n);

#endif