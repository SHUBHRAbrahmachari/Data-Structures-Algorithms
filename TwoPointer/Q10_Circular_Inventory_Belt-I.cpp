/*
    Given a binary circular data where 1 represents a high-priority task and 0 represents a normal task;
    Determine the minimum number of arbitary swaps to group all 1's present in a single contiguous block.
    Since array is circular 1's accumulated on both ends can also be considered grouped

    1 <= N <= 10^5
*/

/*
    Solution:
        To handle a circular array in sliding window problems use the `Array Concatenation Trick`

    By appending the array to iteself that wraps around the end becomes a standard linear window

    step 1> count total number of 1's in the array, let C (all must end up in this window only)
    step 2> append the array to itself
    step 3> run a sliding window to check minimum number of zeroes in the  window. That's the answer
*/
#include <iostream>
#include <vector>

int count_minimum_arbitary_swaps(const std::vector<int>& belt) {
    const size_t size = belt.size();

    std::vector<int> extended_belt = belt;
    int count = 0;

    // appending the array to itself and counting original number of 1's
    for (int ele : belt) {
        extended_belt.emplace_back(ele);

        if (ele == 1)
            count++;
    }

    int max_one_count = 0;
    int curr_one_count = 0;
    
    for (size_t i=0; i<count; i++) {
        if (extended_belt[i] == 1)
            curr_one_count++;
    }

    max_one_count = std::max(
        max_one_count,
        curr_one_count
    );

    int j = 0;
    for (int i=count; i<extended_belt.size(); i++) {
        if (extended_belt[j++] == 1)
            curr_one_count--;

        if (extended_belt[i] == 1)
            curr_one_count++;

        max_one_count = std::max(
            max_one_count,
            curr_one_count
        );
    }

    return count - max_one_count;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size : ";
    std::cin >> size;

    std::vector<int> belt(size);
    std::cout << "\nKeep entering the elements on the belt : ";
    for (size_t i=0; i<size; i++)
        std::cin >> belt[i];

    const int answer = count_minimum_arbitary_swaps(belt);
    std::cout << "\nMinimum " << answer << " swap(s) are required" << "\n\n";

    return 0;
}