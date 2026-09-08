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

        max_sum stores the best subsequence sum found so far. For each element,
        curr_sum either starts a new subsequence at that element or extends the
        best subsequence found so far. No array is needed because only the
        running best sum is used by the next iteration.
    */
    long long max_sum = std::numeric_limits<long long>::min()/2;

    for (long long ele : arr) {
        // Start at ele or extend the best subsequence found so far.
        long long curr_sum = std::max(
            ele,
            ele + max_sum
        );

        // Keep the best subsequence sum, including the option to skip ele.
        max_sum = std::max(
            max_sum,
            curr_sum
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