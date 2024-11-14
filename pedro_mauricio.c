#include "matriz.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int** criar_matriz_inteiro(int tamanho)
{   
    int** matriz = malloc(tamanho * sizeof(int*));
    for (int i = 0; i < tamanho; i++) {
        matriz[i] = malloc(tamanho * sizeof(int));
    }

    return matriz;
}

char** criar_matriz_char(int tamanho)
{
    char** matrizUsuario = malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        matrizUsuario[i] = malloc(tamanho * sizeof(char));
    }

    return matrizUsuario;
}

void preenche_matriz_inteiro(int** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            mat[i][j] = 0;
        }
    }
}

void preenche_matriz_char(char** matUsuario, int tamanho)
{   
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matUsuario[i][j] = 'X';
        }
    }
}

void imprime_matriz_inteiro(int** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void imprime_matriz_char(char** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void desalocar_matriz_inteiro(int** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        free(mat[i]);
    }
    free(mat);
}

void desalocar_matriz_char(char** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        free(mat[i]);
    }
    free(mat);
}


/*
    Retorna quantas minas existem ao redor da posicao escolhida, percorrendo todas as oito posicoes ao redor
    Tem como parametros: ponteiro pra uma matriz de inteiros, o tamanho da matriz, e as coordenadas (x,y) da posicao desejada
    Exemplo de uso: contar_minas_redor(matriz, 10, 2, 2); (percorre todas as posicoes ao redor da coordenada (2,2) e conta quantas minas existem ao redor)
*/
int contar_minas_Redor(int** mat, int tamanho, int x, int y) 
{
    int qntMinasPerto = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < tamanho && ny >= 0 && ny < tamanho && mat[nx][ny] == -1) {
                qntMinasPerto++;
            }
        }
    }
    return qntMinasPerto;
}

/*
    Gera coordenadas aleatorias, utilizando a hora do computador, do campo minado para designar como uma bomba, representada pelo numero -1
    Tem como parametros: ponteiro pra uma matriz de inteiros, o tamanho da matriz, e a quantidade de minas que devem ser distribuidas
    Exemplo de uso: distribui_minas(matriz, 10, 15); (distrinui 15 minas aleatoriamente dentro de uma matriz de inteiros com tamanho 10X10)
*/
void distribui_minas(int** mat, int tamanho, int quantidade_minas)
{
    int minasPosicionadas = 0;
    srand(time(NULL));

    while (minasPosicionadas < quantidade_minas) {
        int i = rand() % tamanho;
        int j = rand() % tamanho;

        if (mat[i][j] != -1) {
            mat[i][j] = -1;
            minasPosicionadas++;
        }
    }

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (mat[i][j] == 0) {
                mat[i][j] = contar_minas_Redor(mat, tamanho, i, j);
            }
        }
    }
}

/*
    Revela as posicoes ao redor de uma posicao escolhida pelo jogador de forma recursiva,
    parando somente quando eh encontrada uma celula que possui uma mina ao redor
    Tem como parametros: ponteiro pra uma matriz de inteiros, ponteiro pra uma matriz de caracterez, as coordenadas (x,y) da posicao escolhida e o tamanho das matrizes
    Exemplo de uso: floodFill(matriz, matrizChar, 3, 3, 10); (revela recursivamente as posicoes ao redor da coordenada (3,3) de uma matriz 10X10 ate que se encontre uma celula com mina perto)
*/
void floodFill(int** mat, char** matChar, int x, int y, int tamanho)
{
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
        return;
    }
    if (matChar[x][y] != 'X') {
        return;
    }
    if (mat[x][y] == 0) {
        matChar[x][y] = '0';
    } else {
        matChar[x][y] = '0' + mat[x][y];
        return;
    }
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                floodFill(mat, matChar, x+i, y+j, tamanho);
            }
        }
    }
}

/*
    Processa se a coordenada escolhida pelo jogador eh uma mina ou nao, caso seja uma mina retorna 1 (game over), e caso nao seja uma mina utiliza a funcao floodFill()
    para abrir as celular adjacentes a da coordenada atual
    Tem como parametros: ponteiro pra uma matriz de inteiros, ponteiro pra uma matriz de carcteres, as coordenadas (x,y) da posicao escolhida e o tamanho das matrizes
*/
int processarJogada(int** mat, char** matChar, int x, int y, int tamanho) 
{
    if (mat[x][y] == -1) {
        return 1;
    }
    else if (mat[x][y] == 0) {
        floodFill(mat, matChar, x, y, tamanho);
    } 
    else {
        matChar[x][y] = '0' + mat[x][y];
    }
    return 0;
}

/*
    Responsavel por gerenciar o jogo de campo minado, permitindo a interacao do jogador com o tabuleiro, que seleciona as coordenadas desejadas
    Tem como parametros: ponteiro de uma matriz de inteiros, ponteiro de uma matriz de caracteres, o tamanho das matrizesm e a quantidade total de minad do campo
    Exemplo de uso: adivinhar_posicao(matriz, matrizChar, 10, 15); (utiliza a matriz de inteiros pra verificar as posicoes onde sao bomba, utiliza da matriz de caracteres como tabuleiro para o usuario)
*/

/*
void adivinhar_posicao(int** mat, char** matChar, int tamanho, int qntMinas) 
{
    int x, y;
    int perdeu = 0;
    int acertos = 0;
    int acertosTotais = (tamanho * tamanho) - qntMinas;
    printf("Comece escolhendo uma coordenada (x,y) do tabuleiro!\n");
    while (acertos != acertosTotais && perdeu == 0) {
        printf("escolha uma coordenada (x, y): ");
        if (scanf("%d , %d", &x, &y) != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }
        x = x-1;
        y = y-1;

        if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
            printf("Coordenadas inexistentes! Tente novamente.\n");
            continue;
        }
        if (matChar[x][y] != 'X') {
            printf("Coordenadas repetidas! Tente novamente.\n");
            continue;
        }
        if (processarJogada(mat, matChar, x, y, tamanho) == 1) {
            perdeu = 1;
        } 
        else {
            acertos++;
        }

         imprime_matriz_char(matChar, tamanho);
    }

    if (perdeu == 1) {
        printf("game over\n");
        imprime_matriz_inteiro(mat, tamanho);
    }
    else {
        printf("parabéns, vc eh fera");
        imprime_matriz_inteiro(mat, tamanho);
    }
}
*/

/* 
    Sao definidas variaveis para conter o tamanho das matrizes, a quantidade total de minas do jogo, e a dificuldade que sera escolhida pelo usuario
    primeiramente da opcao de tres dificuldades para o usuario: facil, medio e dificil. De acordo com a escolha da dificuldade eh designado o tamanho do campo
    e a quantidade de minas do campo, apos isso se utilizam das funcoes anteriores pra criar as matrizes e preparar o jogo de campo minado.
*/

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

    fprintf(log->arquivo, "Log do jogo de Campo Minado\n\n");
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

int main(void)
{
    int tamanho, minas;
    char dificuldade[10];

    // Solicita a escolha da dificuldade e define o tamanho e o numero de minas com base na escolha
    printf("Escolha sua dificuldade entre:\n- facil\n- medio\n- dificil\n"); 
    scanf("%9s", dificuldade);

    if (strcmp(dificuldade, "facil") == 0) {
        tamanho = 10;
        minas = 15;
    }
    else if (strcmp(dificuldade, "medio") == 0) {
        tamanho = 20;
        minas = 60;
    }
    else if (strcmp(dificuldade, "dificil") == 0) {
        tamanho = 30;
        minas = 135;
    }

    // Inicializa as matrizes para o campo minado e o tabuleiro visivel ao usuario
    int **campo = criar_matriz_inteiro(tamanho);
    char **tabuleiro = criar_matriz_char(tamanho);
    preenche_matriz_inteiro(campo, tamanho);
    preenche_matriz_char(tabuleiro, tamanho);

    // Inicializa o arquivo de log
    Log* log = iniciar_log("campo_minado.log");
    if (log == NULL) {
        fprintf(stderr, "Erro ao iniciar o log.\n");
        return 1;
    }

    // Registra a data e a hora de inicio do jogo
    registrar_inicio(log);

    // Distribui minas no campo e exibe o tabuleiro inicial
    distribui_minas(campo, tamanho, minas);
    imprime_matriz_char(tabuleiro, tamanho);

    // Inicia o loop de jogadas e registra cada uma no log
    int x, y, perdeu = 0, acertos = 0;
    int acertosTotais = (tamanho * tamanho) - minas;
    printf("Comece escolhendo uma coordenada (x,y) do tabuleiro!\n");
    while (acertos != acertosTotais && perdeu == 0) {
        printf("Escolha uma coordenada (x, y): ");
        if (scanf("%d , %d", &x, &y) != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }
        x = x - 1;
        y = y - 1;

        if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
            printf("Coordenadas inexistentes! Tente novamente.\n");
            continue;
        }
        if (tabuleiro[x][y] != 'X') {
            printf("Coordenadas repetidas! Tente novamente.\n");
            continue;
        }

        // Registra a jogada no log
        registrar_jogada(log, x, y, tabuleiro, tamanho);

        if (processarJogada(campo, tabuleiro, x, y, tamanho) == 1) {
            perdeu = 1;
        } else {
            acertos++;
        }

        imprime_matriz_char(tabuleiro, tamanho);
    }

    // Condição de fim de jogo e registro do estado final
    if (perdeu == 1) {
        printf("game over\n");
        imprime_matriz_inteiro(campo, tamanho);
    } else {
        printf("parabéns, você venceu!\n");
        imprime_matriz_inteiro(campo, tamanho);
    }

    // Fecha o log e libera a memória
    fechar_log(log);
    desalocar_matriz_inteiro(campo, tamanho);
    desalocar_matriz_char(tabuleiro, tamanho);
}