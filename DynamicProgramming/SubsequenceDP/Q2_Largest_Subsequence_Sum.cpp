/*
    Given an array of integers.
    We need to find the maximum possible non-empty subsequence sum we can have from this array

    1 <= N <= 10^5
    -10^5 <= A[i] <= 10^5

    #O(N)
*/

#include <iostream>
#include <vector>
#include <limits>

long long solve(const std::vector<long long>& arr) {
    // Store the size of the array.
    const int size = arr.size();

    // If the array has only one element, that element itself is the answer.
    if (size == 1)
        return arr[0];

    /*
        DP idea:

        memory[i] = maximum sum of a subsequence that ends at index i.
        At each index, we either:
        - extend the previous subsequence, or
        - start a fresh subsequence from arr[i]

        This is why we take the maximum of:
            max_sum + arr[i]
            arr[i]
    */
    std::vector<long long> memory(size);

    // max_sum keeps track of the best answer seen so far.
    long long max_sum = std::numeric_limits<long long>::min()/2;

    for (int i=0; i<size; i++) {
        // Decide whether to continue the previous best subsequence or start over at i.
        memory[i] = std::max(
            max_sum + arr[i],
            arr[i]
        );

        // Update the global best answer after considering the current index.
        max_sum = std::max(
            max_sum,
            memory[i]
        );
    }

    return max_sum;
}

int main() {
    int size;
    std::cout << "\nEnter the number of elements you want to have : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum possible non-empty subsequence sum would be : " << answer << std::endl << std::endl;

    return 0;
}