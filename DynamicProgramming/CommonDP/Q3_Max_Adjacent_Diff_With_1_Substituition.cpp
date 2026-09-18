/*
    Problem:
    For every element, either keep its original value or replace it with 1.
    After making any combination of replacements, maximize the sum of absolute
    differences between adjacent elements:

        |arr[1] - arr[0]| + |arr[2] - arr[1]| + ...

    Example:
        arr = [3, 2, 1, 4, 5]
        Replace it with [3, 1, 1, 4, 1].
        The score is |1-3| + |1-1| + |4-1| + |1-4| = 8.

    Constraints:
        1 <= N <= 10^5
        1 <= arr[i] <= 10^5
*/

/*
    Dynamic-programming idea:
    Process the array from left to right. When deciding the final value at
    index i, the only new adjacent pair is (i - 1, i), so the state only needs
    to remember how index i - 1 was finalized.

    memory_with_altering[i] is the best score through index i when arr[i] is
    replaced by 1.

    memory_without_altering[i] is the best score through index i when arr[i]
    keeps its original value.

    If arr[i] becomes 1, the previous element was either also replaced (adding
    |1 - 1|) or kept (adding |1 - arr[i - 1]|).

    If arr[i] stays unchanged, the previous element was either replaced (adding
    |arr[i] - 1|) or kept (adding |arr[i] - arr[i - 1]|).

    Index 0 has no adjacent pair yet, so both states start at 0. The answer is
    the larger of the two states at the last index. Each state uses long long
    because the total score can exceed the range of int for the maximum input.

    Time complexity: O(N)
    Space complexity: O(N)
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& arr) {
    const size_t size = arr.size();

    if (size <= 1)
        return 0;

    // Best score through the current index when this element is changed to 1.
    std::vector<long long> memory_with_altering(size);

    // Best score through the current index when this element keeps its value.
    std::vector<long long> memory_without_altering(size);

    // A single element contributes no difference because there is no left neighbor.
    memory_with_altering[0] = 0;
    memory_without_altering[0] = 0;

    for (size_t i=1; i<size; i++) {
        // Case 1: replace arr[i] with 1 and account for the pair ending at i.
        memory_with_altering[i] = std::max(
            memory_with_altering[i-1],
            memory_without_altering[i-1] + std::abs(1-arr[i-1])
        );

        // Case 2: keep arr[i] unchanged and account for the pair ending at i.
        memory_without_altering[i] = std::max(
            memory_with_altering[i-1] + std::abs(arr[i]-1),
            memory_without_altering[i-1] + std::abs(arr[i]-arr[i-1])
        );
    }

    return std::max(
        memory_with_altering[size-1],
        memory_without_altering[size-1]
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum possible answer would be : " << answer << "\n\n";

    return 0;
}
