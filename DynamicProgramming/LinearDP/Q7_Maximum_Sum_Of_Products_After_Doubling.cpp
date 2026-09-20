/*
    Given an array of integers, each element may either be multiplied by 2
    or left unchanged.

    Find the maximum possible sum of products of adjacent elements after this choice.

    The score is sum(arr[i] * arr[i - 1]) for i in [1, N).

    1 <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<long long>& arr) {
    const size_t size = arr.size();
    
    if (size == 1)
        return 0;

    // DP states store the best score through the previous adjacent pair,
    // grouped by whether the previous element was doubled.
    long long max_sum_with_doubling = 0;
    long long max_sum_without_doubling = 0;

    for (size_t i=1; i<size; i++) {
        long long curr_sum_without_doubling = max_sum_without_doubling;
        long long curr_sum_with_doubling = max_sum_with_doubling;

        // Double arr[i]; the pair is scaled by 2 or 4 depending on arr[i - 1].
        max_sum_with_doubling = std::max(
            curr_sum_with_doubling + 4*arr[i]*arr[i-1],
            curr_sum_without_doubling + 2*arr[i]*arr[i-1]
        );

        // Leave arr[i] unchanged; only arr[i - 1] may scale this pair.
        max_sum_without_doubling = std::max(
            curr_sum_with_doubling + 2*arr[i]*arr[i-1],
            curr_sum_without_doubling + arr[i]*arr[i-1]
        );
    }

    return std::max(
        max_sum_with_doubling,
        max_sum_without_doubling
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum possible sum would be : " << answer << "\n\n";

    return 0;
}