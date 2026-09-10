/*
    Find the maximum sum of a non-empty subsequence of arr.

    If i and j are consecutive selected indices with i < j, they must satisfy:
        j - i <= k

    Constraints:
        1 <= k <= n <= 10^5
        -10^9 <= arr[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <limits>
#include <deque>

long long solve(const std::vector<long long>& arr, const int k) {
    // A state can only extend a subsequence whose last index is in [j - k, j - 1].
    const int size = arr.size();

    if (size == 1)
        return arr[0];

    // memory[i] is the maximum sum of a valid subsequence that ends exactly at i.
    // The deque stores candidate indices in decreasing order of memory[index].
    // Therefore, its front is the best predecessor currently allowed for j.
    std::vector<long long> memory(size);
    std::deque<int> dq;

    // The answer may end at any index, so keep the largest state seen so far.
    long long max_sum = std::numeric_limits<long long>::min();

    for (int j=0; j<size; j++) {
        // Remove predecessors that are too far behind to connect to index j.
        while (not dq.empty() and dq.front() < j-k)
            dq.pop_front();

        // Either start a new subsequence at j or extend the best valid predecessor.
        memory[j] = std::max(
            arr[j] + (dq.empty() ? 0 : memory[dq.front()]),
            arr[j]
        );

        max_sum = std::max(
            max_sum,
            memory[j]
        );

        // Any index with a smaller (or equal) state can never be the best
        // predecessor while index j is available, so discard it from the back.
        while (not dq.empty() and memory[j] >= memory[dq.back()])
            dq.pop_back();

        dq.emplace_back(j);
    }

    return max_sum;
}

int main() {
    int size;
    std::cout << "\nEnter the total number of elements to have : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements in the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the value of k : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum subarray sum would be : " << answer << std::endl << std::endl;

    return 0;
}