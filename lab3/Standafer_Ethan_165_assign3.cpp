#include <iostream>
#include <iomanip>
//  note:   #include <functional> is from a tutorial 
#include <functional>
using namespace std;

// This function takes in a higher-order comparator function and 5 subsequent scores. Keeping in the spirit of the assignment
// (assuming that arrays and sorting is not allowed) It performs a comparator check on each score, and keeps the most matched
// score. This is to keep the derivative findLowest and findHighest functions not crossing over repeated logic (DRY)
int compareAll(function<bool(double, double)> comparator, double score1, double score2, double score3, double score4, double score5) {
    int targetIdx = 1; // Assume first score is the target value initially
    double targetScore = score1;

    if (comparator(score2, targetScore)) {
        targetIdx = 2;
        targetScore = score2;
    }
    if (comparator(score3, targetScore)) {
        targetIdx = 3;
        targetScore = score3;
    }
    if (comparator(score4, targetScore)) {
        targetIdx = 4;
        targetScore = score4;
    }
    if (comparator(score5, targetScore)) {
        targetIdx = 5;
        targetScore = score5;
    }

    return targetIdx;
}

// Comparators

bool findLowestComparator(double a, double b) {
    return a < b;
}

bool findHighestComparator(double a, double b) {
    return a > b;
}

// Find lowest/highest functions

int findLowest(double score1, double score2, double score3, double score4, double score5) {
    return compareAll(findLowestComparator, score1, score2, score3, score4, score5);
};

int findHighest(double score1, double score2, double score3, double score4, double score5) {
    return compareAll(findHighestComparator, score1, score2, score3, score4, score5);
}

const string GET_JUDGE_DATA_PROMPT = "Enter a judge's score: ";
void getJudgeData(double &score) {
    double inputted;

    cout << GET_JUDGE_DATA_PROMPT;
    
    while (!(cin >> inputted) || inputted < 0 || inputted > 10) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "The score must be between 0.0 and 10.0" << endl;
        cout << GET_JUDGE_DATA_PROMPT;
    }

    score = inputted;
};
void calcScore(double score1, double score2, double score3, double score4, double score5) {
    int lowestIdx = findLowest(score1, score2, score3, score4, score5);
    int highestIdx = findHighest(score1, score2, score3, score4, score5);

    double trimmedSummation = 0.0;
    
    // We're checking if either of the highest or lowest indicies match the one
    // we're chceking right now. This is very reepated code. The obviously
    // preferred mechanism would be an array. However, a for loop would not work here
    // because we need to directly get the values of variables. If there was a method
    // like get_value_of_var_by_name(foo) we *could* use a for loop, however, that
    // pattern would definitely be a footgun because arrays exist.
    if (lowestIdx != 1 && highestIdx != 1)
        trimmedSummation += score1;
    if (lowestIdx != 2 && highestIdx != 2)
        trimmedSummation += score2;
    if (lowestIdx != 3 && highestIdx != 3)
        trimmedSummation += score3;
    if (lowestIdx != 4 && highestIdx != 4)
        trimmedSummation += score4;
    if (lowestIdx != 5 && highestIdx != 5)
        trimmedSummation += score5;
    
    // Dividing my 3.0 because we trim the highest and lowest (2 records)
    //  note:   the highest and lowest actually *can* be the same number. if
    //          the highest and lowest are the same then it's the same number
    //          repeated over and over again i.e: [1, 1, 1, 1, 1], so the score
    //          would correctly be 1.0. ([(1 + 1 + 1) / 3] = [3 / 3] = [1])
    //          This would not be possible if getLowest/getHighest just returned
    //          the value of the number instaed of the relative index

    //  note:   another edge case could be multiple highest/lowest scores, which is
    //          also handlded properly, because it's index based.
    cout << (trimmedSummation / 3.0);
};

int main()
{
	double score1;
	double score2;	
	double score3;	
	double score4;	
	double score5;	

	getJudgeData(score1);
    getJudgeData(score2);
    getJudgeData(score3);
    getJudgeData(score4);
    getJudgeData(score5);
		
    cout << endl << endl << "After dropping the lowest and highest scores, the average score was ";
    calcScore(score1, score2, score3, score4, score5);
    cout << "." << endl << endl;
	// system("PAUSE");
    return 0;
}

