#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inFile;
    // string temp;
    vector<string> temp;
    vector<string> keywords;
    vector<string> identifiers;
    vector<string> operators;
    vector<string> delimiters;
    vector<string> literals;

    int i = 0;
    inFile.open("input_file.txt");
    while(!inFile.eof()) { 
        inFile >> temp[i];
        i++;
    }
     return 0;
}
