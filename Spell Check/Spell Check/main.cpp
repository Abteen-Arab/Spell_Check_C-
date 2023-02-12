#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

std::vector<std::string> dictionary; // A vector to store the words in the dictionary
std::map<std::string, std::vector<std::string>> suggestions; // A map to store suggestions for misspelled words

// A function to calculate the Levenshtein distance between two strings
int levenshteinDistance(std::string word1, std::string word2) {
    long m = word1.length();
    long n = word2.length();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            }
            else if (j == 0) {
                dp[i][j] = i;
            }
            else if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + std::min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
            }
        }
    }
    return dp[m][n];
}

bool spellCheck(std::string word) {
    // Iterate through the dictionary vector and check if the word is present in the dictionary
    for (int i = 0; i < dictionary.size(); i++) {
        if (dictionary[i] == word) {
            return true;
        }
    }
    return false;
}

void generateSuggestions(std::string word) {
    // Iterate through the dictionary vector and generate suggestions for the misspelled word
    for (int i = 0; i < dictionary.size(); i++) {
        int distance = levenshteinDistance(word, dictionary[i]);
        if (distance <= 2) {
            suggestions[word].push_back(dictionary[i]);
        }
    }
}

int main() {
    // Read the dictionary file into the dictionary vector
    std::ifstream dictFile("dictionary.txt");
    std::string word;
    while (dictFile >> word) {
        dictionary.push_back(word);
    }
    
    // Read the input file and check for spelling mistakes
    std::ifstream inputFile("input.txt");
    while (inputFile >> word) {
        if (!spellCheck(word)) {
            std::cout << word << " is a spelling mistake" << std::endl;
            if (suggestions.count(word) == 0) {
                generateSuggestions(word);
            }
            std::cout << "Did you mean: ";
            for (int i = 0; i < suggestions[word].size(); i++) {
                std::cout << suggestions[word][i] << " ";
            }
            std::
            cout << std::endl << std::endl;
            
        }
    }
    return 0;
}
