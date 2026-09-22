/*
    Given an array of positive integers representing wealth in each house.
    You are planning to rob the houses. But there are two conditions.

        1> You cannot rob two consecutive houses otherwise you'll get caught.
        2> You can rob exactly K houses.


    What is the maximum wealth you can collect?

    1 <= N <= 10^5
    1 <= K <= (N+1)/2       // maximum number of non-consecutive houses
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

// A value smaller than any valid answer. It represents an unreachable state.
#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& houses, const int k) {
    const size_t size = houses.size();

    if (size == 1 and k == 1)
        return houses[0];

    /*
        This is an EXACTLY-K problem, so a DP state is valid only when its
        robbery count is actually achievable. We must never treat an
        unreachable state as a real state just because its value is zero.
            robberies, where house i is not robbed.

        The value MIN means that the corresponding exact-count state has not
        been computed or is impossible. It must not be used in arithmetic.
    */
    /*
        We have to tweak our DP state definition a bit now!
        Instead of using atmost t robbings, now we will make exactly t robbings.

        memory_with_robbing[i][t]: maximum possible collection upto index i and with exactly t robbings considering we have robbed house at index i.
        memory_without_robbing[i][t]: maximum possible collection upto index i and exactly t robbings considering we have not robbed house at index i
    */
    std::vector<std::vector<long long>> memory_with_robbing(
        size,
        std::vector<long long>(k+1, MIN)
    );

    std::vector<std::vector<long long>> memory_without_robbing(
        size,
        std::vector<long long>(k+1, MIN)
    );

    /*
        Initialization:

        1. Every state starts as MIN. For t > 0, this is important: before a
           valid transition proves that exactly t robberies are possible, the
           state must remain unreachable.

        2. The zero-robbery row is the neutral base case. For any prefix, using
           exactly zero robberies gives wealth zero. The [0] state in the
           "with" table is also initialized to zero as a neutral predecessor;
           no robbery has been made yet, so its label does not affect the
           resulting count. It is used when the first robbery is selected.

        3. At index 0, exactly one robbery is possible only by robbing house 0.
           Every other one-robbery state remains MIN until a valid transition
           computes it.
    */
    for (int i=0; i<size; i++) {
        memory_without_robbing[i][0] = 0;
        memory_with_robbing[i][0] = 0;
    }

    // Base case: rob house 0 as the first and only robbery in this prefix.
    memory_with_robbing[0][1] = houses[0];

    // Build every exact-count state from previously valid states.
    for (int i=1; i<size; i++) {
        for (int t=k; t>=1; t--) {
            /*
                Case 1: do not rob house i.

                The previous house may have been robbed or not, but the exact
                robbery count stays t. Taking max(MIN, valid value) is safe
                here because we do not add anything to the result. If both
                predecessors are MIN, this state remains MIN.
            */
            memory_without_robbing[i][t] = std::max(
                (i > 0 ? memory_without_robbing[i-1][t] : MIN),
                (i > 0 ? memory_with_robbing[i-1][t] : MIN)
            );

            /*
                                Case 2: rob house i as the t-th robbery.

                                The previous state must be valid before houses[i] is added:

                                    - If house i-1 was not robbed, use
                                        memory_without_robbing[i-1][t-1].
                                    - If house i-1 was robbed, it would be consecutive with i,
                                        so instead use memory_with_robbing[i-2][t-1].

                                Both candidates must represent exactly t-1 robberies. A MIN
                                candidate is impossible and must not participate in the max or
                                in the addition of houses[i].
            */
            long long res = std::max(
                (i > 0 and memory_without_robbing[i-1][t-1] != MIN ? memory_without_robbing[i-1][t-1] : MIN),
                (i > 1 and memory_with_robbing[i-2][t-1] != MIN ? memory_with_robbing[i-2][t-1] : MIN)
            );

                // Never create a reachable state from an unreachable predecessor.
            if (res != MIN)
                memory_with_robbing[i][t] = res + houses[i];
        }
    }

            // Both final states must contain exactly k robberies. No smaller count is
            // acceptable because this problem requires exactly K thefts.
    return std::max(
        memory_with_robbing[size-1][k],
        memory_without_robbing[size-1][k]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of houses : ";
    std::cin >> size;

    std::vector<int> houses(size);
    std::cout << "\nKeep entering the wealths of the houses : ";
    for (size_t i=0; i<size; i++)
        std::cin >> houses[i];

    int k;
    std::cout << "\nEnter the total number of houses to rob : ";
    std::cin >> k;

    const long long answer = solve(houses, k);
    std::cout << "\nThe maximum wealth we can collect would be : " << answer << "\n\n";

    return 0;
}