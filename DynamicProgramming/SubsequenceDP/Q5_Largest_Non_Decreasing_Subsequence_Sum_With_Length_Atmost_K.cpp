/*
    Given an array of size N. Also given a positive integer K.
    We need to find out the maximum possible non-decreasing subsequence sum from this array such that the length is atmost K.

    1 <= K <= N <= 10^5
    -10^9 <= A[i] <= 10^9

    The solution uses coordinate compression and K segment trees.
    If U is the number of distinct values, its time complexity is O(NK log U)
    and its extra space complexity is O(KU).
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include "../../segment_tree.hpp"

// Compress the distinct values into sorted ranks so that the segment trees can
// use compact non-negative indices while preserving the original value order.
std::vector<long long> get_cc_array(const std::vector<long long>& arr) {
    // First remove duplicate values; equal values need only one rank.
    std::unordered_set<long long> st;

    for (long long ele : arr)
        st.emplace(ele);

    std::vector<long long> cc_array;

    for (long long ele : st)
        cc_array.emplace_back(ele);

    // Sorting makes a smaller rank mean a smaller original value.
    std::sort(cc_array.begin(), cc_array.end());

    return cc_array;
}

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

    // Every target comes from arr, so this fallback should never be reached.
    return -1;
}

// Find the maximum sum of a non-empty non-decreasing subsequence whose length
// is at most k.
long long solve(const std::vector<long long>& arr, const int k) {
    const int size = arr.size();

    // The only non-empty subsequence of a one-element array is that element.
    if (size == 1)
        return arr[0];

    // Build the value-to-rank mapping used by every segment tree.
    const std::vector<long long> cc_array = get_cc_array(arr);

    /*
        DP state:
        memory[l][r] is represented by the l-th segment tree. At rank r it
        stores the best sum of a valid subsequence seen so far that has length
        at most l and ends with the value represented by rank r.

        To append the current value ele, the previous value must be <= ele.
        Therefore we query ranks [0, rank]. A subsequence using ele has one
        additional element, so the transition reads from memory[l - 1].

        The loop over l goes downward. This ensures that the current element
        cannot be inserted more than once during the same outer iteration.
    */

    // Unused states are initialized to a very small sentinel value.
    const long long MIN = std::numeric_limits<long long>::min()/2;

    // memory[0] is the base layer: it contains no non-empty subsequence.
    // The other K layers represent allowed lengths 1 through K.
    std::vector<SegmentTreeMax<long long>> memory(
        k+1,
        SegmentTreeMax(cc_array.size(), MIN)
    );

    long long max_sum = MIN;

    for (long long ele : arr) {
        // Convert ele to the segment-tree index for its original value.
        const int rank = find_rank(cc_array, ele);

        // Compute every length layer from the previous layer, descending so
        // that this occurrence of ele is used at most once.
        for (int l=k; l>=1; l--) {

            /*
                There are two possibilities:

                1. Extend the best valid subsequence from memory[l - 1] whose
                   final value is <= ele.
                2. Start a new one-element subsequence [ele]. This is valid for
                   every l >= 1 because its length is at most l, not exactly l

                Important base-level detail:
                memory[0].query(0, rank) always returns MIN because layer 0
                represents no non-empty subsequence. Thus, for the first
                element of a subsequence, MIN + ele cannot win, and the max
                expression selects ele. This is how the base case creates the
                best subsequence of length at most 1, including when ele is
                negative.
            */
            long long best_sum = std::max(
                memory.at(l-1).query(0, rank) + ele,
                ele
            );

            // Record the best subsequence ending at this value for length atmost l.
            memory.at(l).update(rank, best_sum);

            // The optimal subsequence may have any length from 1 through k.
            max_sum = std::max(
                max_sum,
                best_sum
            );
        }
    }

    return max_sum;
}


int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum length of the subsequence : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum possible subsequence sum with length atmost " << k << " is : " << answer << std::endl << std::endl;

    return 0;
}