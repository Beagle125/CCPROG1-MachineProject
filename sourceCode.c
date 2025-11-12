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
Last modified: November 7, 2025
Version: 2.1
Acknowledgements: 
    1. MP Project Specifications: https://dlsu.instructure.com/courses/219038/assignments/2274482
    2. Generating random numbers: https://www.geeksforgeeks.org/c/generating-random-number-range-c/
*/

//Preprocessor Directives
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Prototypes of helper functions
int gameLoop(int nNumberOfPlayers, int nGameLevel);
int checkPlayer(int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4);
int rollDie(void);
bool answerSequence(int nGameLevel, int nCurrentPlayerTurn);
void updateNumericalAnswer(int nSequence, int *nAnswer);
void updateAlphaAnswer(int nSequence, int nGameDifficulty, char *cAnswer, char *cAnswer2);

/* Description: This is the main function of the program. 
Precondition: N/A
@param void
@return integer 0 for the successful execution of the program.
*/
int 
main (void){
    // Initialize important variables
    int nNumberOfPlayers, nGameLevel, nPlayerWinner, nCheckPlayers = -1, nCheckLevel = -1;

    //Print a welcoming message
    printf("Welcome to a \"Walk in the Sequence Park\"\n");

    // Prompt and input nNumberOfPLayers
    do{     
        printf("\nHow many players will play? ");
        nCheckPlayers =  scanf("%d", &nNumberOfPlayers);
        while (getchar() != '\n');
        system("cls");
    }while (nNumberOfPlayers > 4 || nNumberOfPlayers < 1 || nCheckPlayers != 1);

    // Prompt and input nGameLevel
    do{
        printf("\nSelect a difficulty level: ");
        nCheckLevel = scanf("%d", &nGameLevel);
        while(getchar() != '\n');
        system("cls");
    }while (nGameLevel > 3 || nGameLevel < 1 || nCheckLevel != 1);

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
Bugs: None
*/
int 
gameLoop(int nNumberOfPlayers, int nGameLevel){
    // Initialize important variables
    int nPlayer1, nPlayer2, nPlayer3, nPlayer4;
    int nCurrentPlayerTurn = 1;
    //int nNumberOfEliminated = 0; (these are to be used in future versions)
    int nPlayerWinner;
    int nDieValue;
    //bool bPlayerWon = false; (these are to be used in future versions)
    bool bPlayerCorrect = false;
    // THIS IS TO BE ADDED char cRoll;
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
            // Greet the current player
            printf("-----------------------PLAYER %d \'s TURN-----------------------", nCurrentPlayerTurn);
            // Roll the die and move the current player 
           // THIS IS TO BE ADDED printf("Player %d, press ENTER to roll the dice...", nCurrentPlayerTurn);
            nDieValue = rollDie();
            printf("\nPlayer %d rolled a %d\n", nCurrentPlayerTurn, nDieValue);
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
            bPlayerCorrect =  answerSequence(nGameLevel, nCurrentPlayerTurn);

            // Move the player's position or current space if wrong (Add the going back feature soon)
            if (bPlayerCorrect == false){
                printf("Player %d got it INCORRECT!\n", nCurrentPlayerTurn);
            }
            else{
                printf("Player %d got it CORRECT!\n", nCurrentPlayerTurn);
            }
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

        // Press ENTER to proceed
        printf ("Press ENTER to continue...");
        getchar();
        while (getchar() != '\n');
        system("cls");
        // TEST Update the temporary placeholder
        nPlaceHolder++;
        

    }

    // TEST The following print statement below are to test the rollDie function
    printf("\nAfter the game: player1: %d, player2: %d, player3: %d, player4: %d\n", nPlayer1, nPlayer2, nPlayer3, nPlayer4);

    nPlayerWinner = 1;
    return nPlayerWinner; // TEST 1 here is to just test the print function on main
}

/* Description: This is the checkPlayer function to pair the current player to the status of players. This is to ensure we skip eliminated or non-existent players. 
Precondition: The current player and all possible four players.
@param int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4
@return either nReturnPLayer which is set to either nPlayer1, nPlayer2, nPlayer3, or nPlayer4.
Bugs: None
*/
int 
checkPlayer(int nCurrentPlayerTurn, int nPlayer1, int nPlayer2, int nPlayer3, int nPlayer4){
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
Bugs: None
*/


int 
rollDie(void){
    // Initialize nMin and nMax
    int nMin = 1;
    int nMax = 6;

    // Generate a random number
    srand(time(NULL));

    return (nMin + rand() % (nMax - nMin + 1));
}



/* Description: This variable handles the sequence of the player answering a question
Precondition: The player has already rolled the dice and is currently answering the question
@param nGameLevel nCurrentPlayerTurn
@return a boolean value that indicated if the player answered the question correctly or not
Bugs: 
1. Currently there is a bug where if the player gives a wrong input stuff goes wrong.
2. There is a bug that somehow causes problem in the alpha sequence. Generating A A A A A or so, but the sequence is not 0?
    Causes: Its stems from when nSequence is negative. It also occurs where the char of nAnswer2 is not a letter anymore.
3. There is a bug at difficulty 3 regarding how cAnswer and nAnswer relate to each other. 
*/
bool 
answerSequence(int nGameLevel, int nCurrentPlayerTurn){
    // Declaration of variables
    bool bCorrect = false;
    int nGenerate = 0;
    int nSequence = 0;
    int nAnswer = 0;
    int nAnswer2 = 0; // difficulty 2
    int nPlayerInput = 0;
    int nPlayerInput2 = 0; // difficulty 2
    char cAnswer = 'a'; 
    char cAnswer2 = 'a'; // diffculty 2
    char cPlayerInput = 'a';
    char cPlayerInput2 = 'a'; // difficulty 2
    
    // Call out the current player
    printf("\nPlayer %d...your question\n", nCurrentPlayerTurn);
    // Generate a random number for letters or numbers
    srand(time(NULL));
    nGenerate = (0 + rand() % (2));
    // Generate a random number for the sequence
    nSequence = (-10 + rand() % (21));
    


    // Game difficulty 1
    if (nGameLevel == 1){
        if (nGenerate == 0){
            nAnswer = (-50 + rand() % (101));
            printf("What is the next number in the sequence: ");
            updateNumericalAnswer(nSequence, &nAnswer);
            printf("\n");
            printf("\nYour answer: ");
            scanf("%d", &nPlayerInput);
            printf("\n");
            if (nPlayerInput == nAnswer){
                bCorrect = true;
            }
            else{
                bCorrect = false;
            }
        }
        else{
            cAnswer = 'A' + (rand() % 26);
            printf("What is the next letter in the sequence: ");
            updateAlphaAnswer(nSequence, nGameLevel, &cAnswer, &cAnswer2);
            printf("\n");
            printf("\nYour answer: ");
            scanf(" %c", &cPlayerInput);
            printf("\n");

            // make player input uppercase all the time
            cPlayerInput = toupper(cPlayerInput);
            if (cPlayerInput == cAnswer){
                bCorrect = true;
            }
            else{
                bCorrect = false;
            }
        }
    }

    // Game difficulty 2
    else if (nGameLevel == 2){
        if (nGenerate == 0){
            nAnswer = (-50 + rand() % (101));
            printf("What are the next two numbers in the sequence: ");
            updateNumericalAnswer(nSequence, &nAnswer);
            nAnswer2 = nAnswer + nSequence;
            printf("\n");
            printf("\nYour two answers: ");
            scanf("%d %d", &nPlayerInput, &nPlayerInput2);
            printf("\n");
            if (nPlayerInput == nAnswer && nPlayerInput2 == nAnswer2){
                bCorrect = true;
            }
            else{
                bCorrect = false;
            }
        }
        else{
            cAnswer = 'A' + (rand() % 26);
            printf("What are the next two letters in the sequence: ");
            updateAlphaAnswer(nSequence, nGameLevel, &cAnswer, &cAnswer2);
            printf("\n");
            printf("\nYour two answers: ");
            scanf(" %c %c", &cPlayerInput, &cPlayerInput2);
            printf("\n");

            // make player input uppercase all the time
            cPlayerInput = toupper(cPlayerInput);
            cPlayerInput2 = toupper(cPlayerInput2);
            if (cPlayerInput == cAnswer && cPlayerInput2 == cAnswer2){
                bCorrect = true;
            }
            else{
                bCorrect = false;
            }
        }
    }

    // Game difficulty 3
    else{
        cAnswer = 'A' + (rand() % 26);
        printf("What are the next two numbers and letters in the sequence: ");
        updateAlphaAnswer(nSequence, nGameLevel, &cAnswer, &cAnswer2);
        printf("\n");
        printf("\nYour two answers: ");
        scanf(" %c %d", &cPlayerInput, &nPlayerInput);
        printf("\n");

        // make player input uppercase all the time
        cPlayerInput = toupper(cPlayerInput);
        if (cPlayerInput == cAnswer && nPlayerInput == (int)(cAnswer2 - 64)){
            bCorrect = true;
        }
        else{
            bCorrect = false;
        }
    }
    // return value
    return bCorrect;
}

/* Description: This is function simply updates the number value in answerSequence()
Precondition: It is currently a player's turn and a randomly sequence of numbers is being generated
@param int nSequence int *nAnswer
@return void
*/
void 
updateNumericalAnswer(int nSequence, int *nAnswer){
    for (int i = 0; i < 5; i++){
        printf("%d ", *nAnswer);
        *nAnswer += nSequence;
    }
}


/* Description: This is function simply updates the number value in answerSequence()
Precondition: It is currently a player's turn and a randomly sequence of letters is being generated
@param int nSequence int nGameDifficulty, char *cAnswer char *cAnswer2
@return void
*/
void 
updateAlphaAnswer(int nSequence, int nGameDifficulty, char *cAnswer, char *cAnswer2){
    if (nGameDifficulty == 1){
        for (int i = 0; i < 5; i++){
            printf(" %c", *cAnswer);
             if (nSequence >= 0){
                for (int j = 0; j < nSequence; j++){
                    if (*cAnswer == 90){
                        *cAnswer = 'A';
                    }
                    else{
                        *cAnswer += 1;
                    }
                }
             }
             else{
                for (int j = 0; j > nSequence; j--){
                    if (*cAnswer == 65){
                        *cAnswer = 'Z';
                    }
                    else{
                        *cAnswer -= 1;
                    }
                }
             }
        }

    }
    else if(nGameDifficulty == 2){
        for (int i = 0; i < 5; i++){
            printf(" %c", *cAnswer);
            if (nSequence >= 0){
                for (int j = 0; j < nSequence; j++){
                    if (*cAnswer == 90){
                        *cAnswer = 'A';
                    }
                    else{
                        *cAnswer += 1;
                    }
                }
            }
            else{
                for (int j = 0; j > nSequence; j--){
                    if (*cAnswer == 65){
                        *cAnswer = 'Z';
                    }
                    else{
                        *cAnswer -= 1;
                    }
                }
            }
        }
        // Set cAnswer2 value
        *cAnswer2 = *cAnswer;
        if (nSequence >= 0){
            for (int j = 0; j < nSequence; j++){
                if (*cAnswer2 == 90){
                    *cAnswer2 = 'A';
                }
                else{
                    *cAnswer2 += 1;
                }
            }      
        }
        else{
            for (int j = 0; j > nSequence; j--){
                if (*cAnswer2 == 65){
                    *cAnswer2 = 'Z';
                }
                else{
                    *cAnswer2 -= 1;
                }
            }
        }
    }
    else{
        if (nSequence >= 0){
            for (int i = 0; i < 5; i++){

                if (i % 2 != 0){
                    printf(" %c", *cAnswer);
                }
                else{
                    printf(" %d", (int)*cAnswer - 64);
                }

                for (int j = 0; j < nSequence; j++){
                    if (*cAnswer == 90){
                        *cAnswer = 'A';
                    }
                    else{
                        *cAnswer += 1;
                    }
                }

            }

            // Update cAnswer2
            *cAnswer2 = *cAnswer;
            for (int i = 0; i < nSequence; i++){
                if (*cAnswer2 == 90){
                    *cAnswer2 = 'A';
                }
                else{
                    *cAnswer2 += 1;
                }
            }
        }
        else{
            for (int i = 0; i < 5; i++){

                if (i % 2 != 0){
                    printf(" %c", *cAnswer);
                }
                else{
                    printf(" %d", (int)*cAnswer - 64);
                }

                for (int j = 0; j > nSequence; j--){
                    if (*cAnswer == 65){
                        *cAnswer = 'Z';
                    }
                    else{
                        *cAnswer -= 1;
                    }
                }

            }
            
            // Update cAnswer2
            *cAnswer2 = *cAnswer;
            for (int i = 0; i > nSequence; i--){
                if (*cAnswer2 == 65){
                    *cAnswer2 = 'Z';
                }
                else{
                    *cAnswer2 -= 1;
                }
            }
        }
    }
}