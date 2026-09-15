/*
    Given an two arrays of same size containing positive integers.
    v[]: represents the value of item at slot i.
    w[]: represents the weight of item  at slot i

    Also given a positive integer K, representing the maximum weight capacity of your knapsack.

    You need to pick items such that the total value in your knapsack is maximum for given knapsack capacity.

    1 <= |v[]| = |w[]| <= 10^4
    1 <= K <= 10^3
*/

#include <iostream>
#include <vector>

/*
    solve(values, weights, memory, rem, index)

    This function solves the 0/1 Knapsack problem using recursion + memoization.

    values[i] = value of item i
    weights[i] = weight of item i
    rem       = remaining capacity left in the knapsack
    index     = current item index being considered

    The function returns the maximum total value we can collect from items index..n-1
    while respecting the remaining capacity `rem`.
*/
int solve(const std::vector<int>& values, const std::vector<int>& weights, std::vector<std::vector<int>>& memory, const int rem, const size_t index=0) {
    // If we have processed all items, no more value can be added.
    if (index >= values.size())
        return 0;

    // If this state has already been computed, reuse the result.
    if (memory[index][rem] != -1)
        return memory[index][rem];

    // Case 1: The current item is too heavy to fit in the remaining capacity.
    // We must skip it and consider the next item.
    if (weights[index] > rem)
        return memory[index][rem] = solve(values, weights, memory, rem, index+1);

    // Case 2: The item fits.
    // Option 1 -> take this item, so remaining capacity decreases.
    // Option 2 -> leave this item and move to the next one.
    int option1 = values[index] + solve(values, weights, memory, rem-weights[index], index+1);
    int option2 = solve(values, weights, memory, rem, index+1);

    // Best answer for this state is the greater of taking or skipping the current item.
    return memory[index][rem] = std::max(option1, option2);
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of items : ";
    std::cin >> size;

    std::vector<int> values(size);
    std::vector<int> weights(size);

    std::cout << "\nKeep entering the value and weight pairs respectively : \n\n";
    for (size_t i = 0; i < size; i++)
        std::cin >> values[i] >> weights[i];

    int k;
    std::cout << "\nEnter the knapsack capacity : ";
    std::cin >> k;

    /*
        DP table definition:
        memory[i][rem] = maximum value obtainable from items starting at index i,
        when the remaining knapsack capacity is 'rem'.

        We initialize every cell with -1 to mark it as 'not computed yet'.
        This allows memoization to avoid re-solving the same subproblem.
    */
    std::vector<std::vector<int>> memory(
        size,
        std::vector<int>(k + 1, -1)
    );

    // Start from index 0 and full capacity k.
    const int answer = solve(values, weights, memory, k);
    std::cout << "\nThe maximum collectable value is : " << answer << "\n\n";

    return 0;
}