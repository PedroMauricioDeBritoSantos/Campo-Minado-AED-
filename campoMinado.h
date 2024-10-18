#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int TAMANHO, MINAS;

// define o tamanho do campo minado
void setTamanho(int x)
{
    TAMANHO = x;;
}

// retorna o tamanho do campo minado
int getTamanho()
{
    return TAMANHO;
}

// define a quantidade de minas no campo
void setMinas(int x)
{
    MINAS = x;
}

// retorna a quantidade de minas no campo
int getMinas()
{
    return MINAS; 
}

/* pede para o usuário escolher a dificuldade (fácil, médio, difícil)
 e ajusta o tamanho do campo e a quantidade de minas com base na dificuldade
*/ 
void setDificuldade()
{
    char dificuldade[10];

    printf("Escolha sua dificuldade entre:\nfacil\nmedio\ndificil\n");
    scanf("%9s", dificuldade);

    if (strcmp(dificuldade, "facil") == 0) {
        setTamanho(10);
        setMinas(3);
    } else if (strcmp(dificuldade, "medio") == 0) {
        setTamanho(20);
        setMinas(6);
    } else if (strcmp(dificuldade, "dificil") == 0) {
        setTamanho(30);
        setMinas(9);
    } else {
        printf("Dificuldade inválida!");
    }
}

/* cria e retorna uma matriz de inteiros de tamanho definido */
int** criarMatriz(int tamanho)
{   
    int** matriz = malloc(tamanho * sizeof(int*));
    for (int i = 0; i < tamanho; i++) {
        matriz[i] = malloc(tamanho * sizeof(int));
    }
    return matriz;
}

/* cria e retorna uma matriz de caracteres de tamanho definido para o usuário */
char** criarMatrizUsuario(int tamanho)
{
    char** matrizUsuario = malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        matrizUsuario[i] = malloc(tamanho * sizeof(char));
    }
    return matrizUsuario;
}

// preenche toda a matriz com zeros
void preencheMatriz(int** mat, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            mat[i][j] = 0;
        }
    }
}

// preenche toda a matriz de caracteres do usuário com 'X'
void preencheMatrizUsuario(char** matUsuario, int tamanho)
{   
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matUsuario[i][j] = 'X';
        }
    }
}

// distribui aleatoriamente as minas (representadas por -1) na matriz
void distribuiMinas(int** mat, int tamanho, int QuantidadeMinas)
{
    int minasPosicionadas = 0;
    srand(time(NULL));

    while (minasPosicionadas < QuantidadeMinas) {
        int i = rand() % tamanho;
        int j = rand() % tamanho;

        if (mat[i][j] != -1) {
            mat[i][j] = -1;
            minasPosicionadas++;
        }
    }
}

// imprime a matriz de inteiros
void imprimeMatriz(int** mat)
{
    for (int i = 0; i < getTamanho(); i++) {
        for (int j = 0; j < getTamanho(); j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// imprime a matriz de caracteres do usuário
void imprimeMatrizUsuario(char** mat)
{
    for (int i = 0; i < getTamanho(); i++) {
        for (int j = 0; j < getTamanho(); j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// conta quantas minas existem ao redor de uma posição (x, y)
int contarMinasAoRedor(int** mat, int tamanho, int x, int y) 
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

// processa a jogada do usuário, atualiza a matriz do usuário e verifica se há uma mina na posição escolhida
void processarJogada(int** mat, char** matUsuario, int tamanho, int x, int y) 
{
    if (mat[x][y] == -1) {
        printf("Game over\n");
        matUsuario[x][y] = '*';
    } else {
        int qntMinasPerto = contarMinasAoRedor(mat, tamanho, x, y);
        matUsuario[x][y] = '0' + qntMinasPerto;
    }
}

/* gerencia a lógica do jogo, permitindo que o usuário adivinhe posições e atualize a matriz do usuário
   interrompe quando se escolhe uma mina ou se o usuário acerta todas a posições */
void adivinharPosicao(int** mat, char** matUsuario, int tamanho, int qntMinas) {
    int x, y;
    int perdeu = 0;
    int acertos = 0;
    int acertosTotais = (tamanho * tamanho) - qntMinas;
    printf("Comece escolhendo uma coordenada (x,y) do tabuleiro!\n");
    while (scanf("%d %d", &x, &y), acertos != acertosTotais && perdeu == 0) {
        if (mat[x][y] == -1) {
            printf("game over\n");
            matUsuario[x][y] = '*';
            perdeu = 1;
        } else {
            processarJogada(mat, matUsuario, tamanho, x, y);
            acertos++;
        }
        imprimeMatrizUsuario(matUsuario);
    }
    if (perdeu == 0) {
        printf("parabéns, vc eh fera\n");
        imprimeMatriz(mat);
    }
}


// desaloca a matriz da memória
void desalocarMatriz(int** mat)
{
    for (int i = 0; i < getTamanho(); i++) {
        free(mat[i]);
    }
    free(mat);
}

// utiliza todas as funções anteriores para configurar e iniciar o jogo de campo minado
void criarCampoMinado() {
    setDificuldade();
    int** campoMinado = criarMatriz(getTamanho());
    char** tabuleiro = criarMatrizUsuario(getTamanho());
    preencheMatriz(campoMinado, getTamanho());
    preencheMatrizUsuario(tabuleiro, getTamanho());
    distribuiMinas(campoMinado, getTamanho(), getMinas());
    imprimeMatrizUsuario(tabuleiro);
    adivinharPosicao(campoMinado, tabuleiro, getTamanho(), getMinas());
}