// header files
#include "yahtzee_lib.h"

// main program
int main() {
    // initialize program
    // initialize the random number generator
    initializePlayer();
    
    // declare variables to hold the dice
    int dice1, dice2, dice3, dice4, dice5;

    // declare the variable to store the user's choice
    char choice;
    
    // initialize the variable that stores the play
    int play = NO_PLAY;

    // print a title
    printf("\nWelcome to Simple Yahtzee!\n");
    printf("==========================\n\n");

    // begin game
    
    // TODO 1: create a loop that runs while the user wants to continue
    int continueLoop = 1; 
    while (continueLoop) {
        // TODO 2: roll the dice (one at a time)
        dice1 = rollDice();
        dice2 = rollDice();
        dice3 = rollDice();
        dice4 = rollDice();
        dice5 = rollDice();

        // TODO 3: print the dice
        printf("You roll: %d, %d, %d, %d, %d\n", dice1, dice2, dice3, dice4, dice5);

        // TODO 4: call the function decidePlay and store the result in the play variable
        play = decidePlay(dice1, dice2, dice3, dice4, dice5);

        // TODO 5: evaluate the play variable and print the appropriate message
        if (play == YAHTZEE) {
            printf("You rolled a Yahtzee!\n");
        } else if (play == FOUR_OF_A_KIND) {
            printf("You rolled a Four of a Kind!\n");
        } else if (play == THREE_OF_A_KIND) {
            printf("You rolled a Three of a Kind!\n");
        } else if (play == FULL_HOUSE) {
            printf("You rolled a Full House!\n");
        } else if (play == L_STRAIGHT) {
            printf("You rolled a Large Straight!\n");
        } else if (play == S_STRAIGHT) {
            printf("You rolled a Small Straight!\n");
        } else if (play == NO_PLAY) {
            printf("You rolled no particular play!\n");
        } else {
            printf("Invalid play.\n");
        }

        // prompt the user for continuing
            // function: printf
        printf("\nDo you want to continue (Y/N)? ");
            // Read the choice
        choice = getChoice();
        
        if (choice != 'Y' && choice != 'y') {
            continueLoop = 0;
        }
    }

    // End program
        // print a message
       // function: printf
    printf("\nThanks for playing Yahtzee!\n");
    // return success
    return 0;
}
