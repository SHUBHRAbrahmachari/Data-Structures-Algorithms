/*
    Problem:
    You are given an array of integers. You may flip the sign of at most K elements.
    Find the maximum possible total sum of the array after these sign changes.

    Constraints:
        1 <= K <= N <= 10^5
        -10^5 <= A[i] <= 10^5

    Idea:
    At each index, we have a choice:
    - keep the current value as it is
    - flip its sign, if we still have some flips left

    This becomes a DP over:
        index: which position we are currently processing
        remaining flips: how many sign flips are still allowed

    The value for a state is the maximum sum achievable from this point onward.
*/

#include <iostream>
#include <vector>

long long solve_memoization(const std::vector<int>& arr, const int k, std::vector<std::vector<long long>>& memory, const size_t index = 0) {
    // We have processed the whole array, so no more contribution remains.
    if (index >= arr.size())
        return 0;

    // If this state was already computed, reuse it instead of recursing again.
    if (memory[index][k] != -1)
        return memory[index][k];

    // If no flips are left, we must keep the current element unchanged.
    if (k == 0)
        return memory[index][0] = arr[index] + solve_memoization(arr, 0, memory, index + 1);

    /*
        Option 1: flip the sign of arr[index]
        This gives -arr[index], and we spend one remaining flip.
    */
    long long option1 = -arr[index] + solve_memoization(arr, k - 1, memory, index + 1);

    /*
        Option 2: keep the sign unchanged
        This gives +arr[index], and we do not consume a flip.
    */
    long long option2 = arr[index] + solve_memoization(arr, k, memory, index + 1);

    // Choose the better of the two possibilities for this state.
    return memory[index][k] = std::max(option1, option2);
}

long long solve(const std::vector<int>& arr, const int k) {
    const size_t size = arr.size();

    /*
        DP state:
        memory[i][j] = maximum sum achievable from index i to the end,
                       given that exactly j sign flips are still available.

        We use memoization so each state is computed only once.
    */
    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(k + 1, -1)
    );

    return solve_memoization(arr, k, memory);
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of elements in the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements one by one : ";
    for (size_t i = 0; i < size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum sign toggles possible : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum sum would be : " << answer << "\n\n";
    
    return 0;
}

