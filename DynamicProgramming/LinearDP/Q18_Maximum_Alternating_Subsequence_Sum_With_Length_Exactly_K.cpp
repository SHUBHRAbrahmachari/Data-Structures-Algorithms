/*
    Given an array of integers.
    You can either add (+) or (-) sign in front of the element and transform it accordingly.
    You are tasked to find out the maximum possible subsequence sum such that no two consecutive elements have been assigned same sign to them.
    The length of the subsequence has to be exactly K.

    1 <= K <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& arr, const int k) {
    const int size = arr.size();

    if (size == 1 and k == 1)
        return std::max(
            arr[0], -arr[0]
        );

    /*
        Each state is indexed by t, the exact subsequence length.
        Therefore a valid state at index t represents a non-empty subsequence
        containing exactly t selected elements. MIN marks an unreachable state.
        Unlike the at-most-K version, only states at length k are considered in
        the final answer.

        memory_excluding_neg[t]:
            best sum after skipping the current element when the last selected
            element has a negative sign.

        memory_excluding_pos[t]:
            best sum after skipping the current element when the last selected
            element has a positive sign.

        memory_including_neg[t]:
            best sum when the current element is selected with a negative sign.

        memory_including_pos[t]:
            best sum when the current element is selected with a positive sign.

        The four states are maintained for every length from 1 through k. The
        excluding states preserve exact-length solutions when an element is
        skipped, while the including states increase the length by one and
        enforce alternating signs.
    */
    std::vector<long long> memory_excluding_neg(k+1, MIN);
    std::vector<long long> memory_excluding_pos(k+1, MIN);
    std::vector<long long> memory_including_neg(k+1, MIN);
    std::vector<long long> memory_including_pos(k+1, MIN);

    // The first element starts the two possible exact-length-1 states.
    memory_including_neg[1] = -arr[0];

    // It can independently receive a positive sign.
    memory_including_pos[1] = arr[0];

    for (int i=1; i<size; i++) {
        // Descending t keeps the t-1 states from the previous index available.
        for (int t=k; t>=1; t--) {
            // Skipping arr[i] preserves the best exact-length state already found.
            memory_excluding_neg[t] = std::max(
                memory_excluding_neg[t],
                memory_including_neg[t]
            );

            memory_excluding_pos[t] = std::max(
                memory_excluding_pos[t],
                memory_including_pos[t]
            );

            // Every element may start a new one-element subsequence. There is no
            // exact-length-0 sign state from which length 1 could be derived.
            if (t == 1) {
                memory_including_neg[t] = -arr[i];
                memory_including_pos[t] = arr[i];
            }
            
            else {
                // A negative sign must follow a reachable positive-sign state
                // of exact length t-1.
                long long prev_best_pos = std::max(
                    memory_excluding_pos[t-1],
                    memory_including_pos[t-1]
                );

                if (prev_best_pos != MIN)
                    memory_including_neg[t] = prev_best_pos - arr[i];
                
                // A positive sign must follow a reachable negative-sign state
                // of exact length t-1.
                long long prev_best_neg = std::max(
                    memory_including_neg[t-1],
                    memory_excluding_neg[t-1]
                );

                if (prev_best_neg != MIN)
                    memory_including_pos[t] = prev_best_neg + arr[i];
                }
        }
    }

    // Both final signs are possible, but the requested length must be exactly k.
    return std::max(
        std::max(
            memory_excluding_neg[k],
            memory_excluding_pos[k]
        ),

        std::max(
            memory_including_neg[k],
            memory_including_pos[k]
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering th elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the exact length of the subsequence to have : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum sum would be : " << answer << "\n\n";

    return 0;
}