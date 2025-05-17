// Tic-Tac-Woah
// Programming Assignment 5, Natalie Hoang
// Modified: 12/6/24

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
// global variables: 
int rows = 3;
int columns = 3;

//initializing functions
void DrawBoard(char board[3][3]);
void UpdateBoard(char board[3][3]);
void printBoardArray(char board[3][3]);
int GameWon(char board[3][3]);
int GameTie(char board[3][3]);
int PlayerQuitGame(char userinput[4]);
void StartGame();
void QuitGame();
void PlayGame(char board[3][3]);
int Player1Turn(char board[3][3]);
int Player2Turn(char board[3][3]);
int Menu();


// prints tic-tac-toe board (at program/game start-up)
void DrawBoard(char board[3][3])
{
    printf("Tic-Tac-Woah!\n");
    int rownum = 3;
    //draw rows
    for (int i = 0; i < rows; i++)
    {
        printf("%d ", rownum);
        rownum --;
        if (i < 2) {
            //draw row enteries
            for (int e = 0; e < columns; e++)
            {
                if (e < 2)
                    printf("___|");
                else
                    printf("___\n");
            }
        }
        else
        {
            printf("   |   |   \n");
            printf("   A   B   C\n");
        }
    }
}

//Displays grid board with player moves ('X' or 'O') and fills corresponding board array entry.
void UpdateBoard(char board[3][3])
{
    int rownum = 3;
    //draw rows
    for (int i = 0; i < rows; i++)
    {
        printf("%d ", rownum);
        rownum --;
        if (i < 2) {
            //draw row enteries
            for (int e = 0; e < columns; e++)
            {
                if (e < 2)
                    if (board[i][e] == 'X' || board [i][e] == 'O')
                        printf("_%c_|", board[i][e]);
                    else
                        printf("___|");
                else
                    if (board[i][e] == 'X' || board [i][e] == 'O')
                        printf("_%c_\n",board[i][e] );
                    else 
                        printf("___\n");
            }
        }
        //last row of board (no underscore lines)
        else
        {
            for (int e = 0; e < columns; e++)
            {
                if (e < 2)
                    if (board[i][e] == 'X' || board [i][e] == 'O')
                        printf(" %c |", board[i][e]);
                    else
                        printf("   |");
                else
                    if (board[i][e] == 'X' || board [i][e] == 'O')
                        printf(" %c \n",board[i][e] );
                    else 
                        printf("   \n");
            }
            
            printf("   A   B   C\n");
        }
    }
}
//prints board array (for debugging purposes)
void printBoardArray(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int e = 0; e < 3; e++)
        {
            printf("board[%d][%d] is %c ", i, e, board[i][e]);
        }
    }
}

//check if either player has won. Returns integer (1) if a player wins. Otherwise returns zero (0).
int GameWon(char board[3][3])
{
    
    for (int i = 0; i < 3 ; i++){
        //check rows
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && 'X' == board[i][2]) 
            || (board[i][0] == board[i][1] && board[i][1] == board[i][2] && 'O' == board[i][2]))
            return 1;
        //check columns
        else if ((board[0][i] == board[1][i] && board[1][i] == board[2][i] && 'X' == board [2][i]) 
            || (board[0][i] == board[1][i] && board[1][i] == board[2][i] && 'O' == board [2][i]))
            return 1;
    }
    //check diagonals
    if ((board[0][0] == board [1][1] && board[1][1] == board[2][2] && 'X' == board [2][2])
        || (board [2][0] == board [1][1] && board[1][1] == board[0][2] && 'X' == board[0][2])) {
        return 1; }
    if ((board[0][0] == board [1][1] && board[1][1] == board[2][2] && 'O' == board [2][2])
        || (board [2][0] == board [1][1] && board[1][1] == board[0][2] && 'O' == board[0][2])) {
        return 1; }

    return 0;
}
// check if game is tied by looping through board array and checking if all enteries are filled (with no 3-row enteries)
int GameTie(char board[3][3])
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == ' ')
                return 0;
        }
    }
    return 1;
}

// check if user wants to quit game. Return integer (1) if player wants to quit. Returns 0 otherwise. 
int PlayerQuitGame(char userinput[4])
{
    char quit[] = "quit";
    if (strcmp(quit,userinput) == 0)
        //user wants to quit
        return 1;
    else
        return 0;
}

//Starts game, draws starting grid and initalizes board array.
void StartGame()
{
    char board[rows][columns];
    //initalize board array
    for(int row = 0; row < 3; row++){
        for (int column = 0; column < 3; column++){
            board[row][column] = ' ';
        }
    }
    //draw grid
    DrawBoard(board);
    
    //play Game
    PlayGame(board);
    
}
//Quit Game, exit program 
void QuitGame(){
    printf("Quitting Program. Thanks for playing!\n");
    exit(0);
}
//simulates game and player moves. Stops when player quits, wins, or ties. 
void PlayGame(char board[3][3]) 
{
    bool GameActive = true;
    while (GameActive)
    {
        if(Player1Turn(board))
        {
            GameActive = false;
            break;
        }
        
        if (Player2Turn(board))
        {
            GameActive = false;
            break;
        }
    }
}
//Get player 1 input and move. Returns integer (1) if valid move is made or player wins or quits.
int Player1Turn(char board[3][3])
{
    int p1c = 0;
    int p1r = 0;
        
    char p1cInput ;
    int p1rInput = 0;
    char UserInput[4];
    bool p1Turn = true;
    
    while (p1Turn)
        {
            //Get players input
            //Player 1 (X)
            printf("Player 1's Move: ");
            scanf("%s", UserInput);
            
            //check if player wants to quit game
            if (PlayerQuitGame(UserInput))
            {
                //printf("Quitting game. Thanks for playing.");
                //GameActive = false;
                p1Turn = false;
                
                QuitGame();
                return 1;
                
            }
            // input is valid, add move to board
            if(strlen(UserInput) == 2 && UserInput[0] >= 'A' && UserInput[0] <= 'C' 
            && UserInput[1] >= '1' && UserInput[1] <= '3')
            {
                //convert input (A-C) to board index (0-2)
                p1cInput = UserInput[0] ;
                //convert input (ASCII values of 1-3 (49-51)) into board index (0-2)
                p1rInput = UserInput[1] - '0';
                
                //debugging purposes: print Input P1 values
                //printf("INp1col is %d, INp1row is %d\n", p1cInput,p1rInput);
                
                p1c = p1cInput - 'A';
                p1r = 3 - p1rInput;
                
                //debugging purposes: display player 1 move
                //printf("player1 row: %d, player1 col: %d \n", p1r, p1c);
                
                //check if entry is empty
                if (board[p1r][p1c] ==  ' ')
                {
                    board[p1r][p1c] = 'X';
                    //displays player's move to console
                    UpdateBoard(board);
                    
                    //check if player won
                    if (GameWon(board))
                    {
                        printf("Player 1 wins!\n");
                        //GameActive = false;
                        p1Turn = false;
                       
                        return 1;
                        //menu
                        //Menu();
                    }
                    //check if game is tied
                    if (GameTie(board))
                    {
                        printf("Game is tied!\n");
                        p1Turn = false;
                        
                        return 1;
                        //menu
                        //Menu();
                    }
                    //player 1 turn is over
                    return 0;
                    p1Turn = false;
                }
                //input is not a valid move. Keep reprompting user
                else
                {
                    printf("Invalid move! Please enter a valid move (A-C and 1-3).\n");
                    UpdateBoard(board);
                    continue;
                }
            }
            //check if player input is valid
            // "A" Input is Invalid (missing row value)
            else if( strlen(UserInput) < 2 && ((UserInput[0] >= 'A' && UserInput[0] <= 'C' ) || 
            (UserInput[0] >= '1' && UserInput[0] <= '3')))
            {
                printf("Invalid move, please specify both column and row.\n");
                UpdateBoard(board);
                continue;
            }
            //invalid column (not A-C) 
            else if (UserInput[0] < 'A' || UserInput[0] > 'C' ) 
              {
                printf("Invalid column! Please enter a valid move (A-C and 1-3).\n");
                UpdateBoard(board);
                continue;
              }
              //invalid row (not 1-3)
             else if (UserInput[1] < 1 || UserInput[1] > 3)
             {
                printf("Invalid row! Please enter a valid move (A-C and 1-3).\n");
                UpdateBoard(board);
                continue;
             }
            //return false; 
            
        //print BoardArray (debugging)
        //printBoardArray(board);
        }
    return 0;
}
//Get player two inputs and move. Returns integer (1) if valid move is made or player wins or quits.
int Player2Turn(char board[3][3])
{
    int p2c = 0;
    int p2r = 0;
        
    char p2cInput ;
    int p2rInput = 0;
    char UserInput[4];
    
    bool p2Turn = true;
    while (p2Turn)
    {
            //Player 2 Turn 
            printf("Player 2's Move: ");
            scanf("%s", UserInput);
            
            //check if player wants to quit game
            if (PlayerQuitGame(UserInput))
            {
                //printf("Quitting game. Thanks for playing.");
                //GameActive = false;
                
                p2Turn = false;
                QuitGame();
                return 1;
            }
            // input is valid, add move to board
            if(strlen(UserInput) == 2 && UserInput[0] >= 'A' && UserInput[0] <= 'C' 
            && UserInput[1] >= '1' && UserInput[1] <= '3')
            {
                //convert input (A-C) to board index (0-2)
                p2cInput = UserInput[0] ;
                //convert input (ASCII values of 1-3 (49-51)) into board index (0-2)
                p2rInput = UserInput[1] - '0';
                
                //debugging purposes: print P2 Input values
                //printf("p2cIN is %d, p2rIN is %d\n", p2cInput,p2rInput);
                
                p2c = p2cInput - 'A';
                p2r = 3 - p2rInput;
                
                //debugging purposes: display player 1 move
                //printf("player2 row: %d, player2 col: %d \n", p2r, p2c);
                
                //check if entry is empty
                if (board[p2r][p2c] ==  ' ')
                {
                    board[p2r][p2c] = 'O';
                    //displays player's move to console
                    UpdateBoard(board);
                    
                    //check if player won
                    if (GameWon(board))
                    {
                        printf("Player 2 wins!\n");
                        //GameActive = false;
                        
                        p2Turn = false;
                        return 1;
                        //go to quit or new game menu
                        //Menu();
                    }
                    //check if game is tied
                    if (GameTie(board))
                    {
                        printf("Game is tied!\n");
                        //GameActive = false;
                        
                        p2Turn = false;
                        return 1;
                        //go to quit or new game menu
                        //Menu();
                    }
                    //player 2 turn is over
                    return 0;
                    p2Turn = false;
                }
                //inputted move is invalid 
                else
                {
                    printf("Invalid move! Please enter a valid move (A-C and 1-3).\n");
                    UpdateBoard(board);
                    //continue;
                }
            }
            //check if player input is valid
            // "A" Input is Invalid (missing row value)
            else if( strlen(UserInput) < 2 && ((UserInput[0] >= 'A' && UserInput[0] <= 'C' ) || 
            (UserInput[0] >= '1' && UserInput[0] <= '3')))
            {
                printf("Invalid move, please specify both column and row.\n");
                UpdateBoard(board);
                continue;
            }
            //invalid column (not A-C) 
            else if (UserInput[0] < 'A' || UserInput[0] > 'C' ) 
              {
                printf("Invalid column! Please enter a valid move (A-C and 1-3).\n");
                UpdateBoard(board);
                continue;
                return true;
              }
              //invalid row (not 1-3)
             else if (UserInput[1] < 1 || UserInput[1] > 3)
             {
                printf("Invalid row! Please enter a valid move (A-C and 1-3).\n");
                UpdateBoard(board);
                continue;
             }
    }
    return 0;
    
}

//Menu functions
int Menu()
{
    char UserInput[4];
    char new[] = "new";
    char quit[] = "quit";
    int compare = 0;
    bool finish = true;
    //ask user(s) if they want to play again or quit 
    while(finish)
    {
        printf("Quit or New Game? (type 'quit' or 'new') \n");
        scanf( "%s", UserInput);
        compare = (strcmp(UserInput, new));
        //user wants a new game
        if (compare == 0)
        {
            StartGame();
            return 1;
        }
        
        compare = (strcmp(UserInput, quit));
        //user wants to quit program
        if (compare == 0)
        {
            //printf("Quitting game. Thanks for playing.");
            QuitGame();
            return 0;
        }
        //user input is invalid (does not say 'quit' or 'new')
        else
            continue;
    }
    return 0;
}
int main()
{
   bool ProgramActive = true;
   //start-up program, start game
   StartGame();
   while(ProgramActive)
   {
       //user gets prompted if they wan 
       int choose = Menu();
       //user wants to quit program
       if (choose == 0)
       {
           ProgramActive = false;
       }
       //user wants new game
       if (choose == 1)
       {
            continue;
       }
   }
   return 0;
   
}




