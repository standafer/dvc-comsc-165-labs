#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;
const int QUIT = 4;

// Returns exclusively if either the user or computer have selected the
// passed type exactly once (XOR)
bool exclEitherIsOfType(int type, int user, int computer)
{
    // note:    This function is just in the spirit of keeping things DRY
    return !(user == computer) && (user == type || computer == type);
}


int getUserChoice() {
    int choice;
    
    cout << "Game Menu" << endl << "---------" << endl;
    cout << "1) Rock" << endl;
    cout << "2) Paper" << endl;
    cout << "3) Scissors" << endl;
    cout << "4) Quit" << endl << endl;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid selection. Enter 1, 2, 3, or 4: ";
    }

    return choice;
}

int getComputerChoice()
{
    // Rock, in this case, is the lowest possible decision, and scissors is
    // the highest possible decision in the integer number line

    return rand() % ((SCISSORS - ROCK) + 1) + ROCK;
};

// Outputs
//      - "tie" if both players had the same decision
//      - If it's not a tie it relies on these standard rules for RPC:
//          1) rock beats scissors
//          2) paper beats rock
//          3) scissors beats paper
//      - Depending on which player satisifies the winning condition, it
//      will output "User wins!" or "Computer wins!"
// note:    Range of acceptable decisions is [1, 3] in integers
//          There is no assertion of this requirement.
void determineOutcome(int user, int computer)
{
    // This check is critical for the rest of the code. We need to check to make
    // sure that the two values are not equal, so that the rest of the checks are
    // exclusive
    if (user == computer) {
        cout << "It's a tie! No winner." << endl;
        return;
    }

    // Having a XOR (instead of just an OR) here could be considered "overkill" because of
    // the previous tie checks, but considering this is critical "business" logic, I think
    // the additional robustness is welcome.
    int rock = exclEitherIsOfType(ROCK, user, computer);
    int paper = exclEitherIsOfType(PAPER, user, computer);
    int scissors = exclEitherIsOfType(SCISSORS, user, computer);

    // For reference:
    //      - rock beats scissors
    //      - paper beats rock
    //      - scissors beats paper

    int winner;
    string winningMechanism = "";

    if (rock && scissors) {
        // note:    Winner is the player who played rock
        //          We'll say that the "user" is going to be the checked play here
        //          Really, though, it could be either, or even random

        // note:    Setting the winner to the decision of either the user or the
        //          computer works here because we know that the values are unique,
        //          that is that the computer CANNOT play the same thing as the user
        //          as there is a prior check.
        //          That being said, it might be easier to convey this behavior as a
        //          constant (i.e. const string USER = "<<user>>")
        winner = (user == rock) ? user : computer;
        winningMechanism = "rock smashes the scissors";

    } else if (paper && rock) {
        winner = (user == paper) ? user : computer;
        winningMechanism = "paper wraps the rock";

    } else if (scissors && paper) {
        winner = (user == scissors) ? user : computer;
        winningMechanism = "scissors cut the paper";

    } else {
        // Should never reach this. Safe to have a base-case, though.
        winner = user;
        winningMechanism = "<<impossible case>>";

    }
    
    // Now that a winner has been determined, we can output it. To keep it simple
    // I have it as a ternary operator.
    cout << ((winner == user) ? "YOU win" : "Computer wins")
        << " because "
        << ((winner == user) ? "your" : "their")
        << " "
        << winningMechanism << "!" << endl;
};

void displayChoice(int choice)
{
    // Simple switch statement here. Could also use if/else chains but this makes it
    // easier to maintain. Only potential for error here is with the necessary "break"s
    switch (choice) {
        case(ROCK):
            cout << "rock";
            break;
        case(PAPER):
            cout << "paper";
            break;
        case(SCISSORS):
            cout << "scissors";
            break;
        default:
            cout << "invalid choice";
            break;
    }

    cout << endl;
};

int main()
{
    int userChoice;
    int computerChoice;
    
    // Seed the random number generator
    srand(time(0));

    computerChoice = getComputerChoice();
    userChoice = getUserChoice();
    
    while (userChoice != QUIT)
    {
        cout << "\nYou selected: ";
        displayChoice(userChoice);

        cout << "The computer selected: ";
        displayChoice(computerChoice);
        
        determineOutcome(userChoice, computerChoice);
        cout << endl;

        computerChoice = getComputerChoice();

        userChoice = getUserChoice();
    }
    
    // system("PAUSE");
    return 0;
}