#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PLAYER 0
#define COMPUTER 1

#define EMPTY 0
#define PLAYER_PIECE 1
#define COMPUTER_PIECE 2

#define BOARD_SIZE 3

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int turn;
} GameState;

typedef struct {
    int row;
    int col;
    int score;
} Move;

void display_board(GameState *state) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == EMPTY) {
                printf(" - ");
            } else if (state->board[i][j] == PLAYER_PIECE) {
                printf(" X ");
            } else {
                printf(" O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int game_over(GameState *state) {
    int i, j;
    int sum;

    // check rows
    sum = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            sum += state->board[i][j];
        }
        if (sum == PLAYER_PIECE * BOARD_SIZE) {
            return PLAYER;
        } else if (sum == COMPUTER_PIECE * BOARD_SIZE) {
            return COMPUTER;
        }
    }

    // check columns
    for (j = 0; j < BOARD_SIZE; j++) {
        sum = 0;
        for (i = 0; i < BOARD_SIZE; i++) {
            sum += state->board[i][j];
        }
        if (sum == PLAYER_PIECE * BOARD_SIZE) {
            return PLAYER;
        } else if (sum == COMPUTER_PIECE * BOARD_SIZE) {
            return COMPUTER;
        }
    }

    // check diagonals
    sum = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        sum += state->board[i][i];
    }
    if (sum == PLAYER_PIECE * BOARD_SIZE) {
        return PLAYER;
    } else if (sum == COMPUTER_PIECE * BOARD_SIZE) {
        return COMPUTER;
    }

    sum = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        sum += state->board[i][BOARD_SIZE - i - 1];
    }
    if (sum == PLAYER_PIECE * BOARD_SIZE) {
        return PLAYER;
    } else if (sum == COMPUTER_PIECE * BOARD_SIZE) {
        return COMPUTER;
    }

    // check for tie
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == EMPTY) {
                return -1;
            }
        }
    }
    return EMPTY;
}

int minimax(GameState *state, int player) {
    int result = game_over(state);
    if (result != EMPTY) {
        if (result == PLAYER) {
            return -1;
        } else if (result == COMPUTER) {
            return 1;
        } else {
            return 0;
        }
    }

    int best_score;
    int i, j;
    Move move;
    if (player == COMPUTER) {
       
    best_score = -100;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == EMPTY) {
                state->board[i][j] = COMPUTER_PIECE;
                move.row = i;
                move.col = j;
                move.score = minimax(state, PLAYER);
                state->board[i][j] = EMPTY;
                if (move.score > best_score) {
                    best_score = move.score;
                }
            }
        }
    }
} else {
    best_score = 100;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == EMPTY) {
                state->board[i][j] = PLAYER_PIECE;
                move.row = i;
                move.col = j;
                move.score = minimax(state, COMPUTER);
                state->board[i][j] = EMPTY;
                if (move.score < best_score) {
                    best_score = move.score;
                }
            }
        }
    }
}
return best_score;
}

void *computer_move(void *arg) {
    GameState *state = (GameState *) arg;
    int best_score = -100;
    int i, j;
    Move move;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == EMPTY) {
                state->board[i][j] = COMPUTER_PIECE;
                move.row = i;
                move.col = j;
                move.score = minimax(state, PLAYER);
                state->board[i][j] = EMPTY;
                if (move.score > best_score) {
                    best_score = move.score;
                    state->board[move.row][move.col] = COMPUTER_PIECE;
                }
            }
        }
    }
    state->turn = PLAYER;
    pthread_exit(NULL);

}

int main() {
    GameState *state = (GameState *) malloc(sizeof(GameState));
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
        state->board[i][j] = EMPTY;
    }
}

    state->turn = PLAYER;

    pthread_t computer_thread;

    while (1) {
        if (state->turn == PLAYER) {
            int row, col;
            printf("Enter row (0-2) and column (0-2) separated by a space: ");
            scanf("%d %d", &row, &col);

            if (state->board[row][col] != EMPTY) {
                printf("That space is already occupied. Try again.\n");
            } else {
                state->board[row][col] = PLAYER_PIECE;
                state->turn = COMPUTER;
            }
        } else {
            pthread_create(&computer_thread, NULL, computer_move, (void *) state);
            pthread_join(computer_thread, NULL);
            state->turn = PLAYER;
        }

    display_board(state);

    int result = game_over(state);
    if (result != EMPTY) {
        if (result == PLAYER) {
            printf("You win!\n");
        } else if (result == COMPUTER) {
            printf("You lose!\n");
        } else {
            printf("Tie game!\n");
        }
        break;
    }
}

free(state);

return 0;
}
