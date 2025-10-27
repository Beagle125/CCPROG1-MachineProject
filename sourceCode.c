/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts
in studying and applying the concepts learned. I have constructed the functions
and their respective algorithms and corresponding code by myself. The program
was run, tested, and debugged by my own efforts. I further certify that I have
not copied in part or whole or otherwise plagiarized the work of other students
and/or persons.
Cedric Daniel P. Chan, DLSU ID# 12504106
***************************************************************************/
/*
Description: A simple game where players must answer randomly-generated sequence questions in order to progress a win!
Programmed by: Cedric Daniel P. Chan S19B
Last modified: October 11, 2025
Version: 1.1
Acknowledgements: 
    1. MP Project Specifications: https://dlsu.instructure.com/courses/219038/assignments/2274482
    2. Generating random numbers: https://www.geeksforgeeks.org/c/generating-random-number-range-c/
*/

//Preprocessor Directives
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Prototypes of helper functions
int gameLoop(int nNumberOfPlayers, int nGameLevel);
int checkPlayer(int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4);
int rollDie(void);
bool answerSequence(int nGameLevel);

/* Description: This is the main function of the program. 
Precondition: N/A
@param void
@return integer 0 for the successful execution of the program.
*/
int main (void){
    // Initialize important variables
    int nNumberOfPlayers, nGameLevel, nPlayerWinner;

    //Print a welcoming message
    printf("Welcome to a \"Walk in the Sequence Park\"\n");
    // Prompt and input nNumberOfPLayers
    do{
        printf("\nHow many players will play? ");
        scanf("%d", &nNumberOfPlayers);
    }while (nNumberOfPlayers > 4 || nNumberOfPlayers < 1);
    // Prompt and input nGameLevel
    do{
        printf("\nSelect a difficulty level: ");
        scanf("%d", &nGameLevel);
    }while (nGameLevel > 3 || nGameLevel < 1);
    // Call int gameLoop() function
    nPlayerWinner = gameLoop(nNumberOfPlayers, nGameLevel); // 1 here is to just test printf function below
    // Print the player winner
    printf ("\nCongratulations Player %d!\n", nPlayerWinner);
    printf("\nYou are the winner!\n");
    return 0;

}

/* Description: This is the game loop function. It serves to ensure that the game loops until the proper conditions are met to end the game. 
Precondition: The number of players and game level are inputted by the user.
@param int nNumberOfPlayer, int nGameLevel
@return int nPlayerWinner.
*/
int gameLoop(int nNumberOfPlayers, int nGameLevel){
    // Initialize important variables
    int nPlayer1, nPlayer2, nPlayer3, nPlayer4;
    int nCurrentPlayerTurn = 1;
    //int nNumberOfEliminated = 0; (these are to be used in future versions)
    int nPlayerWinner;
    int nDieValue;
    //bool bPlayerWon = false; (these are to be used in future versions)
    // TEST nPlaceHolder to be removed in the final version
    int nPlaceHolder = 0;

    // Use switch case to set individual player variables
    switch (nNumberOfPlayers){
        case 1:
            nPlayer1 = 1;
            nPlayer2 = 0;
            nPlayer3 = 0;
            nPlayer4 = 0;
            break;

        case 2:
            nPlayer1 = 1;
            nPlayer2 = 1;
            nPlayer3 = 0;
            nPlayer4 = 0;
            break;

        case 3:
            nPlayer1 = 1;
            nPlayer2 = 1;
            nPlayer3 = 1;
            nPlayer4 = 0;
            break;
        
        case 4:
            nPlayer1 = 1;
            nPlayer2 = 1;
            nPlayer3 = 1;
            nPlayer4 = 1;
            break;
    }

    // TEST The following print statement below is to test the rollDie function
    printf("Before the game: player1: %d, player2: %d, player3: %d, player4: %d\n", nPlayer1, nPlayer2, nPlayer3, nPlayer4);

    // The main while loop that continues until a winner is selected or all players are eliminated
    while (nPlaceHolder < 9){ // TEST This is just to see if it will loop  nine times it will soon be changed to while(bPlayerWon == false && nNumberOfEliminated != nNumberOfPlayers)
        // An if statement for every player's turn
        if (checkPlayer(nCurrentPlayerTurn, nPlayer1, nPlayer2, nPlayer3, nPlayer4) > 0){
            // Roll the die and move the current player 
            nDieValue = rollDie();
            switch (nCurrentPlayerTurn){
                case 1:
                    nPlayer1 += nDieValue;
                    break;
                
                case 2:
                    nPlayer2 += nDieValue;
                    break;

                case 3:
                    nPlayer3 += nDieValue;
                    break;

                case 4:
                    nPlayer4 += nDieValue;
                    break;
            }

            // Answering the question

            // Move the player's position or current space if wrong

            // TEST This piece of code is just see the loop in action currently
            printf("Player %d turn done!\n", nCurrentPlayerTurn);
        }

        // Update the current player's turn
        if (nCurrentPlayerTurn == nNumberOfPlayers){
                nCurrentPlayerTurn = 1;
        }
        else if (nDieValue == 6){
            nCurrentPlayerTurn += 0;
        }
        else{
            nCurrentPlayerTurn++;
        } 

        // TEST Update the temporary placeholder
        nPlaceHolder++;
        

    }

    // TEST The following print statement below are to test the rollDie function
    printf("Before the game: player1: %d, player2: %d, player3: %d, player4: %d\n", nPlayer1, nPlayer2, nPlayer3, nPlayer4);

    nPlayerWinner = 1;
    return nPlayerWinner; // TEST 1 here is to just test the print function on main
}

/* Description: This is the checkPlayer function to pair the current player to the status of players. This is to ensure we skip eliminated or non-existent players. 
Precondition: The current player and all possible four players.
@param int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4
@return either nReturnPLayer which is set to either nPlayer1, nPlayer2, nPlayer3, or nPlayer4.
*/
int checkPlayer(int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4){
    int nReturnPlayer;
    switch (nCurrentPlayerTurn){
        case 1:
            nReturnPlayer = nPlayer1;
            break;
        case 2:
            nReturnPlayer = nPlayer2;
            break;
        case 3:
            nReturnPlayer = nPlayer3;
            break;
        case 4:
            nReturnPlayer = nPlayer4;
            break;
    }
    return nReturnPlayer;
}

/* Description: A simple function when called return a random number between 1 and 6
Precondition: It is currently a player's turn
@param void
@return a random integer between 1 and 6
*/
int rollDie(void){
    // Initialize nMin and nMax
    int nMin = 1;
    int nMax = 6;

    // Generate a random number
    srand(time(NULL));

    return (nMin + rand() % (nMax - nMin + 1));
}



/*
bool answerSequence(int nGameLevel){
    // Declaration of variables

    // Game difficulty 1

    // Game difficulty 2

    // Game difficulty 3
}
*/