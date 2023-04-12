#include <stdio.h>

char board[3][3]; // tabuleiro do jogo

void init_board()
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
}

void print_board()
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int check_winner(char player)
{
    int i, j;
    // checa linhas
    for (i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }
    }
    // checa colunas
    for (j = 0; j < 3; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
        {
            return 1;
        }
    }
    // checa diagonais
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return 1;
    }
    return 0;
}

void play_game()
{
    char player = 'X';
    int row, col;
    int turn = 0;
    init_board();
    while (turn < 9)
    {
        printf("Jogador %c, digite a linha (0 a 2) e coluna (0 a 2) da jogada: ", player);
        scanf("%d %d", &row, &col);
        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Jogada inválida. Tente novamente.\n");
            continue;
        }
        if (board[row][col] != '-')
        {
            printf("Espaço ocupado. Tente novamente.\n");
            continue;
        }
        board[row][col] = player;
        print_board();
        if (check_winner(player))
        {
            printf("Jogador %c venceu!\n", player);
            return;
        }
        turn++;
        player = turn % 2 == 0 ? 'O' : 'X';
    }
    printf("Empate!\n");
}

int main()
{
    play_game();
    return 0;
}

// Neste código, a função init_board() inicializa o tabuleiro com '-' em todas as posições.
// A função print_board() imprime o tabuleiro na tela. A função check_winner() verifica se algum jogador ganhou o jogo.
// A função play_game() é a função principal que controla o jogo, alternando entre os jogadores e verificando se alguém ganhou ou se houve empate.
// A função main() chama a função play_game().

