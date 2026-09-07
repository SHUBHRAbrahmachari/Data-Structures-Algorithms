/*
    You are given an array of positive intgers.
    At any point, you can either pick the leftmost element or the rightmost element from the array and subtract it from K
    Then delete that element from the array permananently.

    You need to find minimum number of steps to reduce K to exactly 0.
    If not possible return -1

    1 <= N <= 10^6
    1 <= nums[i] <= 10^4
    1 <= K <= 10^9
*/

#include <iostream>
#include <vector>

/*
    If corner elements are making up target,
    middle elements must be making up total_sum - target
    We need to find the maximum subarray with sum total_sum - target,
    let'n not use prefix sum this time, use two-pointer
*/
int solve(const std::vector<int>& nums, int target) {
    const int size = nums.size();

    int sum = 0;
    for (int ele : nums)
        sum += ele;

    // we got our new target
    target = sum - target;


    int left = 0;
    int right = 0;
    int curr_sum = 0;

    int max_length = -1;

    while (right < size) {
        // add this to curr_sum
        curr_sum += nums[right];

        // shrink the window while curr_sum > target
        while (left <= right and curr_sum > target)
            curr_sum -= nums[left++];

        if (curr_sum == target)
            max_length = std::max(
                max_length,
                right - left + 1
            );

        right++;
    }

    return max_length == -1? max_length : (size - max_length);
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> nums(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> nums[i];

    int k;
    std::cout << "\nEnter the target : ";
    std::cin >> k;

    const int answer = solve(nums, k);
    std::cout << "\nWe need atleast " << answer << " operations!\n\n";

    return 0;
}