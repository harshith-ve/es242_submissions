#include <stdio.h>
#include <assert.h>

// #include "test.h"

/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */
void init(board_t board) {
    for (int i = 0; i < 15; i++) {
        board[i] = 0;
    }
}
player_t other(player_t player) {
    switch (player) {
        case RED: return 2; break;
        case BLUE: return 1; break;
    }
}
int has_won(board_t board, player_t player) {
    player_t opponent = other(player);
    int all[20][3] = {
        {0, 1, 5},
        {0, 2, 6},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 9},
        {1, 3, 10},
        {1, 4, 11},
        {2, 3, 12},
        {2, 4, 13},
        {3, 4, 14},
        {5, 6, 9},
        {5, 7, 10},
        {5, 8, 11},
        {6, 7, 12},
        {6, 8, 13},
        {7, 8, 14},
        {9, 10, 12},
        {9, 11, 13},
        {10, 11, 14},
        {12, 13, 14}
    };
    for (int i = 0; i < 20; i++) {
        int cont = 0;
        for (int j = 0; j < 3; j++) {
            if (board[all[i][j]] == opponent) {
                cont++;
            }
        }
        if (cont == 3) {
            return 1;
        }
    }
    return 0;
}

int is_full(board_t board) {
    for (int i = 0; i < 15; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player) {
    player_t opponent = other(player);
    move_t move_till_now=(move_t){.line=-1,.score=-1};
    int temp1=10;
    for (int i=0;i<15;i++){
        if (board[i]==0){
            board[i]=player;
            if (has_won(board,opponent)){
                board[i]=0;
                if (move_till_now.score==-1){
                    move_till_now.line=i;
                }
                continue;
            }
            move_t resp=best_move(board,opponent);
            if (resp.score<0){
                move_till_now.line=i;
                move_till_now.score=1-resp.score;
                board[i]=0;
                return move_till_now;
            }
            else{
                int temp=-1-resp.score;
                if (temp<temp1){
                    move_till_now.score=temp;
                    temp1=temp;
                    move_till_now.line=i;
                }
            }
            board[i]=0;
        }
    }
    return move_till_now;
}

void print_board(board_t board) {
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
            case NO: printf(".  "); break;
            case RED: printf("R  "); break;
            case BLUE: printf("B  "); break;
        }
    }
    printf("\n");
}

int main() {
    board_t game;
    init(game);
    
    printf("Welcome to the game!\n");
    printf("Choose your player (1 for Red, 2 for Blue): ");
    int bot;
    int gameOver=0;
    player_t currentPlayer;
    player_t userPlayer;
    player_t computerPlayer;
    scanf("%d",&bot);
    if (bot==1){
        userPlayer =1;
        computerPlayer=2;
        currentPlayer = userPlayer; // Added this line
    }
    else{
        userPlayer=2;
        computerPlayer=1; // Changed this line
        currentPlayer = computerPlayer; // Added this line
    }
    
    printf("Who should play first?\n");
    printf("Enter 1 for user\n");
    printf("Enter 2 for Computer\n");
    
    scanf("%d",&bot);
    
    if (bot==1){
        currentPlayer=userPlayer;
    }
    else{
        currentPlayer=computerPlayer;
    }
    
    while (!gameOver) {
        if (currentPlayer == userPlayer) {
            int userMove;
            printf("Your move (Enter a number between 0 and 14): ");
            scanf("%d", &userMove);
            
            game[userMove] = userPlayer;
        } else {
            move_t computerMove = best_move(game, computerPlayer);
            game[computerMove.line] = computerPlayer;
            printf("Computer's move: %d\n", computerMove.line);
        }
        
        print_board(game);
        
        if (has_won(game,userPlayer)) {
            printf("User has won!\n");
            gameOver = 1;
            break;
        } 
        else if(has_won(game,computerPlayer)){
            printf("Computer has won!\n");
            gameOver =1;
            break;
        }
        else if (is_full(game)) {
            printf("It's a draw!\n");
            gameOver = 1;
            break;
        }
        
        currentPlayer = other(currentPlayer);
    }
    
    printf("Game over.\n");
    
    return 0;
}
