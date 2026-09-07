/*
    Given an array of integers which might contain negative numbers as well.
    Return the shortest length of a non-empty contiguous sub-array whose sum is atleast k.

    1 <= N <= 10^5
    -10^5 <= nums[i] <= 10^5
    1 <= K <= 10^9
*/

/*
    Our older Segment Tree idea with coordinate compression works,
    but since here we need the MINIMUM LENGTH and not exactly count of those subarrays, we can do it in shorter time.

    Using a montonic deque we can do it in O(N) time.
*/

#include <iostream>
#include <vector>
#include <deque>

int solve(const std::vector<int>& arr, const int target) {
    /*
        For any prefix sum P[i], we want the closest last occurrence of prefix sum P[j]
        such that P[i] - p[j] >= target, where j < i.
        Segment Tree would have worked, but it it wouls've also take NlogN time.

        Since we need only the MINIMUM such length, a montonic deque can be specialized for O(N) TC

        when we see P[i] - P[dq.front()] >= target: we can safely drop the front()

        why?
            `because even if this is valid for any other future i, 
            that won't be the answer since we need minimum only`

        When we see P[i] < p[dq.back()]: pop back with confidence

        1> for future indices, i will be closer
        2> for future indices, since P[i] < P[dq.back()], there would be a greater chance that our condition is satisfied
    */

    const int size = arr.size();

    std::vector<long long> prefix_sums(size + 1, 0);
    for (int i = 0; i < size; i++) {
        prefix_sums[i + 1] = prefix_sums[i] + arr[i];
    }

    std::deque<int> dq;
    int min_length = INT_MAX;

    for (int i = 0; i <= size; i++) {
        while (!dq.empty() && prefix_sums[i] - prefix_sums[dq.front()] >= target) {
            min_length = std::min(min_length, i - dq.front());
            dq.pop_front();
        }

        // first of all i is closer for future indices and also there would be a greater chance that our condition P[i] - P[j] >= target is satfied, isn't it?
        while (!dq.empty() && prefix_sums[i] <= prefix_sums[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    return (min_length == INT_MAX) ? -1 : min_length;
}


int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> nums(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> nums[i];

    int target;
    std::cout << "\nEnter the target : ";
    std::cin >> target;

    const int answer = solve(nums, target);
    std::cout << "\nThe minimum length of such subarray would be : " << answer << "\n\n";

    return 0;
}