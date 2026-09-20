/*
    Given an arrayy of integers.
    You can alter any elements of this array by 1.
    Buy, tow consecutive elements cannot be flipped.

    i.e. if you decide to flip at index 2, you cannot flip at index 3.

    find out the minimum sum of absolute differences between adjacent elements after any number of flips.

    1 <= N <= 10^5
    -10^5 <= A[i] <= 10^5 
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& arr) {
    const size_t size = arr.size();

    if (size == 1)
        return 0;

    std::vector<long long> memory_with_alteration(size, 0);
    std::vector<long long> memory_without_alteration(size, 0);

    for (size_t i=1; i<size; i++) {
        // if we decide not to alter this element, we can consider altering or not altering previous element
        memory_without_alteration[i] = std::min(
            memory_with_alteration[i-1] + std::abs(arr[i]-1),
            memory_without_alteration[i-1] + std::abs(arr[i]-arr[i-1])
        );

        // if we're altering this element, we cannot consider altering the previous element
        memory_with_alteration[i] = memory_without_alteration[i-1] + std::abs(1-arr[i-1]);
    }

    return std::min(
        memory_without_alteration[size-1],
        memory_with_alteration[size-1]
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of elements in the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements in the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe minimum sum would be : " << answer << "\n\n";
    
    return 0;
}