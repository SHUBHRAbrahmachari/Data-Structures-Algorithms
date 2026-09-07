/*
    Given a binary circular data where 1 represents a high-priority task and 0 represents a normal task;
    Determine the minimum number of adjacent swaps to group all 1's present in a single contiguous block.

    1 <= N <= 10^5
*/

/*
    What is our task? we need to accumulate all the 1's into one cluster right?
    We  can accumulate anywhere in this array, from any starting index T right?

    suppose we have an array like this [1 0 0 1 1] => 1's are present at [0 3 4]
    We count total number of 1's we have and we assign ranks to them.
    We see we have in total 3 1's.

                First 1> rank 0
                Second 1> rank 1
                Third 1> rank 2

    Now what are we actually wanting to do?
    We find the transormed q array!

    q(i) = index(i) - rank(i) where i means i-th 1

    so, q(0) = 0 - 0 = 0
        q(1) = 3 - 2 = 1
        q(2) = 4 - 2 = 2

    so q array becomes [0 1 2]

    now you might be thinking what is the use? see we got the median 1

    minimum swaps required = |0-1| + |1-1| + |2-1| = 2

    In case you had 2 medians, check which one gives smaller results!
*/

#include <iostream>
#include <vector>

int count_swaps(const std::vector<int>& q, const int median) {
    int swaps = 0;
    for (int v : q)
        swaps += std::abs(v-median);

    return swaps;
}

int find_minimum_adjacent_swaps(const std::vector<int>& array) {
    const size_t size = array.size();

    std::vector<int> positions;

    for (size_t i=0; i<size; i++) {
        if (array[i] == 1)
            positions.emplace_back(i);
    }

    // less than 2 1's found or all are 1's
    if (positions.size() < 2 or positions.size() == size)
        return 0;

    std::vector<int> q;

    int rank = 0;
    for (size_t i=0; i<positions.size(); i++)
        q.emplace_back(positions[i] - rank++);

    // odd number
    if (q.size() % 2 == 1) {
        size_t median_index = q.size()/2;
        int median = q[median_index];

        return count_swaps(q, median);
    }

    size_t median_index_1 = q.size()/2;
    size_t median_index_2 = median_index_1 - 1;

    return std::min(
        count_swaps(q, q[median_index_1]),
        count_swaps(q, q[median_index_2])
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> belt(size);
    std::cout << "\nKeep entering the elements : ";
    for (int i=0; i<size; i++)
        std::cin >> belt[i];

    const int answer = find_minimum_adjacent_swaps(belt);
    std::cout << "\nMinimum " << answer << " swap(s) are required" << "\n\n";

    return 0;
}   