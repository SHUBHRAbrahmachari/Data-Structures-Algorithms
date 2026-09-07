/*
    Given a string s consisiting of lowercase english alphabets.
    You can perform following steps repeatedly.

    1> select a non-empty prefix and a non-empty suffix from the string such that they do not overlap.
    2> selected prefix and suffix must contain a single character.
    3> remove both prefix and suffix from s.

    Return the minimum length of the string after performing these steps any number of time.

    1 <= |s| <= 10^5

    Example:

        input: "ca", output = 2 => no prefix suffix found
        input "aabccabba", output 3 => remove ("aa", "a"), ("b", "bb") to keep having "cca"
*/

#include <iostream>

int solve(const std::string& s) {
    int left = 0;
    int right = s.size()-1;

    while (left <= right) {
        // either single character exists or no match found
        if (left == right or s[left] != s[right])
            break;

        const char ch = s[left];

        do {
            left += 1;
        } while (s[left] == ch and left < right);

        // that means all characters are same
        if (left >= right)
            return 0;

        do {
            right -= 1;
        } while (s[right] == ch);
    }

    return right - left + 1;
}

int main() {
    std::string s;
    std::cout << "\nEnter the string : ";
    std::cin >> s;

    const int answer = solve(s);
    std::cout << "\nThe minimum string length would be : " << answer << "\n\n";

    return 0;
}