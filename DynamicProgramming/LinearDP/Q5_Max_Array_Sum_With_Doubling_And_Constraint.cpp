/*
    Problem:
    For each element, we may either:
      - keep it unchanged, or
      - double its value

    But we cannot double two consecutive elements.

    We need the maximum possible sum of the final transformed array.

    Constraints:
        1 <= N <= 10^5
        -10^9 <= A[i] <= 10^9

    Idea:
    At each index i, we only need to know the best result if the previous element
    was doubled or not. This is a standard linear DP because the choice at i
    depends only on the previous decision.
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& arr) {
    const size_t size = arr.size();
    /*
        DP state:
        max_sum_without_doubling = best sum up to current index when the previous element was not doubled
        max_sum_with_doubling = best sum up to current index when the previous element was doubled

        We keep only the previous values, which is enough because the current decision depends
        only on whether the previous element was doubled.
    */

    long long max_sum_without_doubling = arr[0];
    long long max_sum_with_doubling = 2*arr[0];

    for (size_t i=1; i<size; i++) {
        long long curr_max_sum_without_doubling = max_sum_without_doubling;
        long long curr_max_sum_with_doubling = max_sum_with_doubling;

        // If current element is not doubled, then the previous element may have been either:
        // - not doubled, or
        // - doubled
        // We take the better of those two options and add arr[i].
        max_sum_without_doubling = std::max(curr_max_sum_without_doubling, curr_max_sum_with_doubling) + arr[i];

        // If current element is doubled, then the previous element must have been kept unchanged.
        // So we take the best "not doubled" state from the previous step and add 2 * arr[i].
        max_sum_with_doubling = curr_max_sum_without_doubling + 2*arr[i];
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

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum possible array sum would be : " << answer << "\n\n";

    return 0;
}