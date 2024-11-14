#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Log* iniciar_log(const char* nome_arquivo) {
    Log* log = malloc(sizeof(Log));
    if (log == NULL) {
        perror("Erro ao alocar memória para o log");
        return NULL;
    }

    snprintf(log->nome_arquivo, sizeof(log->nome_arquivo), "%s", nome_arquivo);
    log->arquivo = fopen(log->nome_arquivo, "w");
    if (log->arquivo == NULL) {
        perror("Erro ao abrir o arquivo de log");
        free(log);
        return NULL;
    }

    return log;
}

void registrar_inicio(Log* log) {
    if (log->arquivo == NULL) return;

    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(log->arquivo, "Início do jogo: %s\n", date);
}

void registrar_jogada(Log* log, int x, int y, char** matUsuario, int tamanho) {
    if (log->arquivo == NULL) return;

    fprintf(log->arquivo, "Jogada: Coordenada (%d, %d)\n", x + 1, y + 1);
    registrar_matriz(log, matUsuario, tamanho);
}

void registrar_matriz(Log* log, char** matUsuario, int tamanho) {
    if (log->arquivo == NULL) return;

    fprintf(log->arquivo, "Estado atual do tabuleiro:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            fprintf(log->arquivo, "%c ", matUsuario[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "\n");
}

void fechar_log(Log* log) {
    if (log->arquivo != NULL) {
        fclose(log->arquivo);
    }
    free(log);
}
