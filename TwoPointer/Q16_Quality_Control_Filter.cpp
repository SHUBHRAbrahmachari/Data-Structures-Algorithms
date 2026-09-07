/*
    Given a string s with lowercase english alphabets only.
    Also given an integer K.

    Return the longest contiguous substring such that every
    ditinct character appears atleast k times

    1 <= k <= |s| <= 10^4
*/

#include <iostream>
#include <vector>
#include <unordered_map>

/*
    Let us use a Divide & Conquer approach here.
    Find frequency of each and every alphabet in the string
    Find any alphabet that does have frequency less than K.
    So this alphabet is never a part of a valid window right?

    look for the right and left part for answer and return the maximum value

    if no such element exists, simply size is the answer.
*/

// worst case: O(N)
int find_longest_substring_length(const std::string s, const int k) {
    if (k > s.size())
        return 0;

    // count frequency of each character
    std::unordered_map<char, int> freq;
    for (char c : s) {
        auto itr = freq.find(c);
        if (itr == freq.end())
            freq.emplace(c, 1);
        else
            freq.at(c) += 1;
    }

    for (size_t i=0; i<s.size(); i++) {
        // this can never be in a valid substring
        if (freq.at(s.at(i)) < k) {
            return std::max(
                find_longest_substring_length(s.substr(0, i), k),
                find_longest_substring_length(s.substr(i+1), k)
            );
        }
    }

    // no such element exists
    return s.size();
}


int main() {
    std::string s;
    std::cout << "\nEnter the string : ";
    std::cin >> s;

    int k;
    std::cout << "\nEnter the value of k : ";
    std::cin >> k;

    const size_t length = find_longest_substring_length(s, k);
    std::cout << "\nMaximum length of such a substring would be : " << length << "\n\n";

    return 0;
}