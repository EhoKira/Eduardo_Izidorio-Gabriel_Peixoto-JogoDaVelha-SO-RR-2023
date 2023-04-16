#include "jogodavelha.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char marks[2] = {'x', 'o'};
int turn = 0;
int finished = 0;
int is_finished_verified = 1;

// Estrutura a ser usada como forma de passar argumentos para a função player_thread. 
typedef struct player_thread_args
{
    jogodavelha *t;
    int mark;
} PlayerThreadArgs;

pthread_mutex_t lock;

void *player_thread(void *v_args)
{
    // "convertendo" argumentos do ponteiro vazio.
    PlayerThreadArgs *args = (PlayerThreadArgs *)v_args;
    jogodavelha *t = args->t;
    int mark = args->mark;

    int x, y;
    // loop principal da thread
    while (1)
    {
        if (finished)
        {
            break;
        }
        // se o turno for igual a mark da thread ('x' = 0 e 'o' = 1), então é a vez dessa thread jogar.
        if (turn == mark)
        {
            //Gera coordenadas dentro do tabuleiro.
            y = rand() % 3;
            x = rand() % 3;
            //Verifica se a jogada é valida. Enquanto o movimento for invalido, tenta novamente com diferentes coordenadas.
            while (!verificaJogo(t, y, x, marks[mark]))
            {
                y = rand() % 3;
                x = rand() % 3;
                if (finished) //Se o jogo terminar durante a escolha da jogada, a thread sairá do loop.
                    break;
            }
            pthread_mutex_lock(&lock); //A thread recebe um bloqueio mutex para garantir que apenas uma thread jogue de cada vez.
            //Se a jogada ainda nao tiver sido registrada e o jogo ainda não tiver acabado, a thread registra a jogada e passa a vez.
            if (is_finished_verified && !finished)
            {
                Jogar(t, y, x, marks[mark]);
                is_finished_verified = 0;
                turn = !turn;
            }
            pthread_mutex_unlock(&lock); //O bloqueio mutex é liberado.
        }
        else //Se nao for a vez da thread jogar, ela executa a condicao abaixo.
        {
            if (!is_finished_verified)
            {
                pthread_mutex_lock(&lock);
                //verifica se alguém ganhou o jogo ou se está cheio.
                if (someoneWin(t) || isFull(t))
                {
                    finished = 1;
                }
                printf("\n");
                printJogoDaVelha(t);
                is_finished_verified = 1;
                pthread_mutex_unlock(&lock);
            }
        }
    }
    // quando sair do loop principal, print a condição final do jogo
    if (!someoneWin(t))
    {
        printf("DEU VELHA !!!\n");
    }
    else if (isWin(t, marks[mark]))
    {
        printf("%c GANHOU !!!\n", marks[mark]);
    }
    else
    {
        printf("%c PERDEU !!!\n", marks[mark]);
    }
}

int main()
{
    clock_t start, end;
    long double cpu_time_used;
    start = clock();

    if (pthread_mutex_init(&lock, NULL) != 0)
        return 1;
    srand(time(NULL));

    jogodavelha *t = criarjogodavelha();
    int turn = 1;

    pthread_t t_player1, t_player2;
    PlayerThreadArgs args1, args2;
    args1.t = t;
    args1.mark = 0;
    args2.t = t;
    args2.mark = 1;

    pthread_create(&t_player1, NULL, &player_thread, &args1);
    pthread_create(&t_player2, NULL, &player_thread, &args2);
    pthread_join(t_player1, NULL);
    pthread_join(t_player2, NULL);

    destroyJogoDaVelha(t);

    end = clock();

    cpu_time_used = ((long double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Lf\n", cpu_time_used);
    return 0;
}