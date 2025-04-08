#include <iostream>
#include <unordered_set>
using namespace std;

const int ROWS = 3;  
const int COLS = 3;  
const int MIN  = 1;  
const int MAX  = 9;  

// The value -1 works for the initial value, because the actual value of check
// could NEVER be negative as a magic square can only contian values that are positive
// integers between the values of 0 and 9 inclusive.
const int CHECK_INITIAL = -1;

void showResult(int[][COLS]);
void showArray(int[][COLS]);
bool isMagicSquare(int[][COLS]);
bool checkRange(int[][COLS]);
bool checkUnique(int[][COLS]);
bool checkRowSum(int[][COLS]);
bool checkColSum(int[][COLS]);
bool checkDiagSum(int[][COLS]);

int main()
{
  
    // int magicArray[ROWS][COLS] = {  {4, 9, 2},
    //                                 {3, 5, 7},
    //                                 {8, 1, 6} };
    // int normalArray[ROWS][COLS] = { {1, 2, 3},
    //                                 {4, 5, 6},
    //                                 {7, 8, 9} };
                                   
    // int magicArray[ROWS][COLS] = {  {8, 3, 4},
    //                                 {1, 5, 9},
    //                                 {6, 7, 2} };
    // int normalArray[ROWS][COLS] = { {5, 5, 5},
    //                                 {5, 5, 5},
    //                                 {5, 5, 5} };

    // int magicArray[ROWS][COLS] = {  {2, 9, 4},
    //                                 {7, 5, 3},
    //                                 {6, 1, 8} };
    // int normalArray[ROWS][COLS] = { {-1, 0, 1},
    //                                 {2, 0, -2},
    //                                 {3, 0, -3} };

    // int magicArray[ROWS][COLS] = {  {6, 1, 8},
    //                                 {7, 5, 3},
    //                                 {2, 9, 4} };
    // int normalArray[ROWS][COLS] = { {10, 20, 30},
    //                                 {40, 50, 60},
    //                                 {70, 80, 90} };

    int magicArray[ROWS][COLS] = {  {2, 7, 6},
                                    {9, 5, 1},
                                    {4, 3, 8} };
    int normalArray[ROWS][COLS] = { {12, 34, 56},
                                    {78, 90, 23},
                                    {45, 67, 89} };

    showArray(normalArray);
    showResult(normalArray);

    showArray(magicArray);
    showResult(magicArray);

 // system("PAUSE");
    return 0;
}


void showResult(int values[][COLS])
{
   
   if (isMagicSquare(values))
   {
      cout << "This is a Lo Shu magic square.\n\n";
   }
   else
   {
      
      cout << "This is not a Lo Shu magic square.\n\n";
   }
}


void showArray(int values[][COLS])
{

   for (int row = 0; row < ROWS; row++)
   {
      for (int col = 0; col < COLS; col++)
      {
       
         cout << values[row][col] << " ";
      }

    
      cout << endl;
   }
}

bool isMagicSquare(int matrix[][COLS]) {
    return checkRange(matrix)
        && checkUnique(matrix)
        && checkRowSum(matrix)
        && checkColSum(matrix)
        && checkDiagSum(matrix);
}

bool checkRange(int matrix[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // We're iterating over all the values in the matrix here
            // If they're outside of the range of [1, 9], we reject it
            // and return false early.
            int element = matrix[i][j];

            if (!(element >= 0 && element <= 9)) {
                // Outside of the acceptable range, reject and return early
                return false;
            }
        }
    }

    return true;
}

bool checkUnique(int matrix[][COLS]) {
    // For this case, I'm using a dictionary to check for uniqueness. As the
    // loop goes over all elements, it adds each of the values to the hit map.
    // If it then finds in a future element that that element has been previously
    // hit, then it'll reject the batch as not unique. Note that this syntax was
    // not covered yet, I had to look it up.
    
    // This pattern is more efficient as it doesn't create loop seption, or where
    // we would have to iterate over all 2D elements, then for every 2D element, do
    // a sub iteration over all elements again checking for duplicates.
    // That solution would be o(n^2), the solution I chose is o(n)

    unordered_set<int> hit;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // We're iterating over all the values in the matrix here
            // If they're outside of the range of [1, 9], we reject it
            // and return false early.
            int element = matrix[i][j];

            if (hit.find(element) != hit.end()) {
                // The element has already been hit, meaning that the set is not entirely
                // unique. Reject the batch.
                return false;
            } else {
                // The element hasn't been hit yet, meaning that it's still unique up to this
                // point
                hit.insert(element);
            }
        }
    }

    // Continuing with the logic above, if it escapes the for loop without returning early, the
    // entire batch would be unique up to the last element (basically: entire array is unique)
    return true;
}

bool checkRowSum(int matrix[][COLS]) {
    int check = CHECK_INITIAL;

    for (int i = 0; i < ROWS; i++) {
        int sum = 0;
        for (int j = 0; j < COLS; j++) {
            sum += matrix[i][j];
        }

        if (check == CHECK_INITIAL) {
            // We're the first iteration if this is true, therefore we need to set the baseline to
            // the current sum. The baseline we be what all future sums are checked against. In concept,
            // this doesn't need to be the first iteration, it could even be random. We just need ANY of
            // the row sums to check all others against to see if they all equal the same thing.
            check = sum;
        } else if (check != sum) {
            // The check is not equal to the initial value, and is not equal to the current sum. This means
            // the rows are NOT equal, therefore we early return
            return false;
        }
    }

    // If we were able to iterate over all values and escape the loop, all rows should be equal as a result
    return true;
}

bool checkColSum(int matrix[][COLS]) {
    int check = CHECK_INITIAL;
    
    for (int j = 0; j < COLS; j++) {
        int sum = 0;
        for (int i = 0; i < ROWS; i++) {
            sum += matrix[i][j];
        }

        // This follows the same logic as the above function, checkRowSum, check comments for that function
        // for implementation details
        if (check == CHECK_INITIAL) {
            check = sum;
        } else if (check != sum) {
            return false;
        }
    }

    return true;
};

bool checkDiagSum(int matrix[][COLS]) {
    int mainDiagonalSum = 0;
    int antiDiagonalSum = 0;

    for (int i = 0; i < ROWS; i++) {
        // If we look at a 2x2 matrix it makes it obvious how we can get the sum of both diagonals at the same
        // time:
        // 1 2
        // 3 4
        // The indicies of the diagonal are     [(0, 0), (1, 1)]
        //                                  and [(0, 1), (1, 0)]
        // The main diagonal in this case is just (i, i) and the anti is (i, cols-1-i)

        mainDiagonalSum += matrix[i][i];
        antiDiagonalSum += matrix[i][COLS - 1 - i];
    }

    return mainDiagonalSum == antiDiagonalSum;
};