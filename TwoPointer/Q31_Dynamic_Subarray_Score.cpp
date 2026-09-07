/*
    Given a binary array `nums`.
    You need to return the length of longest consecutive subarray where you are 
    allowed to delete atmost 1 zero from the subarray

    1 <= N <= 10^6
*/

#include <iostream>
#include <vector>

int solve(const std::vector<int>& nums) {
    const int size = nums.size();

    int last_zero_index = -1;
    int left = 0;
    int right = 0;
    int max_length = 0;

    while (right < size) {
        // we found a zero
        if (nums[right] == 0) {
            if (last_zero_index == -1)
                last_zero_index = right;

            else {
                left = last_zero_index + 1;
                last_zero_index = right;
            }
        }

        max_length = std::max(
            max_length,
            last_zero_index == -1? (right - left + 1) : (right - left)
        );

        right++;
    }

    return max_length;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> nums(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> nums[i];

    const int answer = solve(nums);
    std::cout << "\nThe maximum possible such contiguous length will be : " << answer << std::endl;

    return 0;
}