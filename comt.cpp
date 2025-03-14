#include <iostream>
#include <string> 
#include <algorithm>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <chrono>

using namespace std;
using namespace chrono;

string randomeGeneratePrintStatement() {
    vector<string> prefixes = {"print(", "printf(", "println("};
    vector<string> quotoesType = {"\"", "\'"};
    vector<string> contents = {"Hello", "World", " ", "!", "123"};
    vector<string> allItems = {"print", "printf", "println", "(", "\"", "\'", "\"", "\'", "Hello", "World", " ", "!", "123", "System.out.", ")", ";", ");"};

    bool isGeneratedValidSyntax = rand() % 2; // 50% chance of valid vs invalid

    if (isGeneratedValidSyntax) {
        string prefix = prefixes[rand() % prefixes.size()];
        string content = contents[rand() % contents.size()];
        string startQuotes = quotoesType[rand() % quotoesType.size()];
        string endQuotes = quotoesType[rand() % quotoesType.size()];
    
        return "System.out." + prefix + startQuotes + content + endQuotes + ");";
    } else {
        string randomeResult;
        for (int i = 0; i < 8; i++) {
            randomeResult += allItems[rand() % allItems.size()];
        } return randomeResult;
    }

}

// Check if input starts with "System.out."
bool startsWithSystemOut(string input) {
    // cout << "Using find: " << input.find("System.out.", 0) << endl;
    // cout << "Using rfind: " << input.find("System.out.", 0) << endl;
    // cout << "Check the position of 'System.out.'': " << input.rfind("System.out.", 0) << endl;
    return input.rfind("System.out.", 0) == 0; // rfind at position 0 ensures it starts with "System.out."
}

// Check if input contains print, printf, or println and return the matched length
bool extractPrintType(string input, int &printTypeLength) {
    string printSyntax[3] = {"print(", "printf(", "println("};
    
    for (string ps : printSyntax) {
        if (input.substr(11, ps.length()) == ps) { 
            // cout << "Check the print type: " << ps << endl;
            return printTypeLength = ps.length(), true;
        }
    }
    return false;
}

bool isAlphanumericWithSpace(string check) {
    // cout << "Check the parameter inside the print statement: " << check << endl;
    return (all_of(check.begin(), check.end(), [](char c) { return isalnum(c) || c == ' '; }));
}

// Validate quotation marks and determine their type
bool validQuotes(string input, int start, char& quotesType) {
    char startQuotes = input[start], endQuotes = input[input.length() - 3];
    // cout << "Check the start quotes: " << startQuotes << "\nCheck the end quotes: " << endQuotes << "\nCheck the closing parenthesis: " << input.substr(input.length() - 2) << endl;
    return quotesType = startQuotes, 
            (startQuotes == endQuotes && (startQuotes == '"' || startQuotes == '\'') && input.substr(input.length() - 2) == ");");
}

// Validate the parameter inside the print statement
bool checkParameter(string input, int printTypeLength) {
    printTypeLength += 11;
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    if (input == "System.out.println();") return true;
    if (input.length() < printTypeLength + 4) return false;

    char quotesType;
    string param = input.substr(printTypeLength + 1, input.length() - printTypeLength - 4); // get the string in the parenthesis 

    if (!validQuotes(input, printTypeLength, quotesType) || !isAlphanumericWithSpace(param)) return false; // not valid quotes or alphanumeric with space

    // valid printf syntax (only allow double quotes) 
    // Single quotes should contain only one character

    // if (printTypeLength - 11 == 7) cout << "Check the printf is only using double quotes: " << quotesType << endl;
    // else if (quotesType == '\'') cout << "Check is it single quotes if not printf: " << quotesType << "\nTo ensure its only 1 charater: " << param.length() << endl;
    return (printTypeLength - 11 == 7) ? (quotesType == '"') : ((quotesType == '\'' && param.length() == 1) || quotesType == '\"');
}

int main() {
    string input;
    int printTypeLength = 0;

    while (cout << "Enter a Java print statement (0 to exit): ", getline(cin, input), input != "0") {       
        auto start = high_resolution_clock::now(); 
        
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        cout << (startsWithSystemOut(input) && extractPrintType(input, printTypeLength) && checkParameter(input, printTypeLength) ? "Valid" : "\033[44mInvalid\033[0m") 
            << " Java print statement. " << endl;
        
        auto stop = high_resolution_clock::now(); 
        cout << "Time taken: " << (duration_cast<microseconds>(stop - start)).count() << endl;
    }
    
    // input =  "System.out.println();";
    // input =  "System.out.println(');";
    // while (true) {
    //     // check the possibility of infinity loop
    //     if (startsWithSystemOut(input)) break; 
    //     if (startsWithSystemOut(input) && extractPrintType(input, printTypeLength)) break; 
    //     if (startsWithSystemOut(input) && extractPrintType(input, printTypeLength) && checkParameter(input, printTypeLength)) break; 
    // }

    // input = "System.out.println();";
    // for (int i = 0; i < 1000; i++) {
    //     cout << (startsWithSystemOut(input) && extractPrintType(input, printTypeLength) && checkParameter(input, printTypeLength) ? "is Valid" : "\033[44mInvalid\033[0m") 
    //         << " Java print statement. " << endl;
    // }

    // string randomResult;
    // srand(time(0));  // Seed random number generator
    // while (cout << "Do u want to exit the program (0 = yes)", cin >> input, input != "0") {
    //     for (int i = 0; i < 10; i++) {
    //         cout << (randomResult = randomeGeneratePrintStatement()) << endl;
    //         cout << (startsWithSystemOut(randomResult) && extractPrintType(randomResult, printTypeLength) && checkParameter(randomResult, printTypeLength) ? "is Valid" : "\033[44mis Invalid\033[0m") 
    //             << " Java print statement. " << endl;
    //     }
    // }

    return 0;
}