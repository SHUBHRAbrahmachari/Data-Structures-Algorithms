/*
    Problem:
    We are given an array of integers and need the maximum possible length of a subsequence
    such that any two consecutive picked elements differ by exactly 1 in absolute value.

    Example:
    arr = [1, 2, 1, 2, 3]
    A valid subsequence is [1, 2, 1, 2, 3], because each adjacent difference is 1.
    The answer is 5.

    Constraints:
    1 <= N <= 10^5
    -10^5 <= A[i] <= 10^5

    DP idea:
    For every value x, we store the best subsequence length that ends with either x-1 or x+1.

    If we are processing current value ele, then the subsequence ending at ele can be formed by
    extending a subsequence that ended at ele-1 or ele+1.

    Hence:
        bestEndingAt[ele] = 1 + max(bestEndingAt[ele-1], bestEndingAt[ele+1])

    We also keep a global maximum over all values seen so far.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

int solve(const std::vector<int>& arr) {
    // memory[value] = maximum length of a valid subsequence that ends exactly at `value`.
    // Example: if memory[2] = 5, then we have a valid subsequence of length 5 ending at 2.
    std::unordered_map<int, int> memory;

    // max_len stores the best answer seen so far across all values.
    int max_len = 1;

    for (const int ele : arr) {
        // Look for the best subsequence that ends with ele-1.
        auto itr1 = memory.find(ele - 1);
        int max_prev_len1 = (itr1 == memory.end()) ? 0 : itr1->second;

        // Look for the best subsequence that ends with ele+1.
        auto itr2 = memory.find(ele + 1);
        int max_prev_len2 = (itr2 == memory.end()) ? 0 : itr2->second;

        // The subsequence ending at ele can extend from either side.
        int max_prev_len = std::max(max_prev_len1, max_prev_len2);

        // Check whether we already saw this value before.
        auto itr = memory.find(ele);

        // This will store the best possible length for the current element.
        int new_len = -1;

        // Case 1: this value has never appeared before.
        // Then the new subsequence ending at ele starts from this element itself.
        if (itr == memory.end()) {
            new_len = 1 + max_prev_len;
            memory.emplace(ele, new_len);
        }

        else {
            // Case 2: this value was seen before.
            // We may keep the previous best or improve it by extending a valid chain ending at ele-1 / ele+1.
            new_len = std::max(itr->second, 1 + max_prev_len);
            itr->second = new_len;
        }

        // Update the global answer.
        max_len = std::max(max_len, new_len);
    }

    return max_len;
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of elements : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements : ";
    for (size_t i = 0; i < size; i++)
        std::cin >> arr[i];

    const int answer = solve(arr);
    std::cout << "\nThe maximum length of such subsequence would be : " << answer << "\n\n";

    return 0;
}

