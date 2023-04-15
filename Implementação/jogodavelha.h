//Esse é um arquivo de cabeçalho em C que contém a declaração de uma estrutura de dados chamada
//TicTacToe (Jogo da velha) e as declarações de suas funções associadas.

//A estrutura de dados TicTacToe contém uma matriz de caracteres de tamanho 3x3 que 
//representa o tabuleiro do jogo da velha.

//E suas funções são:

#ifndef _JOGODAVELHA_H_
#define _JOGODAVELHA_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct jogodavelha {
    char table[3][3];
} jogodavelha;

jogodavelha* criarjogodavelha(); //inicializa o tabuleiro do jogo da velha com espaço em branco.
void destroyJogoDaVelha(jogodavelha* t); //libera a mem alocada para uma instância.
void printJogoDaVelha(jogodavelha* t); //exibi o tabuleiro do jogo da velha no console.
int verificaJogo(jogodavelha* t, int i, int j, char mark); //verifica se uma jogada com a marcação "mark" é válida no tabuleiro "t".
int Jogar(jogodavelha* t, int i, int j, char mark); // executa uma jogada (i,j) com a marcação "mark" no tabuleiro "t".
int isWin(jogodavelha* t, char mark); // verifica se uma marcação "mark" ganhou o jogo no tabuleiro "t".
int isFull(jogodavelha* t); // verifica se o tabuleiro "t" está completamente preenchido.
int someoneWin(jogodavelha* t); // verifica se alguém ganhou o jogo no tabuleiro "t". Se sim, retorna 1; caso contrário, retorna 0.

#endif 

//O uso de #ifndef, #define e #endif é uma técnica de programação conhecida como "inclusão de guarda" que previne a redefinição das declarações
//de cabeçalho caso o arquivo seja incluído mais de uma vez em um mesmo programa.