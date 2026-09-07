/*
    Given two strings search_word and result_word. Return the minimum number of characters that must be
    appended to the end of search_word so that result_word becomes a subsequence of search_word.

    1 <= |earch_word|, |result_word| <= 10^5

    Example:

        search_word = "coaching", result_word = "coding"
        output: 4
        explanation: the prefix "co" of result_word appears as a subsequence in "coaching".
        To make the entire string "coding" a subsequence, 4 characters 'd, 'i', 'n' and 'g' are to be appended.
*/

/*
    Basically, we need to find out the longest possible prefix of 'result_word'
    occuring in 'search_word'.

    final answer: result_word.size - longest found prefix as subsequence
*/

#include <iostream>

int solve(const std::string& search_word, const std::string& result_word) {
    // looking for longest common prefix of result_word in search_word as a subsequence
    const int result_word_size = result_word.size();
    const int search_word_size = search_word.size();

    int result_word_index = 0;
    int search_word_index = 0;

    while (search_word_index < search_word_size) {
        // no more possibility further, stop searching
        if (result_word_index == result_word_size)
            break;

        if (search_word[search_word_index] == result_word[result_word_index])
            result_word_index++;

        search_word_index++;
    }

    // we got the maximum possible prefix length as `result_word_index`
    return result_word_size - result_word_index;
}

int main() {
    std::string search_word, result_word;
    std::cout << "\nEnter the search word and result word : ";
    std::cin >> search_word >> result_word;

    int result = solve(search_word, result_word);
    std::cout << "\nYou need minimum " << result << " character(s) to append" << std::endl << std::endl;

    return 0;
}