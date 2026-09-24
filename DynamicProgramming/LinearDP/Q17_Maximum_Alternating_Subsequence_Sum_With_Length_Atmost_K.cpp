/*
    Given an array of integers.
    You can either add (+) or (-) sign in front of the element and transform it accordingly.
    You are tasked to find out the maximum possible subsequence sum such that no two consecutive elements have been assigned same sign to them.
    The length of the subsequence has to be at most K.

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
            -arr[0], arr[0]
        );

    /*
        Each state is indexed by t, the maximum allowed subsequence length.
        Therefore every state represents a non-empty subsequence of length at most t.

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

        The four states are maintained for every allowed length t. The excluding
        states preserve solutions that skip elements, while the including states
        enforce alternating signs.
    */
    std::vector<long long> memory_excluding_neg(k+1, MIN);
    std::vector<long long> memory_excluding_pos(k+1, MIN);
    std::vector<long long> memory_including_neg(k+1, MIN);
    std::vector<long long> memory_including_pos(k+1, MIN);

    // A one-element subsequence can use either sign and is valid for every t >= 1.
    for (int t=k; t>=1; t--) {
        memory_including_neg[t] = -arr[0];
        memory_including_pos[t] = arr[0];
    }

    for (int i=1; i<size; i++) {
        // Iterate downward so that t-1 still refers to the previous index.
        for (int t=k; t>=1; t--) {

            // Skipping arr[i] keeps the best state already accumulated.
            memory_excluding_neg[t] = std::max(
                memory_excluding_neg[t],
                memory_including_neg[t]
            );

            memory_excluding_pos[t] = std::max(
                memory_excluding_pos[t],
                memory_including_pos[t]
            );

            // A negative sign must follow a positive sign. Zero starts a new subsequence.
            memory_including_neg[t] = std::max(
                (long long)0,
                std::max(
                    memory_including_pos[t-1],
                    memory_excluding_pos[t-1]
                )
            ) - arr[i];

            // A positive sign must follow a negative sign. Zero starts a new subsequence.
            memory_including_pos[t] = std::max(
                (long long)0,
                std::max(
                    memory_excluding_neg[t-1],
                    memory_including_neg[t-1]
                )
            ) + arr[i];
        }
    }

    // The answer may end with either sign and may have any length up to k.
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
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum size of the subsequence : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum possible subsequence sum would be : " << answer << "\n\n";

    return 0;
}