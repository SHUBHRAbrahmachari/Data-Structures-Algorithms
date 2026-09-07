/*
    Given a string s,
    check if this string can be transformed into a valid palindrome with atmost
    1 deletion.

    1 <= |s| <= 10^6
*/

#include <iostream>

bool is_palindrome(const std::string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

bool solve(const std::string& s) {
bool solve(const std::string& s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            // Choice 1: Delete s[left]  -> Check s[left + 1 ... right]
            // Choice 2: Delete s[right] -> Check s[left ... right - 1]
            return is_palindrome(s, left + 1, right) || 
                   is_palindrome(s, left, right - 1);
        }
        left++;
        right--;
    }

    return true;
}

int main() {
    std::string s;
    std::cout << "\nEnter the string : ";
    std::cin >> s;

    bool flag = solve(s);
    if (flag)
        std::cout << "YES we CAN";
    else
        std::cout << "NO WE CANNOT";

    std::cout << "\n\n";

    return 0;
}

