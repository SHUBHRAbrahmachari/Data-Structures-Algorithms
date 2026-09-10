/*
    Given an array of size N.
    You are supposed to find the maximum possible subsequence sum such that the subsequence is a NON-DECREASING subsequence

    1 <= N <= 10^5
    -10^9 <= A[i] <= 10^9

    The solution uses coordinate compression and a segment tree.
    If U is the number of distinct values, its time complexity is O(N log U)
    and its extra space complexity is O(U).

    #O(NlogN) #Optimization #BinarySearch #SegmentTree #RangeQueryOptimization
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include "../../segment_tree.hpp"

// Segment-tree indices must be non-negative and compact. Coordinate compression
// maps the distinct array values to sorted ranks 0, 1, ..., U - 1. The relative
// order is preserved, so comparing ranks is equivalent to comparing values.
std::vector<long long> get_cc_array(const std::vector<long long> arr) {
    // Keep one copy of each value before assigning sorted ranks.
    std::unordered_set<long long> st;

    for (const long long ele : arr)
        st.emplace(ele);

    std::vector<long long> cc_array;

    for (long long ele : st)
        cc_array.emplace_back(ele);

    // Sorting makes the rank order match the original numeric order.
    std::sort(cc_array.begin(), cc_array.end());

    return cc_array;
}

// Return the compressed rank of target. The target is guaranteed to occur in
// cc_array because the compressed array was built from the input array.
int find_rank(const std::vector<long long>& cc_array, const long long target) {
    int left = 0;
    int right = cc_array.size()-1;

    while (left <= right) {
        const int mid = (left+right)/2;

        if (cc_array[mid] == target)
            return mid;

        else if (cc_array[mid] > target)
            right = mid-1;

        else
            left = mid+1;
    }

    // Defensive fallback; this path is not expected for a value from arr.
    return -1;
}

// Find the maximum sum of a non-empty non-decreasing subsequence.
long long solve(const std::vector<long long>& arr) {
    const int size = arr.size();

    // A one-element array has exactly one possible non-empty subsequence.
    if (size == 1)
        return arr[0];

    // Build the sorted value-to-rank mapping used by the segment tree.
    const std::vector<long long> cc_arr = get_cc_array(arr);

    /*
        DP state:
        memory[r] stores the best sum of a valid subsequence seen so far whose
        final value has compressed rank r. The segment tree stores the maximum
        over these states, allowing a prefix maximum query in O(log U) time.
    */

    // MIN means that no subsequence has been formed at an unused rank yet.
    const long long MIN = std::numeric_limits<long long>::min()/2;

    SegmentTreeMax<long long> memory(cc_arr.size(), MIN);

    /*
        Process elements from left to right so that every transition preserves
        subsequence order. For the current value ele, only earlier subsequences
        ending at a value <= ele may be extended. Therefore query ranks [0, rank].
    */

    long long max_sum = MIN;
    for (long long ele : arr) {
        // Convert the current value to the index used by the segment tree.
        const int rank = find_rank(cc_arr, ele);

        // Get the best earlier subsequence that can legally be followed by ele.
        const long long prev_sum = memory.query(0, rank);

        // Either extend that subsequence or start a new subsequence at ele.
        long long best_sum = std::max(
            prev_sum + ele,
            ele
        );

        // Store the best subsequence ending at this value/rank.
        memory.update(rank, best_sum);

        // The answer may end at any rank, so maintain the global maximum.
        max_sum = std::max(
            max_sum,
            best_sum
        );
    }

    return max_sum;
}

int main () {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum possible non-decreasing subsequence sum would be : " << answer << std::endl << std::endl;

    return 0;
}