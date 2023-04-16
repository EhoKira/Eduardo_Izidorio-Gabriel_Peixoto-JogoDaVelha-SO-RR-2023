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
        // se o turno for igual a mark da thread ('x' = 0 e 'o' = 1), então é a
        // vez dessa thread jogar.
        if (turn == mark)
        {
            // enquanto o movimento for invalido (espaço já ocupado), tenta novamente
            // com diferentes coordenadas.
            y = rand() % 3;
            x = rand() % 3;
            while (!verificaJogo(t, y, x, marks[mark]))
            {
                y = rand() % 3;
                x = rand() % 3;
                if (finished)
                    break;
            }
            pthread_mutex_lock(&lock);
            if (is_finished_verified && !finished)
            {
                Jogar(t, y, x, marks[mark]);
                is_finished_verified = 0;
                turn = !turn;
            }
            pthread_mutex_unlock(&lock);
        }
        else
        {
            if (!is_finished_verified)
            {
                pthread_mutex_lock(&lock);
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