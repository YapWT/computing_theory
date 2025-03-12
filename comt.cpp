#include <iostream>
#include <string> 
#include <cctype>
#include <algorithm>

using namespace std;

// Check if input starts with "System.out."
bool checkq0(string input) {
    return input.substr(0, 11) == "System.out.";
}

// Check if input contains print, printf, or println
bool checkq1(string input, int &matchedPrint) {
    string printSyntax[3] = {"print(", "printf(", "println("};
    
    for (string ps : printSyntax) {
        if (input.substr(11, ps.length()) == ps) { 
            matchedPrint = ps.length();
            return true;
        }
    }
    return false;
}

bool checkAlphanumeric(const string& check) {
    if (all_of(check.begin(), check.end(), ::isalnum)) return true;
    else if (check.empty()) return false;
    else cout << "Current version of algorithms does not support non-alphanumeric characters in print parameter." << endl;
    return false;
}

bool isValidQuotesType(string input, int start, string& quotesType) {
    if ((input.substr(start, 1) == input.substr(input.length() - 3, 1)) && input.substr(input.length() - 2) == ");") {
        quotesType = input.substr(start, 1);
        return (quotesType == "\"" || quotesType == "'");
    }
    return false;
}

bool checkParameter(string input, int printTypeLength) {
    printTypeLength += 11;

    if (input == "System.out.println();") return true;
    if (input.length() < printTypeLength + 4) return false;

    string quotesType;

    bool validQuotesResult = isValidQuotesType(input, printTypeLength, quotesType);
    bool validAlphaNumeric = checkAlphanumeric(input.substr(printTypeLength + 1, input.length() - printTypeLength - 4));

    if (printTypeLength - 11 == 7) {
        if (validQuotesResult && quotesType == "\"") { // valid printf syntax
            return (validAlphaNumeric);
        }
    } else {
        if (validQuotesResult) {
            if (quotesType == "'") // single quotes print 1 character
                return (validAlphaNumeric && ((input.substr(printTypeLength + 1, input.length() - printTypeLength - 4)).length() == 1));
            else return (validAlphaNumeric);
        }
    }
    return false;
}

// Print result
void printResult(bool valid) {
    cout << (valid ? "Valid" : "Invalid") << " Java print statement!" << endl;
}

int main() {
    string input;
    while (true) {
        cout << "Enter a Java print syntax (0 to exit): ";
        getline(cin, input); // Read entire input with spaces

        if (input == "0") break;
        
        // Check for "System.out."
        if (!checkq0(input)) {
            printResult(false);
            continue;
        }

        // Extract and check print type
        int printTypeLength;
        if (!checkq1(input, printTypeLength)) {
            printResult(false);
            continue;;
        }
        printResult(checkParameter(input, printTypeLength));
    }
    return 0;
}