/*
    Given an array of positive integers.
    We are required to find the maximum sum of a non-empty subsequence such that
    for any two consecutive indices picked i, j where (i < j) the following condition must
    be preserved:

            j - i <= K

    1 <= K <= N <= 10^5
    -10^4 <= A[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <limits>
#include <deque>

#define MIN std::numeric_limits<int>::min()/2

// O(N^2)
int solve(const std::vector<int>& arr, std::vector<std::vector<int>>& memory, const int k, const int i=-1, const int j=0) {
    // if no elements were taken, we have to discard this answer. We cannot allow empty sequence
    if (j >= arr.size())
        return i == -1? MIN : 0;

    // pre-computed case
    if (memory[i+1][j] != -1)
        return memory[i+1][j];

    int option1 = MIN;
    int option2 = MIN;

    if (i == -1) {
        option1 = arr[j] + solve(arr, memory, k, j, j+1);
        option2 = solve(arr, memory, k, i, j+1);
    }

    else {
        if (j > i+k)
            return memory[i+1][j] = 0;

        else {
            option1 = arr[j] + solve(arr, memory, k, j, j+1);
            option2 = solve(arr, memory, k, i, j+1);
        }
    }

    return memory[i+1][j] = std::max(
        option1, option2
    );
}

// O(N) : monotonic deque approach, just because we have index level dependency
int solve_optimized(const std::vector<int>& arr, const int k) {
    /*
        Let memory[j] define the maximum sum of a non-empty subsequence strictly ending at index j

        memory[i] = arr[j] + max(0, max(memory[i] where i >= j-k))

        if the best previous window is negative, we start a new subsequence at j.

        we'll maintain a montonic deque whose front would always have the index in range : [j-k, j-1]
    */

    const int size = arr.size();

    std::vector<int> memory(size);
    std::deque<int> dq;

    int max_sum = INT_MIN;
    int index = 0;

    while (index < size) {
        // first, drop those who fall before j-k
        while (not dq.empty() and dq.front() < index-k)
            dq.pop_front();

        int prev_max_sum = 0;

        // we got atleast one previous element
        if (not dq.empty()) {
            // the maximum value itself is negative, why would we take that along? start a new chain from here only by returning 0
            prev_max_sum = memory[dq.front()] > 0? memory[dq.front()] : 0;
        }

        memory[index] = arr[index] + prev_max_sum;

        max_sum = std::max(
            max_sum,
            memory[index]
        );

        // make the largest possible sum reside at front
        while (not dq.empty() and memory[index] >= memory[dq.back()])
            dq.pop_back();

        // push the current index back to deque
        dq.emplace_back(index);

        index++;
    }

    return max_sum;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the value of k : ";
    std::cin >> k;

    /*
        This becomes a DP problem:
        let us define our state this way:

        memory[i][j]: maximum sum achievable from index j such that last index taken was i
                      and j <= i + k

        now, since i can be empty as well, so we'll keep extra space to denote that
    */
   std::vector<std::vector<int>> memory(
        size+1,
        std::vector<int>(
            size, -1
        )
   );

   int answer = solve(arr, memory, k);
   std::cout << "\nThe maximum such sum would be : " << answer << "\n";
   std::cout << "\nThe maximum sum using optimized approach : " << solve_optimized(arr, k) << "\n\n";

   return 0;

}