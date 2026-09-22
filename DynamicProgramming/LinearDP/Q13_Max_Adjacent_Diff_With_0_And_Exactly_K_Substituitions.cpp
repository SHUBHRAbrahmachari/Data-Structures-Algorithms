/*
    Given an array of integers.
    You can substitute any element with 0.

    You can substitute exactly K elements, neither more nor less.

    What is the maximum possible sum of absolute differences of adjacent
    elements after exactly K substitutions?

    1 <= K <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& arr, const int k) {
    const size_t size = arr.size();

    if (size == 1 and k == 1)
        return 0;

    /*
        DP state definition:

        memory_without_sub[i][t]:
            Maximum adjacent-difference sum for arr[0..i], after exactly t
            substitutions, where arr[i] remains unchanged.

        memory_with_sub[i][t]:
            Maximum adjacent-difference sum for arr[0..i], after exactly t
            substitutions, where arr[i] has been replaced by zero.

        MIN means that the state is unreachable. Since this is an EXACTLY-K
        problem, an unreachable state must never be used in a transition.
    */
    std::vector<std::vector<long long>> memory_without_sub(
        size,
        std::vector<long long>(k+1, MIN)
    );

    std::vector<std::vector<long long>> memory_with_sub(
        size,
        std::vector<long long>(k+1, MIN)
    );

        /*
                Base cases for the first element:

                - With zero substitutions, arr[0] remains unchanged and contributes no
                    adjacent difference yet, so memory_without_sub[0][0] = 0.
                - With one substitution, arr[0] becomes zero and also contributes no
                    adjacent difference yet, so memory_with_sub[0][1] = 0.
                - memory_with_sub[0][0] is kept as a neutral zero state for the
                    implementation's transition representation. No adjacent edge exists
                    at index 0, so its value is zero.
                - Every other state remains MIN because its exact substitution count is
                    impossible for a one-element prefix.
        */
    memory_without_sub[0][0] = 0;
    memory_with_sub[0][0] = memory_with_sub[0][1] = 0;

        // Add the edge between arr[i-1] and arr[i] while processing arr[i].
    for (int i=1; i<size; i++) {
        for (int t=k; t>=0; t--) {
            if (t > 0) {
                /*
                    Case 1: leave arr[i] unchanged.

                    If arr[i-1] was substituted, its value is zero, so the new
                    edge contributes |arr[i]|. Otherwise, the edge contributes
                    |arr[i] - arr[i-1]|. The substitution count stays t.
                */
                long long prev_res_without_sub = memory_without_sub[i-1][t];
                long long prev_res_with_sub = memory_with_sub[i-1][t];

                if (prev_res_with_sub != MIN and prev_res_without_sub == MIN)
                    memory_without_sub[i][t] = prev_res_with_sub + std::abs(arr[i]);

                else if (prev_res_with_sub == MIN and prev_res_without_sub != MIN)
                    memory_without_sub[i][t] = prev_res_without_sub + std::abs(arr[i]-arr[i-1]);
                
                else if (prev_res_with_sub != MIN and prev_res_without_sub != MIN)
                    memory_without_sub[i][t] = std::max(
                        prev_res_with_sub + std::abs(arr[i]),
                        prev_res_without_sub + std::abs(arr[i]-arr[i-1])
                    );


                /*
                    Case 2: substitute arr[i] with zero.

                    This is the t-th substitution, so predecessors must use
                    exactly t-1 substitutions. If arr[i-1] was also substituted,
                    the new edge is |0-0| = 0. Otherwise, it is |arr[i-1]|.
                */

                prev_res_without_sub = memory_without_sub[i-1][t-1];
                prev_res_with_sub = memory_with_sub[i-1][t-1];

                if (prev_res_with_sub != MIN and prev_res_without_sub == MIN)
                    memory_with_sub[i][t] = prev_res_with_sub;

                else if (prev_res_with_sub == MIN and prev_res_without_sub != MIN)
                    memory_with_sub[i][t] = prev_res_without_sub + std::abs(arr[i-1]);
                
                else if (prev_res_with_sub != MIN and prev_res_without_sub != MIN)
                    memory_with_sub[i][t] = std::max(
                        prev_res_with_sub,
                        prev_res_without_sub + std::abs(arr[i-1])
                    );
            }

            // With zero substitutions, both elements remain unchanged. The
            // substituted state is not a real zero-substitution state, but is
            // carried here as the implementation's neutral state.
            else {
                long long res = std::max(
                    memory_without_sub[i-1][0],
                    memory_with_sub[i-1][0]
                );

                if (res != MIN)
                    memory_with_sub[i][0] = memory_without_sub[i][0] = res + std::abs(arr[i]-arr[i-1]);
            }
            
        }
    }

    // Both final states must represent exactly k substitutions.
    return std::max(
        memory_without_sub[size-1][k],
        memory_with_sub[size-1][k]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the exact number of alterations to make : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum possible sum would be : " << answer << "\n\n";

    return 0;
}

