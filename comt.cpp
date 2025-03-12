#include <iostream>
#include <string> 
#include <algorithm>

using namespace std;

// Check if input starts with "System.out."
bool startsWithSystemOut(string input) {
    return input.rfind("System.out.", 0) == 0; // rfind at position 0 ensures it starts with "System.out."
}

// Check if input contains print, printf, or println and return the matched length
bool extractPrintType(string input, int &printTypeLength) {
    string printSyntax[3] = {"print(", "printf(", "println("};
    
    for (string ps : printSyntax) {
        if (input.substr(11, ps.length()) == ps) { 
            return printTypeLength = ps.length(), true;
        }
    }
    return false;
}

bool isAlphanumericWithSpace(string check) {
    return (all_of(check.begin(), check.end(), [](char c) { return isalnum(c) || c == ' '; }));
}

// Validate quotation marks and determine their type
bool validQuotes(string input, int start, string& quotesType) {
    char startQuotes = input[start], endQuotes = input[input.length() - 3];

    return quotesType = startQuotes, 
            (startQuotes == endQuotes && (startQuotes == '"' || startQuotes == '\'') && input.substr(input.length() - 2) == ");");
}

// Validate the parameter inside the print statement
bool checkParameter(string input, int printTypeLength) {
    printTypeLength += 11;

    if (input == "System.out.println();") return true;
    if (input.length() < printTypeLength + 4) return false;

    string quotesType, param = input.substr(printTypeLength + 1, input.length() - printTypeLength - 4); // get the string in the parenthesis 

    if (!validQuotes(input, printTypeLength, quotesType) || !isAlphanumericWithSpace(param)) return false; // not valid quotes or alphanumeric with space

    // valid printf syntax (only allow double quotes) 
    // Single quotes should contain only one character
    return (printTypeLength - 11 == 7) ? (quotesType == "\"") : ((quotesType == "'" && param.length() == 1) || quotesType == "\"");
}

int main() {
    string input;
    int printTypeLength = 0;

    while (cout << "Enter a Java print statement (0 to exit): ", getline(cin, input), input != "0") {
        cout << (startsWithSystemOut(input) && extractPrintType(input, printTypeLength) && checkParameter(input, printTypeLength) ? "Valid" : "Invalid") 
            << " Java print statement. " << endl;
    }

    return 0;
}