/*
    Given an array of integers.
    We need to find the maximum subsequence sum such that between any two picked elements, there must be atleast D distance between them i.e j-i >= D

    1 <= D <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()

long long solve(const std::vector<int>& arr, const int d) {
    const int size = arr.size();

    if (size == 1)
        return arr[0];

    /*
        memory_with_cons[i]: best non-empty subsequence sum up to i that picks arr[i].
        memory_without_cons[i]: best non-empty subsequence sum up to i that skips arr[i].

        Both states keep non-empty subsequences so that an all-negative input
        returns its largest element instead of incorrectly returning zero.
    */
    std::vector<long long> memory_with_cons(size, MIN);
    std::vector<long long> memory_without_cons(size, MIN);

    // The only non-empty subsequence ending at index 0 contains arr[0].
    memory_with_cons[0] = arr[0];

    for (int i=1; i<size; i++) {
        /*
            If arr[i] is picked after arr[j], then i - j >= d, so j <= i-d.
            Therefore, the best compatible predecessor is represented by the
            best state at index i-d.
        */

        // Skipping arr[i] preserves the best result found through index i-1.
        memory_without_cons[i] = std::max(
            memory_with_cons[i-1],
            memory_without_cons[i-1]
        );

        // No earlier element can be paired with arr[i] when i < d.
        if (i < d)
            memory_with_cons[i] = arr[i];

        else
            memory_with_cons[i]  = std::max(
                0LL,    // Start a new subsequence at arr[i] if every predecessor is worse.
                std::max(
                    memory_with_cons[i-d],
                    memory_without_cons[i-d]
                )
            ) + arr[i];
    }

    return std::max(
        memory_with_cons[size-1],
        memory_without_cons[size-1]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int d;
    std::cout << "\nEnter the minimum difference between consecutive positions : ";
    std::cin >> d;

    const long long answer = solve(arr, d);
    std::cout << "\nThe maximum subsequence sum would be : " << answer << "\n\n";

    return 0;
}