/*
    Given an array of positive integers `scores` and an integer k.
    return the total number of subarrays where the product of the elements is strictly less than K.

    1 <= N <= 10^5
    1 <= scores[i] <= 100
    1 <= k <= 10^9
*/

#include <iostream>
#include <vector>

size_t solve(const std::vector<int>& array, const size_t k) {
    const size_t size = array.size();

    size_t left = 0;
    size_t right = 0;
    size_t counter = 0;
    size_t curr_prod = 1;

    while (right < size) {
        curr_prod *= array[right];

        // shrink the window as long as product touches the limit
        while (curr_prod >= k and left <= right)
            curr_prod /= array[left++];

        counter += right - left + 1;
        right++;
    }

    return counter;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "\nKeep entering the elements : ";
    for (size_t i=0; i<size; i++)
        std::cin >> array[i];

    size_t k;
    std::cout  << "\nEnter the limit : ";
    std::cin >> k;

    size_t answer = solve(array, k);
    std::cout << "\nThere are " << answer << " such subarrays \n\n";

    return 0;
}