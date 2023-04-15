#include "jogodavelha.h"

char empty = '-';

jogodavelha* criarjogodavelha(){
    
    // aloca dinamicamente a struct TicTacToe
    jogodavelha* t = (jogodavelha*)malloc(sizeof(jogodavelha));

    // coloca todos os elementos da tabela como o char vazio ('-')
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            t->table[i][j] = empty;
    
    // retorna t
    return t;
}

void destroyJogoDaVelha(jogodavelha* t){
    // libera o espaço na memoria
    free(t);
}

void printJogoDaVelha(jogodavelha* t){
    // printa os elementos da tabela
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            printf("%c ", t->table[i][j]);
        printf("\n");
    }
}

int verificaJogo(jogodavelha* t, int i, int j, char mark){
    if (t->table[i][j] != empty)
        return 0;
    return 1;
}

int Jogar(jogodavelha* t, int i, int j, char mark){
    if (!verificaJogo(t, i, j, mark))
        return 0;
    
    t->table[i][j] = mark;
    return 1;
}

int isWin(jogodavelha* t, char mark){
    int i, j;

    // verificar se um dos jogadores ganhou no tabuleiro
    
    // >> vertical
    for (i = 0; i < 3; i++)
        if(t->table[i][0] == mark && t->table[i][1] == mark && t->table[i][2] == mark)
            return 1;
    
    // >> horizontal
    for (j = 0; j < 3; j++)
        if(t->table[0][j] == mark && t->table[1][j] == mark && t->table[2][j] == mark)
            return 1;
    
    // >> diagonal principal e secundaria
    if(t->table[0][0] == mark && t->table[1][1] == mark && t->table[2][2] == mark)
        return 1;
    if(t->table[0][2] == mark && t->table[1][1] == mark && t->table[2][0] == mark)
        return 1;
    

    // não ganhou
    return 0;
}

int someoneWin(jogodavelha* t){
    int i, j;

    // verificar
    // >> vertical
    for (i = 0; i < 3; i++)
        if(t->table[i][0] == t->table[i][1] && t->table[i][1] == t->table[i][2] && t->table[i][2] != empty)
            return 1;
    
    // >> horizontal
    for (j = 0; j < 3; j++)
        if(t->table[0][j] == t->table[1][j] && t->table[1][j] == t->table[2][j] && t->table[2][j] != empty)
            return 1;
    
    // >> diagonal principal e secundaria
    if(t->table[0][0] == t->table[1][1] && t->table[1][1] == t->table[2][2] && t->table[2][2] != empty)
        return 1;
    if(t->table[0][2] == t->table[1][1] && t->table[1][1] == t->table[2][0] && t->table[2][0] != empty)
        return 1;

    // não ganhou
    return 0;
}

int isFull(jogodavelha* t){
    // verifica elemento por elemento da tabela, se algum deles for igual
    // ao elemento vazio, returna 0/False (não cheio).
    // caso contrario, retorna 1/True (cheio).
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if(t->table[i][j] == empty){
                return 0;
            }
        }
    }
    return 1;
}