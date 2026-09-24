/*
    Given an array of integers.
    We need to find out a subsequence such that there are atmost K such elements taht are consecutive.

    Find the maximum subsequence sum.

    1 <= N <= 10^5
    2 <= K <= N
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

// O(NK)
long long solve(
    const std::vector<int>& arr,
    const int k,
    std::vector<std::vector<std::vector<long long>>>& memory,
    const int curr_k=0,
    int empty=1,
    const int index=0
) {
    if (index >= arr.size())
        return empty == 1? MIN : 0;

    if (memory[index][curr_k][empty] != MIN)
        return memory[index][curr_k][empty];

    // case 1: if curr_k=k, no more consecutive elements can be picked. Although after skipping it again atmost K consecutive elements can be picked
    if (curr_k == k)
        return memory[index][curr_k][empty] = solve(arr, k, memory, 0, empty, index+1);

    // means we can collect consecutive elements further
    // option 1> we skip this element, so again we can pick atmost k consecutive elements
    long long option1 = solve(arr, k, memory, 0, empty, index+1);

    // option 2> we take this element, we can pick currk-1 consecutive elements further only
    long long option2 = arr[index] + solve(arr, k, memory, curr_k+1, 0, index+1);

    return memory[index][curr_k][empty] = std::max(
        option1,
        option2
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
    std::cout << "\nEnter the maximum number of consecutive elments : ";
    std::cin >> k;

    std::vector<std::vector<std::vector<long long>>> memory(
        size,
        std::vector<std::vector<long long>>(
            k+1,
            std::vector<long long>(2, MIN)
        )
    );

    const long long answer = solve(arr, k, memory);
    std::cout << "\nThe maximum possible sum would be : " << answer<< "\n\n";

    return 0;
}