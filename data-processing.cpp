#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Function to check if a line is a comment
bool isComment(const string& line) {
    // Trim leading whitespace
    size_t start = line.find_first_not_of(" \t");
    if (start == string::npos) return false; // line was all whitespace
    return line[start] == '/'; // comment lines start with '/'
}

// Function to trim whitespace from the start and end of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

int main() {
    ifstream inFile("input_file.txt");
    string line;
    vector<string> cleanedLines;

    if (!inFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    while (getline(inFile, line)) {
        // Check if the line is a comment or empty
        if (!isComment(line) && !line.empty()) {
            // Trim and add to cleaned lines
            cleanedLines.push_back(trim(line));
        }
    }
    inFile.close();

    // Print the cleaned code
    for (const auto& cleanLine : cleanedLines) {
        cout << cleanLine << endl;
    }

    // TODO: Implement tokenization based on your requirements

    return 0;
}
