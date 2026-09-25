/*
    Given two arrays with integers.

            w[]: weights at index i
            p[]: penalties of index i

    If you collect index i, you gain weight w[i]
    If you skip index i, you pay a penalty p[i]

    Maximize the weight!

    1 <= |w[]| = |p[]| <= 10^5
    -10^5 <= w[i], p[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& weights, const std::vector<int>& penalties) {
    const int size = weights.size();

    if (size == 1)
        return std::max(
            weights[0],
            penalties[0]
        );

    /*
        Let's define our DP states first:

            memory_without_cons: best collectable weight upto any index i without considering that element (skipping the element)
            memory_with_cons: best collectable weight upto any index i with considering that element (taking the element)
    */
    // if we're skipping index 0, we must pay a penalty of prenalties[0]
    long long memory_without_cons = -penalties[0];

    // if we are taking index 0 into account, we must collect the weight
    long long memory_with_cons = weights[0];

    for (int i=1; i<size; i++) {
        long long curr_without_cons = memory_without_cons;
        long long curr_with_cons = memory_with_cons;

        memory_without_cons = std::max(
            curr_with_cons,
            curr_without_cons
        ) - penalties[i];

        // we can't have zero as an option here since every past element has an effect
        memory_with_cons = std::max(
            curr_with_cons,
            curr_without_cons
        ) + weights[i];
    }

    return std::max(
        memory_with_cons,
        memory_without_cons
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the arrays : ";
    std::cin >> size;

    std::vector<int> weights(size), penalties(size);
    std::cout << "\nKeep entering the weights and penalties as a pair simultaneously : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> weights[i] >> penalties[i];

    const long long answer = solve(weights, penalties);
    std::cout << "\nThe maximum score would be : " << answer << "\n\n";

    return 0;
}
