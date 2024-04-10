#include <stdio.h>
#include <conio.h>
char BOARD[9] =  {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
// winning lines size
int WLS = 8;
//winning lines array contains the positions that make a winner
int winning_lines[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 98}, {2, 4, 6}, {0, 4, 8}};


typedef struct Player Player;
struct Player
{
    char name[20];
    int score;
    char symbol;
};

struct Game
{
    Player player1;
    Player player2;
    int rounds;
};


void printBoard();
int thereIsAWinner();
void startGame();
void playRound(Player*, Player*);
unsigned playAgain();
void swap(Player *, Player *);
void updateBoard(char , int);
int getChoice(char *);
unsigned validChoice(int);
void resetBoard();


int main()
{
    startGame();
    return 0;
}

void playRound(Player *player1, Player *player2)
{
    Player *currentPlayer, *previousPlayer;
    currentPlayer = player1; 
    previousPlayer = player2;
    int choice, count = 0;
    while (count < 9)
    {
        printBoard();
        choice = getChoice(currentPlayer->name);
        updateBoard(currentPlayer->symbol, choice);
        if (thereIsAWinner() == 1)
        {
            printBoard();
            currentPlayer->score++;
            printf("%s won this round.", currentPlayer->name);
            return;
        }
        count++;
        swap(currentPlayer, previousPlayer);
    }
    printf("Tie game.\n");
}
void startGame()
{
    Player player1, player2;

    printf("WELCOME TO TIC-TAC-TOE!\n");


    printf("Enter player1's name : "); scanf("%s", player1.name);
    printf("Enter player2's name : "); scanf("%s", player2.name);

    player1.symbol = 'X'; player1.score = 0;
    player2.symbol = 'O'; player2.score = 0;

    do 
    {
        printf("\n");
        playRound(&player1, &player2);
        resetBoard();
        swap(&player1, &player2);
    }while (playAgain());

}
void resetBoard()
{
    for (int i = 0; i < 9; i++)
        BOARD[i] = i + 49;
}
void printBoard()
{
    printf("\n");
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 3; j++)
        {
            
            printf("|%c", BOARD[i+j]);
        }
        printf("|\n");
    }
}

int thereIsAWinner()
{
    for (int i = 0; i < 8; i++)
    {
        if (BOARD[winning_lines[i][0]] == BOARD[winning_lines[i][1]] && BOARD[winning_lines[i][1]] == BOARD[winning_lines[i][2]])
            return 1;
    }
    return 0;
}


void swap(Player *currentPlayer, Player *previousPlayer)
{
    Player tmp;
    tmp = *currentPlayer;
    *currentPlayer = *previousPlayer;
    *previousPlayer = tmp;
}





int getChoice(char *name)
{
    int choice;
    printf("%s :", name);
    scanf("%d", &choice);
    if (!validChoice(choice))
        return getChoice(name);
    return choice;
}

unsigned validChoice(int choice)
{
    if (choice < 1 || choice > 9 || BOARD[choice - 1] != 48 + choice)
        return 0;
    
    return 1;
}

void updateBoard(char symbol, int choice)
{
    BOARD[choice - 1] = symbol;
}

unsigned playAgain()
{
    char response;

    printf("PLAY AGAIN?\n");
    printf("Do you want to play again? (Y/n)");
    response = getch(); 
    
    return response == 'Y' || response == 'y';
}