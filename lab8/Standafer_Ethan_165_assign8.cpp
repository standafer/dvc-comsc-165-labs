#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFileToStringVec(const string& fileName) {
    ifstream input;
    vector<string> builtVector;

    // Comment 1 (one)
    //  Because of how the compiler is set up on my machine,
    //  the C++ is built in a directory called "output", so my
    //  directory ends up looking like
    //      lab8/
    //          output/
    //              PostBuild (executable)
    //          PreBuild.cpp
    //          Teams.txt
    //  So, because of this, to get the Teams.txt, we need to 
    //  add a ../ to bring the directory up from the executable's
    //  position to get the Teams.txt file
    ifstream inputObject;
    vector<string> built;
    
    // Had to add ../ here because the output directory is separate from the directory that the
    // main C++ file is in.
    inputObject.open("../" + fileName);

    if (!inputObject.is_open()) {
        cout << "Failed to open file!" << endl;
    }

    string line;
    
    while (getline(inputObject, line)) {
        built.push_back(line);
    }
    
    inputObject.close();
    
    return built;
}

// Comment 2 (Two)
//  Ceiling integer division is necessary to rounding up to the correct
//  amount of lines correctly. i.e. there are three strings, and you
//  have a per line need of "2", doing regular integer division 3 / 2
//  would yield "1" instead of the required "2". Using ceiling integer
//  division it correctly returns "2" lines needed.
int ceilIntDivide(int a, int b) {
    // Attribution for inspiration for implementation:
    // https://stackoverflow.com/a/62032709
    return (a + (b - 1)) / b;
}

// This specific implementation was not in the program requirements, I
// did this for the challenge.
void displayStringVec(const vector<string>& strings) {
    // Comment 3 (three)
    //  This function takes in a string vector and outputs the
    //  values in a formatted manner i.e. ["Hello", "world", "world2"]
    //  would output:
    //      Hello       world2
    //      world
    //  NOTE: This was not a program requirement, I am doing this for
    //  the challenge.

    int perLine = 2;
    
    int numStrings = strings.size();
    int linesNeeded = ceilIntDivide(numStrings, perLine);
    // Comment 4 (four)
    //  This is a two-dimensional vector storing data in this format:
    //      vec[
    //          vec["line1", "line3"]
    //          vec["line2"]
    //      ]
    vector<vector<string>> lines(linesNeeded, vector<string>(perLine));
    
    // Comment 5 (five)
    //  To demonstrate the index mapping math here, I made a Desmos
    //  https://www.desmos.com/calculator/dbkhsszzji
    for (int i = 0; i < numStrings; i++) {
        int col = i % perLine;                // Column index
        int row = i / perLine;                // Row index
        int mappedIndex = col * linesNeeded + row; // Column-major mapping
        
        if (mappedIndex < numStrings) {
            lines[row][col] = strings[mappedIndex];
        }
    }

    // Comment 6 (six)
    //  OK, so we have assembled our array and have all the relevant variables,
    //  all that's left to do is print it all.
    for (int i = 0; i < lines.size(); i++) {
        vector<string>& line = lines[i];

        for (int j = 0; j < line.size(); j++) {
            cout << line[j];
            
            if (!line[j].empty()) {
                for (int t = 0; t < 3; t++) {
                    cout << "\t";
                }

            }
        }
        cout << "\n";
    }
}

string promptForTeamName() {
    cout << endl << "Enter the name of one of the teams:";
    
    // Comment 7 (seven)
    //  Prompt the user for the name of the team
    string teamName;
    getline(cin, teamName);


    return teamName;
}

int countWins(const string& name, const vector<string>& winners) {
    int count = 0;

    cout << winners.size() << endl;
    
    for (int i = 0; i < winners.size(); i++) {
        const string& winnerName = winners[i];

        if (winnerName == name) {
            // Comment 8 (eight)
            //  We have a match to the name, increment the count amount
            count ++;
        }
    }

    return count;
}

void outputWins(const string& name, const int wins) {
    cout << "The " << name << " have won the World Series " << wins << " time" << ((wins != 1) ? "s" : "") << " between 1903 and 2012.";
}

int main() {
    // Comment 9 (nine)
    //  Read both the "Teams.txt" and "Winners.txt" file and convert
    //  them into a vector
    const vector<string> teams = readFileToStringVec("Teams.txt");
    const vector<string> winners = readFileToStringVec("Winners.txt");

    // Comment 10 (ten)
    //  Output all the team names
    displayStringVec(teams);

    const string teamName = promptForTeamName();

    cout << "DEBUG: Looking for team: '" << teamName << "'" << endl;
    cout << "DEBUG: First 5 winners:" << endl;

    outputWins(teamName, countWins(teamName, winners));
    
    return 0;
}