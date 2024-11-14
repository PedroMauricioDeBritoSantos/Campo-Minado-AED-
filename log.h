#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

/*
    Estrutura do Log, possuindo um ponteiro pro arquivo onde o log sera gravado
    e um array de caracteres pra armazenar o nome do arquivo
*/
typedef struct {
    FILE *arquivo;
    char nome_arquivo[100];
} Log;

/*
    Inicializa o log criando e abrindo o arquivo de log
    Tem como parametros: nome do arquivo em que o log ficara registrado
*/
Log* iniciar_log(const char* nome_arquivo);

/*
    registra a data e hora de inicio do jogo no log
    Tem como parametros: ponteiro para a estrutura log contendo o arquivo de log aberto
*/
void registrar_inicio(Log* log);

/*
    Registra uma jogada no log, incluindo coordenadas e o estado atual do tabuleiro
    Tem como parametros: ponteiro pra estrutura log, coordenadas usadas pelo jogador, ponteiro pra matriz de caracteres e o tamanho da matriz do tabuleiro
*/
void registrar_jogada(Log* log, int x, int y, char** matUsuario, int tamanho);

/*
    Registra o estado atual do tabuleiro no log
    Tem como parametros: ponteiro pra estrutura log contendo o arquivo log, ponteiro para matriz de caracteres e o tamanho da matriz do tabuleiro
*/
void registrar_matriz(Log* log, char** matUsuario, int tamanho);

/*
    Encerra o uso do log, fechando o arquivo e liberando a estrutura
    Tem como parametros: ponteiro pra estrutura log que contem o arquivo log
*/
void fechar_log(Log* log);

#endif