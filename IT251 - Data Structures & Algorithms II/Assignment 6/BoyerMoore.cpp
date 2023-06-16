#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

//BAD CHARACTER HEURISTIC
// Function to generate the bad character table
// Parameters:
// - pattern: the pattern string
// - badCharacterTable: reference to an unordered_map to store the bad character table
void generateBadCharacterTable(string &pattern, unordered_map<char, int> &badCharacterTable) {
    int patternLength = pattern.length();

    // Initializing all characters with a default shift equal to pattern length
    for (int i = 0; i < 256; i++) {
        badCharacterTable[char(i)] = patternLength;
    }

    // Assigning appropriate shifts for characters present in the pattern
    for (int i = 0; i < patternLength - 1; i++) {
        badCharacterTable[pattern[i]] = patternLength - 1 - i;
    }
}

// Boyer-Moore algorithm using the bad character rule
// Parameters:
// - text: the text string to search within
// - pattern: the pattern string to find
// Returns:
// - vector containing the starting positions of occurrences of the pattern in the text
vector<int> boyerMooreBadCharacter(string &text, string &pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();

    // Generating the bad character table
    unordered_map<char, int> badCharacterTable;
    generateBadCharacterTable(pattern, badCharacterTable);

    vector<int> occurrences;

    int i = 0;
    while (i <= textLength - patternLength) {
        int j = patternLength - 1;

        // Comparing characters from right to left
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            // Pattern found, adding the occurrence and shift by one position
            occurrences.push_back(i);
            i += badCharacterTable[text[i + patternLength]];
        } else {
            // Computing the bad character shift based on the bad character table
            int badCharacterShift = badCharacterTable[text[i + j]] - (patternLength - 1 - j);
            i += badCharacterShift;
        }
    }
    
    return occurrences;
}


// Function to generate the good suffix table
// Parameters:
// - pattern: the pattern string
// Returns:
// - vector containing the good suffix table
vector<int> generateGoodSuffixTable(string &pattern) {
    int m = pattern.length();
    vector<int> suffixes(m + 1, 0);  // Array to store the suffix lengths
    vector<int> border(m + 1, 0);    // Array to store the border lengths

    int i = m;
    int j = m + 1;
    border[i] = j;

    // Computing borders and suffixes
    while (i > 0) {
        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
            if (suffixes[j] == 0) {
                suffixes[j] = j - i;
            }
            if (border[j] == 0) {
                border[j] = j - i;
            }
            j = border[j];
        }
        i--;
        j--;
        border[i] = j;
    }

    // Filling in remaining suffixes
    j = border[0];
    for (i = 0; i <= m; i++) {
        if (suffixes[i] == 0) {
            suffixes[i] = j;
        }
        if (i == j) {
            j = border[j];
        }
    }

    return suffixes;
}


// Boyer-Moore algorithm using the good suffix rule
// Parameters:
// - text: the text string to search within
// - pattern: the pattern string to find
// Returns:
// - vector containing the starting positions of occurrences of the pattern in the text
vector<int> boyerMooreGoodSuffix(string &text, string &pattern) {
    vector<int> occurrences;  // Vector to store the starting positions of occurrences
    int n = text.length();
    int m = pattern.length();
    vector<int> goodSuffix = generateGoodSuffixTable(pattern);  // Generate the good suffix table

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        // Compare characters from right to left
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            // Pattern found, add the occurrence and shift using the first entry of the good suffix table
            occurrences.push_back(i);
            i += goodSuffix[0];
        } else {
            // Compute the shift based on the good suffix table
            i += max(1, goodSuffix[j + 1]);
        }
    }

    return occurrences;
}


//BOYER MOORE WITH BOTH HEURISTICS
// Boyer-Moore algorithm using the good suffix rule
// Parameters:
// - text: the text string to search within
// - pattern: the pattern string to find
// Returns:
// - vector containing the starting positions of occurrences of the pattern in the text
// Boyer-Moore algorithm for string matching
// Parameters:
// - text: the text string to search within
// - pattern: the pattern string to find
// Returns:
// - vector containing the starting positions of occurrences of the pattern in the text
vector<int> boyerMoore(string &text, string &pattern) {
    int n = text.length();
    int m = pattern.length();

    unordered_map<char, int> badChar;  // Bad character table
    generateBadCharacterTable(pattern, badChar);  // Generate the bad character table
    vector<int> goodSuffix = generateGoodSuffixTable(pattern);  // Generate the good suffix table
    vector<int> occurrences;  // Vector to store the starting positions of occurrences

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        // Comparing characters from right to left
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            // Pattern found, adding the occurrence and shifting using the first entry of the good suffix table
            occurrences.push_back(i);
            i += goodSuffix[0];
        } else {
            // Computing the shifting based on the bad character shift and the good suffix shift (the maximum of them)
            int badCharacterShift = badChar[text[i + j]] - (m - 1 - j);
            int suffixShift = goodSuffix[j + 1];
            i += max(1, max(badCharacterShift, suffixShift));
        }
    }

    return occurrences;
}



int main(){
    
    string text;
    string pattern;

    cout << endl << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern: ";
    getline(cin, pattern);

    vector<int> occurrences = boyerMooreBadCharacter(text, pattern);

    cout<<endl<<"Bayer Moore using only bad character heuristic: "<<endl;

    if (occurrences.size() == 0)
    {
        cout << "No matches found." << endl;
    }
    else
    {
        cout << "Match found at index ";
        for (int i = 0; i < occurrences.size(); i++)
        {
            cout << occurrences[i];
            if (i != occurrences.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "." << endl;
    }

        cout<<endl<<"Bayer Moore using only good suffix heuristic: "<<endl;

        vector <int> occurrences2 = boyerMooreGoodSuffix(text, pattern);

        if (occurrences2.size() == 0)
        {
            cout << "No matches found." << endl;
        }
        else
        {
            cout << "Match found at index ";
            for (int i = 0; i < occurrences2.size(); i++)
            {
                cout << occurrences2[i];
                if (i != occurrences2.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "." << endl;
        }


        cout<<endl<<"Bayer Moore using both bad character and good suffix heuristic: "<<endl;
        vector <int> occurrences3 = boyerMoore(text, pattern);

        if (occurrences3.size() == 0)
        {
            cout << "No matches found." << endl;
        }
        else
        {
            cout << "Match found at index ";
            for (int i = 0; i < occurrences3.size(); i++)
            {
                cout << occurrences3[i];
                if (i != occurrences3.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "." << endl;
        }

    return 0;
}