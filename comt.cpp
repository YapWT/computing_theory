#include <iostream>
#include <string> 
#include <cctype>
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
            printTypeLength = ps.length();
            return true;
        }
    }
    return false;
}

bool isAlphanumericWithSpace(string check) {
    return (all_of(check.begin(), check.end(), [](char c) { return isalnum(c) || c == ' '; }));
}

// Validate quotation marks and determine their type
bool validQuotes(string input, int start, string& quotesType) {
    if ((input[start] == input[input.length() - 3]) && input.substr(input.length() - 2) == ");") {
        quotesType = input[start];
        return (quotesType == "\"" || quotesType == "'");
    }
    return false;
}

// Validate the parameter inside the print statement
bool checkParameter(string input, int printTypeLength) {
    printTypeLength += 11;

    if (input == "System.out.println();") return true;
    if (input.length() < printTypeLength + 4) return false;

    string quotesType, param = input.substr(printTypeLength + 1, input.length() - printTypeLength - 4);

    bool validQuotesResult = validQuotes(input, printTypeLength, quotesType);
    bool validAlphaNumeric = isAlphanumericWithSpace(param);

    if (!validAlphaNumeric || !validQuotesResult) return false; 

    if (printTypeLength - 11 == 7) return (quotesType == "\""); // valid printf syntax (only allow double quotes)
    
    return ((quotesType == "'" && param.length() == 1) || quotesType == "\""); // Single quotes should contain only one character
}

int main() {
    string input;
    while (true) {
        cout << "Enter a Java print statement (0 to exit): ";
        getline(cin, input); // Read entire input with spaces

        if (input == "0") break;
        
        int printTypeLength;

        if (!startsWithSystemOut(input) || !extractPrintType(input, printTypeLength) || !checkParameter(input, printTypeLength)) {
            cout << "Invalid Java print statement!" << endl;
            continue;
        }
        cout << "Valid Java print statement. " << endl;
    }
    return 0;
}