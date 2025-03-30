#include <iostream>
#include <cassert>
#include <cctype>
#include <vector>
#include <string>

using namespace std;

const int QUESTIONS = 20;
// List of all answers by their answer
const string ANSWER_KEY[QUESTIONS] = {
    "A",    // (1)
    "D",    // (2)
    "B",    // (3)
    "B",    // (4)
    "C",    // (5)
    "B",    // (6)
    "A",    // (7)
    "B",    // (8)
    "C",    // (9)
    "D",    // (10)
    "A",    // (11)
    "C",    // (12)
    "D",    // (13)
    "B",    // (14)
    "D",    // (15)
    "C",    // (16)
    "C",    // (17)
    "A",    // (18)
    "D",    // (19)
    "B"     // (20)
};

bool answerIsValid(string answer) {
    // List of all valid responses (upper and lower)
    string okResponses[] = {"A", "a", "B", "b", "C", "c", "D", "d"};

    // Iterate over each
    for (const string& ok : okResponses) {
        if (answer == ok) {
            // If one matches, then it's an ok answer
            return true;
        }
    }
    
    // Otherwise, it's not valid and should be rejected
    return false;
}

// Returns if the answer was correct or not, based on the data in ANSWER_KEY
// Should be valid before passing, will raise an exception
bool questionAnswerIsCorrect(int questionIdx, string answer) {
    assert(answerIsValid(answer));
    char upperAnswer = toupper(answer[0]);
    return ANSWER_KEY[questionIdx][0] == upperAnswer;
}

string promptUserForAnswer(int questionIdx) {
    cout << "Question " << to_string(questionIdx + 1) << ": ";

    string response;
    // Continue prompting until a valid response is received
    while (true) {
        cin >> response;
        cin.ignore(1000, 10);
        if (answerIsValid(response)) {
            break; // Answer is correct, no need to proceed with invalid message.
        }
        cout << "Use only an A, B, C or D!" << endl << "Please try again." << endl;
    }

    return response;
}

int main() {
    vector<int> incorrect;
    
    // Present all questions
    for (int i = 0; i < QUESTIONS; i++) {
        string answer = promptUserForAnswer(i);

        if (!questionAnswerIsCorrect(i, answer)) {
            // Answer is incorrect
            incorrect.push_back(i + 1);
        }
    }

    // Determine if student passed or failed (passing requires at least 15 correct)
    if (incorrect.size() > 5) {
        // failed
        cout << endl << endl << "The student failed the exam." << endl << endl;
    }

    // Display the list of incorrectly answered questions
    cout << "Questions that were answered incorrectly:" << endl;
    // Iterate over all questions
    for (int questionNum : incorrect) {
        // Output the number. No need for a newline because it'll just take up more space.
        cout << questionNum << " ";
    }
    cout << endl;

    return 0;
}