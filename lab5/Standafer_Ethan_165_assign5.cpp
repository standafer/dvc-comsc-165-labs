#include <iostream>

using namespace std;

const int COLS = 5;
const int ROWS = 4;

int getTotal(int (&array)[ROWS][COLS]) {
    int summation = 0;

    // Iterate over all possible x and all possible y,
    // which are i and j respectively
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int value = array[i][j];
            // Increment the summation value
            summation += value;
        }
    }

    // Return it
    return summation;
};

float getAverage(int (&array)[ROWS][COLS]) {
    // Take the summation of the matrix
    float summation = getTotal(array);
    
    // Divide it by the number of elements, which is guaranteed to be
    // ROWS * COLS. There's no need to do a +1 adjustement since ROWS/COLS
    // are already C++ lengths (already offset by +1)
    return (summation / (ROWS * COLS));
}

int getRowTotal(int (&array)[ROWS][COLS], int rowIdx) {
    int summation = 0;

    // Since we're trying to get all of the row values, the positions would
    // be P(0...COLS, n) where m is the target row. Given that n is a constant
    // value, we don't need to perform two iterations, just iterate 0 through COLS
    for (int j = 0; j < COLS; j++) {
        int value = array[rowIdx][j];
        // Increment the summation value
        summation += value;
    }

    return summation;
}

int getColTotal(int (&array)[ROWS][COLS], int colIdx) {
    int summation = 0;

    // Similar concept to the past implementation, however, the constant variable is 
    // flipped P(n, 0...ROWS). So same implementation. For sake for consistency, I'll
    // keep i = x & j = y, so this would be an "i" iteration
    for (int i = 0; i < ROWS; i++) {
        int value = array[i][colIdx];
        // Increment the summation value
        summation += value;
    }

    return summation;
}

int getHighestInRow(int (&array)[ROWS][COLS], int rowIdx) {
    int highest = array[rowIdx][0];

    // This follows a very similar logic pattern to the getTotalInRow implementation.
    // The only difference being, instead of incrementing a value by n we instead
    // just check if it's greater than the current stored value, and if it is, we
    // replace it with the new value

    // Additionally, since we're already setting the highest to the first value, we 
    // don't need to process the first value since it's automatically the highest
    for (int j = 1; j < COLS; j++) {
        int value = array[rowIdx][j];
        if (value > highest)
            highest = value;
    }

    return highest;
}

int getLowestInRow(int (&array)[ROWS][COLS], int rowIdx) {
    int lowest = array[rowIdx][0];

    // Logic identical to getHighestInRow, just changing the variable name and converting
    // from a greater than operator to a lesser than operator
    for (int j = 1; j < COLS; j++) {
        int value = array[rowIdx][j];
        if (value < lowest)
        lowest = value;
    }

    return lowest;
}


int main() {
    int testArray[ROWS][COLS] = {
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 }
    };

    cout << "The total of the array elements is " << getTotal(testArray) << endl;
    cout << "The average value of an element is " << getAverage(testArray) << endl;
    cout << "The total of row 0 is " << getRowTotal(testArray, 0) << endl;
    cout << "The total of col 2 is " << getColTotal(testArray, 2) << endl;
    cout << "The highest value in row 2 is " << getHighestInRow(testArray, 2) << endl;
    cout << "The lowest value in row 2 is " << getLowestInRow(testArray, 2) << endl;

    return 0;
}
