/*
    Given a binary circular data where 1 represents a high-priority task and 0 represents a normal task;
    Determine the minimum number of adjacent swaps to group all 1's present in a single contiguous block.
    Since array is circular 1's accumulated on both ends can also be considered grouped

    1 <= N <= 10^5
*/

/*
    It looks dangerous but it is not, We have already done the linear part.
    
    Step 1> first calculate how many original 1's we have, let K
    Step 2> append the array to itself, extended_belt
    Step 3> find Q array on extended belt.

    Now on this Q array run a K sized window and find out number of swaps required, return the minimum swap requirement window value
*/

#include <iostream>
#include <vector>

int count_swaps(const std::vector<int>& array, const size_t left, const size_t right, const int median) {
    int swaps = 0;
    for (size_t i=left; i<=right; i++)
        swaps += std::abs(median - array[i]);

    return swaps;
}

int count_minimum_adjacent_swaps(const std::vector<int>& belt) {
    const size_t size = belt.size();

    // see how many one's do we have?
    int counter = 0;
    for (int ele : belt)
        if (ele == 1)
            counter++;

    if (counter < 2 or counter == size)
        return 0;

    // doubled up the belt
    std::vector<int> extended_belt = belt;
    for (int ele : belt)
        extended_belt.emplace_back(ele);

    const size_t new_size = 2*size;

    // getting the positions array
    std::vector<int> positions;
    for (int i=0; i<new_size; i++)
        if (extended_belt[i] == 1)
            positions.emplace_back(i);

    // getting the q array
    std::vector<int> q;
    int rank = 0;
    for (int ele : positions)
        q.emplace_back(ele - rank++);

    // now, over that q array we run a window of length `counter` and do the same we did in linear part
    int left = 0;
    int right = counter - 1;
    int min_swaps = INT_MAX;

    if (counter % 2 == 1) {
        while (right < q.size()) {
            size_t median_index = (left+right)/2;
            int median = q[median_index];

            min_swaps = std::min(
                min_swaps,
                count_swaps(q, left, right, median)
            );

            left++;
            right++;
        }
    }

    else {
        while (right < q.size()) {
            size_t median_index_1 = (left+right)/2;
            size_t median_index_2 = median_index_1+1;

            int median1 = q[median_index_1];
            int median2 = q[median_index_2];

            min_swaps = std::min(
                min_swaps,
                std::min(
                    count_swaps(q, left, right, median1),
                    count_swaps(q, left, right, median2)
                )
            );

            left++;
            right++;
        }
    }

    return min_swaps;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size : ";
    std::cin >> size;

    std::vector<int> belt(size);
    std::cout << "\nKeep entering the elements on the belt : ";
    for (size_t i=0; i<size; i++)
        std::cin >> belt[i];

    const int answer = count_minimum_adjacent_swaps(belt);
    std::cout << "\nMinimum " << answer << " swap(s) are required" << "\n\n";

    return 0;
}