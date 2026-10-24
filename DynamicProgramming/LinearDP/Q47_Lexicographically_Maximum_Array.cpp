/*
    Given an array arr[].
    We are allowed to swap two adjacent elements arr[i] and arr[i+1] only if their sum is even.
    Find the lexicographically largest array that can be obtained by performing the swapping operation
    any number of times, including zero times.

    An array X is lexicographically larger that another array Y if at the first place they differ,
    X has a larger element.

    Example:
        input: [1 3 5]
        output: [5 3 1]

        input: [1 3 4 2]
        output: [3 1 4 2]

    1 <= arr.size() <= 10^5
    0 <= arr[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

/*
    Simple sort works but that would take O(N^2).
    Which can result in TLE. So we must go with further optimized approach.

    We can do it in O(NlogN).
    Let's see how we can do it!

    Observation 1>

        Only adjacent elements having similar parity can swap places.
        ODD + ODD = allowed
        EVEN + EVEN = allowed
        ODD + EVEN = not allowed

    Observation 2>

        Because an odd number and an even number can never swap places:

            > no odd number can move past an even number
            > no even number can move past an odd number

        An element of opposite parity acts as a wall.

    Observation 3>

        Because opposite parities cannot cross each other, the array naturally breaks down
        into contiguous subsegments where all elements in a block share the same parity.

        Within every subsegment any pair of adjacent elements can be swapped freely. This is what we can do in O(NlogN)
*/

void solve(std::vector<int>& arr) {
    const int size = arr.size();

    if (size == 1)
        return;

    int start = 0;
    int end = 1;
    bool parity = arr[start] % 2;

    while (end < size) {
        if (arr[end] % 2 != parity) {
            // sort the subsegment
            std::sort(arr.begin()+start, arr.begin()+end, std::greater<int>());

            // change the subsegment
            start = end;
            parity = not parity;
        }

        end++;
    }

    // sort the final subsegment
    std::sort(arr.begin()+start, arr.begin()+end, std::greater<int>());
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    solve(arr);
    std::cout << "\n";
    for (const int& ele : arr)
        std::cout << ele << " ";
    std::cout << "\n";

    return 0;
}