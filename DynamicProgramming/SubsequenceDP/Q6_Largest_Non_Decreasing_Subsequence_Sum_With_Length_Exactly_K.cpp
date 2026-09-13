/*
    Given an array of size N. Also given a positive integer K.
    We need to find out the maximum possible non-decreasing subsequence sum such that length of the subsequence is exactly K.
    If solution is not possible simply print "No Such Subsequence Exists"

    1 <= K <= N <= 10^5
    -10^9 <= A[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <algorithm>
#include "../../segment_tree.hpp"

#define MIN std::numeric_limits<long long>::min()/2

std::vector<long long> get_cc_array(const std::vector<long long>& arr) {
    std::unordered_set<long long> st;

    for (long long ele : arr)
        st.emplace(ele);

    std::vector<long long> cc_arr;
    for (long long ele : st)
        cc_arr.emplace_back(ele);

    std::sort(cc_arr.begin(), cc_arr.end());

    return cc_arr;
}

size_t find_rank(const std::vector<long long>& cc_arr, const long long target) {
    size_t left = 0;
    size_t right = cc_arr.size()-1;

    while (left <= right) {
        const size_t mid = (left + right)/2;

        if (cc_arr[mid] == target)
            return mid;

        else if (cc_arr[mid] > target)
            right = mid-1;
        
        else
            left = mid+1;
    }

    return -1;
}

long long solve(const std::vector<long long>& arr, const size_t k) {
    const size_t size = arr.size();

    if (size == 1 and k == 1)
        return arr[0];
    
    if (size == 1 and k > 1)
        return MIN;

    /*
        Coordinate compression maps every distinct value to a rank in sorted
        order. Therefore, rank(a) <= rank(b) is equivalent to a <= b, while
        using only small integer indices in the segment trees.
    */
    const std::vector<long long> cc_arr = get_cc_array(arr);

    /*
        For every length l, memory[l] is a segment tree over compressed ranks.

        At an individual rank r, memory[l] stores the maximum sum of a valid
        non-decreasing subsequence of exactly length l whose LAST value has
        rank exactly r.

        To append the current value x (rank rx), the previous value must be
        <= x.  Thus, memory[l-1].query(0, rx) gives the best subsequence of
        length l-1 that can be extended by x.  The segment-tree prefix query
        is what enforces the non-decreasing condition.

        A value of MIN means that no valid subsequence for that state exists.
        Segment trees give O(log N) prefix queries and point updates.

        There are k+1 trees because the answer must have exactly length k.
    */
    std::vector<SegmentTreeMax<long long>> memory(
        k+1,
        SegmentTreeMax<long long>(size, MIN)
    );

    for (long long ele : arr) {
        /*
            Find the compressed rank of the current value in O(log U), where U
            is the number of distinct values.
        */
        const size_t rank = find_rank(cc_arr, ele);

        /*
            Process lengths in descending order. This is essential: a state
            created using the current element must not be reused again for a
            longer state during this same iteration. Descending l ensures that
            memory[l-1] still describes subsequences formed before `ele`.
        */
        for (size_t l=k; l>=1; l--) {
            /*
                Every element by itself is a valid subsequence of length 1.
                It ends at this element's rank and has sum equal to `ele`.
            */
            if (l == 1)
                memory[l].update(rank, ele);

            else {
                /*
                    Transition:
                      best[l][rank] = max(
                          best[l][rank],
                          best[l-1][any rank <= rank] + ele
                      )

                    The prefix query finds the best subsequence that can be
                    extended while preserving non-decreasing order.
                */
                const long long prev_sum = memory[l-1].query(0, rank);

                // any valid subsequence sum already exists, so we can proceed.
                if (prev_sum != MIN) {
                    /*
                        Keep the better of the old state and the state obtained
                        by appending `ele` to the best valid shorter subsequence.
                    */
                    long long best_sum = memory[l].query(0, rank);
                    long long proposed_sum = prev_sum + ele;

                    memory[l].update(
                        rank,
                        std::max(
                            best_sum,
                            proposed_sum
                        )
                    );
                }
            }
        }
    }

    /*
        Any ending rank is allowed for the final element, so query the complete
        rank range for the best subsequence of exactly length k.
    */
    return memory[k].query(0, size-1);
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> arr(size);
    std::cout << "\nKeep entering the elements in the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    size_t k;
    std::cout << "\nEnter the exact length of K : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    if (answer == MIN)
        std::cout << "\nNo Such Subsequence Exists!\n\n";
    else
        std::cout << "\nThe maximum possible such subsequence sum would be : " << answer << "\n\n";

    return 0;
}