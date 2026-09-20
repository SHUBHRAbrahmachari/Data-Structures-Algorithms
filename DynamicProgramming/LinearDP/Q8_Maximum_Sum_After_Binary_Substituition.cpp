/*
    You are given an array of integers and two replacement values, L and R.

    For every element, choose exactly one of these options:

        1. Keep arr[i] unchanged.
        2. Replace arr[i] with L.
        3. Replace arr[i] with R.

    Maximize the score over all adjacent pairs. The value used for each pair is:

    |chosen[i] - chosen[i - 1]| * original(arr[i - 1]) for i in [0, N).

    The first element contributes no score because it has no preceding element.
    Since a pair depends only on the chosen values at two adjacent positions,
    dynamic programming can keep the best score for each possible chosen value
    of the previous element: original, L, or R.

    1 <= N <= 10^5
    -10^4 <= L < R <= 10^5
    -10^4 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<long long>& arr, const int l, const int r) {
    const size_t size = arr.size();

    if (size == 1)
        return 0;

    // Each state is the best score through the previous index, categorized by
    // whether that previous element is original, replaced by L, or replaced by R.
    long long max_sum_without_update = 0;
    long long max_sum_with_l_update = 0;
    long long max_sum_with_r_update = 0;

    for (size_t i=1; i<size; i++) {
        long long curr_sum_without_update = max_sum_without_update;
        long long curr_sum_with_l_update = max_sum_with_l_update;
        long long curr_sum_with_r_update = max_sum_with_r_update;

        // Case 1: keep arr[i] unchanged. Compare it with the value chosen at i - 1;
        // the pair is weighted by the original value arr[i - 1].
        max_sum_without_update = std::max(
            curr_sum_without_update + std::abs(arr[i]-arr[i-1])*arr[i-1],
            std::max(
                curr_sum_with_l_update + std::abs(arr[i]-l)*arr[i-1],
                curr_sum_with_r_update + std::abs(arr[i]-r)*arr[i-1]
            )
        );

        // Case 2: replace arr[i] with L and transition from each previous-value state.
        max_sum_with_l_update = std::max(
            curr_sum_without_update + std::abs(l-arr[i-1])*arr[i-1],
            std::max(
                curr_sum_with_l_update,
                curr_sum_with_r_update + std::abs(l-r)*arr[i-1]
            )
        );

        // Case 3: replace arr[i] with R and transition from each previous-value state.
        max_sum_with_r_update = std::max(
            curr_sum_without_update + std::abs(r-arr[i-1])*arr[i-1],
            std::max(
                curr_sum_with_l_update + std::abs(r-l)*arr[i-1],
                curr_sum_with_r_update
            )
        );
    }

    return std::max(
        max_sum_without_update,
        std::max(
            max_sum_with_l_update,
            max_sum_with_r_update
        )
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

    int l, r;
    std::cout << "\nEnter the lower and upper bounds respectively : ";
    std::cin >> l >> r;

    const long long answer = solve(arr, l, r);
    std::cout << "\nThe maximum possible score would be : " << answer <<  "\n\n";

    return 0;
}
