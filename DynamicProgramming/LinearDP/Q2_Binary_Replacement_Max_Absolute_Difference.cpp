/*
    Problem:
    Given an array of integers, you may replace any element with 0.
    We need to maximize the sum of absolute differences between adjacent elements.

    Formally, for array A:
        max over all choices of replacing some A[i] with 0
        sum of |A[i] - A[i-1]| for i = 1..N-1

    Constraints:
        1 <= N <= 10^5
        -10^9 <= A[i] <= 10^9

    Idea:
    For each index i, we decide whether the current element is kept as it is
    or replaced by 0. The DP keeps the best possible value up to index i in
    both cases.

    This is a classic linear DP because the answer for index i depends only on
    the previous index i-1, not on all earlier choices.
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& arr) {
    const size_t size = arr.size();

    if (size == 1)
        return 0;

    /*
        DP definition:

        memory_with_alteration[i] = best total contribution for pairs up to index i,
                                    assuming arr[i] is replaced by 0.

        memory_without_alteration[i] = best total contribution for pairs up to index i,
                                      assuming arr[i] is kept unchanged.

        At each step, we only need the previous states at i-1, so the transition is O(1)
        per index and the whole solution runs in O(N).
    */
    std::vector<long long> memory_with_alteration(size, 0);
    std::vector<long long> memory_without_alteration(size, 0);

    // Start from index 1 because the first pair is (0, 1).
    for (size_t i = 1; i < size; i++) {
        /*
            If arr[i] is changed to 0, then the contribution for pair (i-1, i) is:
            - 0, if arr[i-1] was also changed to 0
            - |arr[i-1]|, if arr[i-1] was kept unchanged
        */
        memory_with_alteration[i] = std::max(
            memory_with_alteration[i - 1],
            memory_without_alteration[i - 1] + std::abs(arr[i - 1])
        );

        /*
            If arr[i] is kept unchanged, then the contribution for pair (i-1, i) is:
            - |arr[i]|, if arr[i-1] was changed to 0
            - |arr[i] - arr[i-1]|, if arr[i-1] was kept unchanged
        */
        memory_without_alteration[i] = std::max(
            memory_with_alteration[i - 1] + std::abs(arr[i]),
            memory_without_alteration[i - 1] + std::abs(arr[i] - arr[i - 1])
        );
    }

    return std::max(
        memory_with_alteration[size-1],
        memory_without_alteration[size-1]
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i = 0; i < size; i++)
        std::cin >> arr[i];

    const long long ans = solve(arr);
    std::cout << "\nThe maximum possible sum would be : " << ans << std::endl << std::endl;

    return 0;
}