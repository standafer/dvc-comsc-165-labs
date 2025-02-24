#include <iostream>
#include <tuple>

using namespace std;

const int RUNNERS_LEN = 3;

struct Runner {
    string name;
    int finishingTime;
};

const string OK = "<<ok>>";

// Checks if a runner's finishing time is valid.
//      If yes, function returns a "OK" constant
//      If not, function returns a descriptive user-facing error message
// note: Using a tuple like <bool, string (error)> might be a nicer approach to this
string runnerFinishingTimeIsInvalid(int finishingTime) {
    // In this case, the value entered was either less than or
    // equal to zero, which is not possible in a race.
    if (finishingTime <= 0) return "Enter positive values for each runner's time only.";

    return OK;
}

// Prompts the user for a runner with validation built-in
// Returns the Runner object
Runner promptForRunner(int number) {
    Runner runner = {};

    // Prompt for runner name (no validation needed here)
    cout << "Name of Runner " << number << ": ";
    getline(cin, runner.name);

    bool runnerTimeIsValid = false;
    while (!runnerTimeIsValid) {
        cout << "Runner " << number << "'s finishing time: ";
        
        // Prompt for finishing time
        cin >> runner.finishingTime;
        cin.ignore(1000, 10);

        // Validate the runner finishing time using the method
        string result = runnerFinishingTimeIsInvalid(runner.finishingTime);
        // Runner time is only valid if the string is OK (see runnerFinishingTimeIsInvalid)
        runnerTimeIsValid = result == OK;

        // The runners time is valid, so early exit from the loop
        if (runnerTimeIsValid) break;
        // Otherwise, if it isn't valid, display the error message

        cout << endl << result << endl  << endl;
    }

    return runner;
}

bool compareByFinishingTime(const Runner& a, const Runner& b) {
    return a.finishingTime < b.finishingTime;
}

string getOrdinal(int num) {
    // Note: See https://stackoverflow.com/a/13627586/13157115 for
    // implementation details. Ported from JavaScript to C++

    int j = num % 10;
    int k = num % 100;

    if (j == 1 && k != 11) {
        return "st";
    } else if (j == 2 && k != 12) {
        return "nd";
    } else if (j == 3 && k != 13) {
        return "rd";
    }

    return "th";
}

string numWithOrdinal(int num) {
    return std::to_string(num) + getOrdinal(num);
}

int main() {
    cout << "Enter the names of three runners and their finishing times."
        << endl << "I will tell you who came in first, second and third." << endl << endl;
    
    // Initialize list of runners
    Runner runners[RUNNERS_LEN] = {};

    // Prompt RUNNERS_LEN times 
    for (int i = 0; i < RUNNERS_LEN; i++) {
        runners[i] = promptForRunner(i + 1);
        
        Runner currentRunner = runners[i];

        // Add an extra line
        cout << endl;
    }

    // For adherence to the process:
    //  note:   This check is largely unncessary as validation is performed within the
    //          promptForRunner method, and there should be no way an unvalidated Runner
    //          object makes it past the loop above
    bool runnersFinishingTimesOK = true;
    for (int i = 0; i < RUNNERS_LEN; i++) {
        string result = runnerFinishingTimeIsInvalid(runners[i].finishingTime);

        if (result != OK) {
            // Result is not OK, output the error message, set the flag
            // and then escape the loop
            //  note:   This does not handle a case where there are potentially >1 distinct
            //          errors in the runners, in which case it would only output the first
            //          error, then escape

            runnersFinishingTimesOK = false;
            cout << endl << result << endl;
            break;
        }
    }
    if (!runnersFinishingTimesOK) {
        return 0;
    }

    // Sort the array by finishing time
    sort(runners, runners + RUNNERS_LEN, compareByFinishingTime);

    for (int i = 0; i < RUNNERS_LEN; ++i) {
        Runner currentRunner = runners[i];
        int finishingTime = currentRunner.finishingTime;
        
        string context = "(finished in: " + to_string(finishingTime) + "s";
        if (i < RUNNERS_LEN - 1) {
            // Not last place, also say how much they were ahead by
            Runner beforeRunner = runners[i + 1];
            // Subtract the previous runners time by ours to get the speed difference
            context += ", ahead by " + to_string(beforeRunner.finishingTime - currentRunner.finishingTime) + "s";
        }
        context += ")";

        cout << currentRunner.name << " came in " << numWithOrdinal(i + 1) << " place. " << context << endl;
    }

    return 0;
}