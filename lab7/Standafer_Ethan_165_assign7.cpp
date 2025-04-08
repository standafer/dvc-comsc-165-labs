#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


vector<string> getVector(string);
string getName(string);
bool search(string, vector<string>);
void displayResult(string, string, bool);
void writeToFile(string, vector<string>);
void reverseVector(vector<string> &);

void selectionSort(vector<string> &);

int main()
{
    string boyName, girlName;   
    bool boyNameFound, girlNameFound;  
    
    vector<string> boyNames(getVector("BoyNames.txt"));
    vector<string> girlNames(getVector("GirlNames.txt"));
    
    boyName = getName("boy's");   
    girlName = getName("girl's");
    
    selectionSort(boyNames);  
    selectionSort(girlNames);
    
    boyNameFound = search(boyName, boyNames); 
    girlNameFound = search(girlName, girlNames);
    
    displayResult("boy's", boyName, boyNameFound);    
    displayResult("girl's", girlName, girlNameFound);
    
    writeToFile("Boynames_asc.txt", boyNames); 
    writeToFile("Girlnames_asc.txt", girlNames);
    
    reverseVector(boyNames); 
    reverseVector(girlNames);
    
    writeToFile("Boynames_desc.txt", boyNames); 
    writeToFile("Girlnames_desc.txt", girlNames);
    
    cout<<endl;
    
    //system("PAUSE");
    return 0;
}

vector<string> getVector(string fileName) {
    ifstream inputObject;
    vector<string> built;
    
    // Had to add ../ here because the output directory is seperate from the directory that the
    // main C++ file is in.
    inputObject.open("../" + fileName);
    
    string name;

    while (inputObject >> name) {
        built.push_back(name);
    }
    
    inputObject.close();
    
    return built;
}

string getName(string label) {
    cout << "Enter a " << label << " name, or N if you do not wish to enter a " << label << " name: ";
    string name = "";
    
    cin >> name;
    cin.ignore(1000, '\n');
    
    if (name == "N") return "";
    
    return name;
}

bool search(string target, vector<string> vec) {
    // Iterate through each element in the vector
    for (int i = 0; i < vec.size(); i++) {
        // Get the current element at position i
        string item = vec[i];
        
        // If we find an exact match, immediately return true
        if (item == target) return true;
    }
    
    // If we've checked all elements and found no match, return false
    return false;
}

void displayResult(string label, string name, bool found) {
    if (name == "") {
        cout << "You chose not to enter a " << label << " name." << endl;
        return;
    }
    
    cout << name 
    << " is "
    << (found ? "" : "NOT ")
    << "one of the most popular "
    << label
    << " names." << endl;
}


void writeToFile(string filename, vector<string> vec) {
    ofstream outputFile(filename);
    
    for (int i = 0; i < vec.size(); i++) {
        string item = vec[i];
        outputFile << item << endl;
    }
    
    outputFile.close();
};

void reverseVector(vector<string> &values) {
    // Get the total number of elements in the vector
    int size = values.size();
    
    // Calculate the midpoint - we only need to swap up to halfway
    // (swapping beyond halfway would undo previous swaps)
    int half = size / 2;
    
    // Iterate from the beginning up to (but not including) the midpoint
    for (int i = 0; i < half; i++) {
        // Calculate the matching index from the opposite end
        int antiIndex = (size - 1) - i;
        
        // Store the current element temporarily before it gets overwritten
        string temp = values[i];
        
        // Replace the current element with its matching element from the end
        values[i] = values[antiIndex];
        
        // Complete the swap by placing the temporarily stored element
        // at the matching position from the end
        values[antiIndex] = temp;
    }
}

// BUILT-INS FOR ASSIGNMENT:
void selectionSort(vector<string> &arr)
{
    
    int startScan, minIndex;
    string minValue;
    
    for (startScan = 0; startScan < (arr.size() - 1); startScan++)
    {
        minIndex = startScan;
        minValue = arr[startScan];
        for(int index = startScan + 1; index < arr.size(); index++)
        {
            if (arr[index] < minValue)
            {
                minValue = arr[index];
                minIndex = index;
            }
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minValue;
    }
    
    
}

