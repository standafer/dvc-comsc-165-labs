#include <iostream>
using namespace std;

int getMode(int*, int);
int* makeArray(int);

// main has been completed for you

int main()
{	
	const int SIZE = 5;
	int test[SIZE] = {1, 2, 3, 4, 5};
	
    int mode;

	mode = getMode(test, SIZE);

	if (mode == -1)
		cout << "The test set has no mode.\n";
	else
		cout << "\nThe mode of the test set is: " 
		     << mode << endl;

    // // system("PAUSE");
	// return 0;
}

int getMode(int *array, int size)
{
	
	// frequencies will point at a dynamically allocated array
	// in this assignment pointer notation (i.e., using the *) should always be used instead of
	// bracket/subscript notation (i.e., using the []).
	
	int* frequencies = makeArray(size);
	
	for (int i = 0; i < size; i++) {
        // For every element, we're checking how many times that that element occurs by doing
        // a sub iteration with a domain of every number in integers between 0 and size. We
        // purposeffully include ourselves in this scope, checking the current value of i,
        // in the sub loop of j such that it increments properly.
        
        // An alternative approach to this might be to instead make the increment start at 1
        // and then skip i during the j loop. This is not the approach I chose to take for the
        // sake of logic conciseness (single source of truth: the loop)
        int comparator = *(array + i);
        int count = 0;

        for (int j = 0; j < size; j++) {
            // Access the element using rotation syntax. Intentionally not using the [n] syntax
            // due to program requirements
            int element = *(array + j);

            // Check for a match of the comparator (master element) to the sub loop element
            if (comparator == element) {
                // It's a match, increment the count
                count ++;
            }
        }

        *(frequencies + i) = count;
    }

    // Note that this variable stores VALUES and NOT indicies.
    // This variable will only be replaced if:
    //  a) the value has a frequency that is greater than highestFreq
    int mostCommon = -1;
    // Note that highestFreq is intentionally set to the value of 1, requiring that any that
    // intend on replacing it must be greater than 1, which is part of the program requirements.
    int highestFreq = 1;
    
    for (int i = 0; i < size; i++) {
        int frequency = *(frequencies + i);
        
        // Greater than or equal to here in order to satisfy the tie logic: always replace.
        if (frequency > highestFreq) {
            // If both criterion are met, then replace mostCommon with the value of the 
            mostCommon = *(array + i);
            highestFreq = frequency;
        }
    }
	
	delete[] frequencies; // Do NOT remove this -- this needs to be at the end of the function
	                       // to remove the dynamically allocated frequencies array from memory
	                       // when it is no longer needed.
	
    // We now have the highest most common element defined to program spec. f none of the values occur
    // more than once, then there is no mode, and the function should return -1.
    return mostCommon;
}



// makeArray has been completed for you

int* makeArray(int size)
{
	return new int[size];
}