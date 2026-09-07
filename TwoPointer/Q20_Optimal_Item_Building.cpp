/*
    Given an array of integers `items` of even length.
    pair up all elements n/2 distinct pairs such that each element belongs to exactly one pair.
    Return the minimum possible value of the maximum pair sum

    2 <= N <= 10^5, where n is even
    1 <= item[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> nums(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> nums[i];

    /*
        basically we are asked to pair the elements.

        pretty simple, sort the array and pair left and right sequentially
    */

    std::sort(nums.begin(), nums.end());

    int left = 0, right = size-1;
    int max_num = INT_MIN;

    while (left < right) {
        max_num = std::max(
            max_num,
            nums[left++] + nums[right--]
        );
    }

    std::cout << "\nThe minimum of those maximum pair sums would be " << max_num << std::endl;

    return 0;
}