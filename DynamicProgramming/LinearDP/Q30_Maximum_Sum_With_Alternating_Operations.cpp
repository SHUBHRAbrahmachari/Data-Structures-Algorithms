/*
    For every array element, choose either +arr[i] or -arr[i]. Choose exactly
    one sign per element, and never use the same sign more than k times in a
    row. Find the largest possible total.

    The DP tracks the best total ending with each sign. Its second index t
    tells how large a consecutive run of that sign is allowed to be. To extend
    a run to allowance t, the previous same-sign state must have allowance
    t-1; switching signs starts a new run.

    Constraints: 1 <= k <= N <= 10^5; -10^5 <= arr[i] <= 10^5.
*/

#include <iostream>
#include <vector>
#include <limits>

// Marks a DP state that cannot be reached. This is safely below any valid sum.
#define MIN std::numeric_limits<long long>::min()/2

// Return the largest signed sum while limiting each same-sign run to k items.
long long solve(const std::vector<int>& arr, const int k) {
    const int size = arr.size();

    // With one item, choose whichever sign gives the larger value.
    if (size == 1)
        return std::max(
            arr[0], -arr[0]
        );
    
    /*
        State meaning after processing arr[0..i]:
        - memory_neg[i][t]: best total ending with a minus, with a run limit t.
        - memory_pos[i][t]: best total ending with a plus, with a run limit t.

        For t >= 1, each state allows the current sign to have appeared up to t
        times in a row. The t = 0 cells are helper states: they hold the best
        total ending with the OPPOSITE sign, so the next element can switch
        signs and begin a run of length 1.

        MIN means that no valid way to reach a state has been found yet.
    */
    // Each table has one row per processed prefix and columns for allowances
    // 0 through k. Initially every state is unreachable.
    std::vector<std::vector<long long>> memory_neg(
        size,
        std::vector<long long>(k+1, MIN)
    );

    std::vector<std::vector<long long>> memory_pos(
        size,
        std::vector<long long>(k+1, MIN)
    );

    // Initialize the first element, which can only contribute +arr[0] or
    // -arr[0]. The zero-allowance cells are set to the opposite-sign helpers.
    for (int t=k; t>=0; t--) {
        if (t == 0) {
            memory_neg[0][t] = arr[0];
            memory_pos[0][t] = -arr[0];
        }

        else {
            memory_neg[0][t] = -arr[0];
            memory_pos[0][t] = arr[0];
        }
    }

    for (int i=1; i<size; i++) {
        // Prepare the helper cells for the previous prefix. They represent
        // switching from any valid run of the opposite sign (up to k items).
        memory_neg[i-1][0] = memory_pos[i-1][k];
        memory_pos[i-1][0] = memory_neg[i-1][k];

        for (int t=k; t>=1; t--) {
            /*
                Choose -arr[i]. There are two ways to arrive here:
                1. Continue a minus run: use the previous minus state with
                   allowance t-1, then subtract arr[i].
                2. Switch from plus to minus: use the previous plus state with
                   allowance k, then subtract arr[i]. The run limit resets
                   when the sign changes.
            */
            long long prev_neg_1 = memory_neg[i-1][t-1];
            long long prev_pos_1 = memory_pos[i-1][k];

            long long prev_best_1  = std::max(
                prev_neg_1, prev_pos_1
            );

            // Do not add to MIN: it represents an impossible predecessor.
            if (prev_best_1 != MIN)
                memory_neg[i][t] = prev_best_1 - arr[i];

            /*
                Choose +arr[i], symmetrically:
                1. Continue a plus run from allowance t-1.
                2. Switch from minus, whose run may have used allowance k.
            */

            long long prev_pos_2 = memory_pos[i-1][t-1];
            long long prev_neg_2 = memory_neg[i-1][k];

            long long prev_best_2 = std::max(
                prev_pos_2, prev_neg_2
            );

            // Skip unreachable predecessors; otherwise add the current value.
            if (prev_best_2 != MIN)
                memory_pos[i][t] = prev_best_2 + arr[i];
        }
    }

    // At the last element, either sign may give the optimal total. Allowance k
    // includes every valid run length, so these two states cover all solutions.
    return std::max(
        memory_neg[size-1][k],
        memory_pos[size-1][k]
    );
}

int main() {
    int size;
    std::cout << "\nKeep entering the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum consecutive same operation count : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum sum would be : " << answer << "\n\n";

    return 0;
}