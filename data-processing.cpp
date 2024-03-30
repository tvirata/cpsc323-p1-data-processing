#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <map>
#include <iomanip>

using namespace std;

// Helper function to read the entire content of the file
string readCodeFromFile(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Function to remove comments and unnecessary whitespaces
string removeCommentsAndWhitespaces(const string& source) {
    string code;
    regex commentRegex(R"((\/\/.*|\/\*.*?\*\/))");
    regex whitespaceRegex("\\s+");
    // Remove comments
    code = regex_replace(source, commentRegex, "");
    // Remove multiple consecutive whitespaces
    code = regex_replace(code, whitespaceRegex, " ");
    // Trim leading and trailing whitespaces
    code = regex_replace(code, regex("^\\s+|\\s+$"), "");
    return code;
}

// Function to tokenize the source code
map<string, vector<string>> tokenize(const string& source) {
    // Define regex patterns for each token category
    regex keywordRegex(R"(\b(int|float|return|if|else|while|for|do|break|continue|switch|case|default|void|char|double|bool)\b)");
    regex identifierRegex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)");
    regex literalRegex(R"(\b\d+\.?\d*\b)");
    regex operatorRegex(R"([\+\-\*\/=<>!&\|%^~]+)");
    regex delimiterRegex(R"([,;\{\}\[\]\(\)])");

    map<string, vector<string>> tokens{
        {"Keywords", {}},
        {"Identifiers", {}},
        {"Literals", {}},
        {"Operators", {}},
        {"Delimiters", {}}
    };

    // Find and categorize tokens
    auto categorizeToken = [&](const string& token, const regex& re, const string& category) {
        sregex_iterator begin(token.begin(), token.end(), re), end;
        for (auto it = begin; it != end; ++it) {
            tokens[category].push_back(it->str());
        }
    };

    // Tokenizing process
    istringstream sourceStream(source);
    string token;
    while (sourceStream >> token) {
        categorizeToken(token, keywordRegex, "Keywords");
        categorizeToken(token, identifierRegex, "Identifiers");
        categorizeToken(token, literalRegex, "Literals");
        categorizeToken(token, operatorRegex, "Operators");
        categorizeToken(token, delimiterRegex, "Delimiters");
    }
    
    return tokens;
}

// Function to print the tokens in a tabular format
void printTokensInTable(const map<string, vector<string>>& tokens) {
    for (const auto& category : tokens) {
        cout << left << setw(12) << category.first << " | ";
        for (const auto& token : category.second) {
            cout << token << " ";
        }
        cout << endl;
    }
}

int main() {
    string filepath = "input_file.txt"; // Replace with your actual file path

    try {
        // Step 1: Read code from a file
        string code = readCodeFromFile(filepath);

        // Step 2: Process the data to remove comments and excess whitespace
        string cleanedCode = removeCommentsAndWhitespaces(code);

        // Step 3 & 4: Tokenize the cleaned code and print the cleaned code
        cout << "Cleaned Code: " << endl << cleanedCode << endl << endl;

        // Step 5: Tokenize the remaining code and print in tabular form
        auto tokens = tokenize(cleanedCode);
        cout << "Tokenized Code: " << endl;
        printTokensInTable(tokens);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
