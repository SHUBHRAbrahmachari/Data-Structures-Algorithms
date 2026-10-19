/*
    Given two words, `begin_word` and `end_word`.
    You are also given a list of words `word_list`.

    Return the minimum number of transformations we need to make in `begin_word`
    to reach the end_word.

    Every intermediate word must belong to the given list including the end_word.
    begin_word may or may not belong to the given list.

    > all cases are lower case
    > all words would be having same length
    > one transformation means altering exactly one alphabet.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

int solve(const std::string& begin_word, const std::string& end_word, std::vector<std::string>& word_list) {
    // we will maintain a single set to check what words are still unvisited
    std::unordered_set<std::string> unvisited_words(word_list.begin(), word_list.end());

    // to find the length of each word
    const int word_len = begin_word.size();

    // we explicitly add the begin word if it does not exist
    if (unvisited_words.find(begin_word) == unvisited_words.end())
        unvisited_words.emplace(begin_word);

    // get a queue for the BFS
    std::queue<std::string> que;

    // to count minimum transformation requirements
    int steps = 0;

    // initialize the BFS
    que.emplace(begin_word);
    unvisited_words.erase(begin_word);        // there's no point of coming back to the same word

    // start the BFS
    while (not que.empty()) {
        const int size = que.size();

        for (int i=0; i<size; i++) {
            std::string curr_word = que.front();
            que.pop();

            // we have found the end_word
            if (curr_word == end_word)
                return steps;

            for (int pos=0; pos<word_len; pos++) {
                char original_char = curr_word[pos];

                for (char alt_ch='a'; alt_ch<='z'; alt_ch++) {
                    // do the transformation
                    curr_word[pos] = alt_ch;

                    // check if the transformed word is unvisited or not
                    if (unvisited_words.find(curr_word) != unvisited_words.end()) {
                        que.emplace(curr_word);
                        unvisited_words.erase(curr_word);
                    }
                }

                // reset the original character
                curr_word[pos] = original_char;
            }
        }

        // increase steps
        steps++;
    }

    return -1;
}

int main() {
    std::string begin_word;
    std::cout  << "\nEnter the begin word : ";
    std::cin >> begin_word;

    std::string end_word;
    std::cout << "\nEnter the end word : ";
    std::cin >> end_word;

    int size;
    std::cout << "\nEnter the size of the word list : ";
    std::cin >> size;

    std::vector<std::string> word_list(size);
    std::cout << "\nKeep entering the words in the list : ";
    for (int i=0; i<size; i++)
        std::cin >> word_list[i];

    const int ans = solve(begin_word, end_word, word_list);
    if (ans == -1)
        std::cout << "\nThe end word is not reachable!\n\n";

    else
        std::cout << "\nWe need minimum " << ans << " transformation(s)\n\n";

    return 0;
}