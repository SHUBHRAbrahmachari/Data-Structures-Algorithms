/*
    Given two sentemces `sentence1` and `sentence2`.
    A sentence is a sequence of words separated by single spaces.
    Determine if it is possible to place any arbitary sequence of words(possible empty as well)
    inside one of the sentences such that both becomes identical.

    For example:

        sentence1 = "My name is Haley"
        sentence2 = "My Haley"

        o/p: true

        "name is" can be inserted in sentence2 to make them identical
*/

/*
    This is a typical prefix-suffix problem.
    See the words of smaller sentence must reside at prefix and/or suffix of the bigger sentence
*/

#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& s) {
    std::stringstream stream(s);
    std::string word;

    std::vector<std::string> words;

    while (stream >> word)
        words.emplace_back(word);

    return words;
}

// words1 would be smaller, so we will check words1 makes prefix and/or suffix of words2 or not
bool is_possible(const std::vector<std::string>& words1, const std::vector<std::string>& words2) {
    int word1_left_index = 0;
    int word2_left_index = 0;

    while (word1_left_index < words1.size() and words1[word1_left_index] == words2[word2_left_index]) {
        word1_left_index++;
        word2_left_index++;
    }

    // go the complete prefix only
    if (word1_left_index == words1.size())
        return true;

    int word1_right_index = words1.size()-1;
    int word2_right_index = words2.size()-1;

    while (word1_right_index >= word1_left_index) {
        // the moment we find a mistmatch, break as answwr is not possible
        if (words1[word1_right_index] != words2[word2_right_index])
            return false;

        word1_right_index--;
        word2_right_index--;
    }

    return true;
}

bool solve(const std::string& s1, const std::string& s2) {
    const std::vector<std::string> words1 = split(s1);
    const std::vector<std::string> words2 = split(s2);

    if (words1.size() <= words2.size())
        return is_possible(words1, words2);

    else
        return is_possible(words2, words1);
}


int main() {
    std::string s1, s2;
    std::cout << "\nEnter the sentences in two different lines please : \n\n";
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);

    if (solve(s1, s2))
        std::cout << "\nYes we can!";
    else
        std::cout << "No we cannot!";

    std::cout << std::endl << std::endl;

    return 0;
} 

