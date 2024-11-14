#ifndef MATRIZ_H
#define MATRIZ_H

/* 
    Cria uma matriz dinamica de inteiros com formato tamanhoXtamanho
    Tem como unico parametro o tamanho desejado para a matriz
    Retorna um ponteiro para a matriz de inteiros dinamicamente alocada
    Exemplo de uso: int **matriz = criar_matriz_inteiro(10); (cria uma matriz de inteiros com tamanho 10X10)
*/
int **criar_matriz_inteiro(int tamanho);

/*
    Cria uma matriz dinamica de caracteres com formato tamanhoXtamanho
    Tem como unico parametro o tamanho desejado para a matriz
    Retorna um ponteiro para a matriz de caracteres dinamicamente alocada
    Exemplo de uso: char **matriz = criar_matriz_char(10); (cria uma matriz de caracteres com tamanho 10X10)
*/
char **criar_matriz_char(int tamanho);

/*
    Preenche a matriz de inteiros com o valor 0 em todas as posicoes
    Tem como parametros: ponteiro pra uma matriz de inteiros e o tamanho da matriz
    Exemplo de uso: preenche_matriz_inteiro(matriz, 10); (preenche todos os elementos de uma matriz 10X10 com 0)
 */
void preenche_matriz_inteiro(int** mat, int tamanho);

/*
    Preenche a matriz de caracteres com o caractere 'X' em todas as posicoes
    Tem como parametros: ponteiro pra uma matriz de caracteres e o tamanhon da matriz
    Exemplo de uso: preenche_matriz_char(matrizChar, 10); (preenche todos os elementos de uma matriz 10X10 com o caractere 'X')
*/
void preenche_matriz_char(char** matChar, int tamanho);

/*
    Imprime uma matriz de inteiros no terminal
    Tem como parametros: ponteiro para uma matriz de inteiros e o tamanho da matriz
    Exemplo de uso: imprime_matriz_inteiro(matriz, 10); (imprime uma matriz 10X10 no terminal)
*/
void imprime_matriz_inteiro(int** mat, int tamanho);

/*
    Imprime uma matriz de caracteres no terminal
    Tem como parametros: ponteiro pra uma matriz de caracteres e o tamanho da matriz
    Exemplo de uso: imprime_matriz_char(matrizChar, tamanho); (imprime uma matriz de caracteres 10X10 no terminal)
*/
void imprime_matriz_char(char** mat, int tamanho);

/*
    Libera a memoria alocada para uma matriz de inteiros
    Tem como parametros: ponteiro pra uma matriz de inteiros e o tamanho da matriz
    Exemplo de uso: desalocar_matriz_inteiro(matriz, 10); (libera a memoria de uma matriz de inteitos 10X10)
*/
void desalocar_matriz_inteiro(int** mat, int tamanho);

/*
    Libera a memoria alocada para uma matriz de caracteres
    Tem como parametros: ponteiro pra uma matriz de caracteres e o tamanho da matriz
    Exemplo de uso: desalocar_matriz_char(matrizChar, 10); (libera a memoria de uma matriz de caracteres 10X10)
*/
void desalocar_matriz_char(char **mat, int tamanho);

#endif