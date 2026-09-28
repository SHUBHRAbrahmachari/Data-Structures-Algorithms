/*
    Pick a subsequence (keep array order, skip anything) whose steps alternate
    up and down. For example, 4, 9, 6, 12 has steps +, -, +. The task is to
    maximize the sum of the picked values; negative values are allowed.

    For each possible ending value, track two best sums: one where the last
    step went up, and one where it went down. A new up-step must follow a
    down-step from a smaller value; a new down-step must follow an up-step
    from a larger value. Compressed value ranks plus max segment trees let us
    find the best eligible previous sum quickly.

    Constraints: 1 <= N <= 10^5; -10^5 <= arr[i] <= 10^5.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include "../../segment_tree.hpp"

// Marks a DP state that has not been reached. It is safely below any possible
// answer, while leaving room for arithmetic without using LLONG_MIN itself.
#define MIN std::numeric_limits<long long>::min()/2

/*
    Keep each distinct value once, in sorted order. Its position in this list
    is its rank: ranks preserve value ordering, but fit directly in the trees.
*/
std::vector<int> get_cc_array(const std::vector<int>& arr) {
    std::unordered_set<int> st;
    for (auto ele : arr)
        st.emplace(ele);

    std::vector<int> cc_arr;
    for (auto ele : st)
        cc_arr.emplace_back(ele);

    std::sort(cc_arr.begin(), cc_arr.end());
    return cc_arr;
}

/*
    Find target's position in the sorted compressed values using binary search.
    Every value passed here came from arr, so it must be present.
*/
int find_rank(const std::vector<int>& cc_arr, const int target) {
    int left = 0;
    int right = cc_arr.size()-1;

    while (left <= right) {
        int mid = (left+right)/2;

        if (cc_arr[mid] == target)
            return mid;

        else if(cc_arr[mid] > target)
            right = mid-1;

        else
            left = mid+1;
    }

    return -1;
}


/*
    Return the largest sum among all subsequences whose nonzero steps alternate
    in sign. The input is guaranteed to contain at least one element.
*/
long long solve(const std::vector<int>& arr) {
    const int size = arr.size();

    if (size == 1)
        return arr[0];

    const std::vector<int> cc_arr = get_cc_array(arr);

    /*
        At rank r, memory_pos[r] is the best sum ending there after an up-step;
        memory_neg[r] is the best after a down-step. A singleton has no step,
        so it can start either kind of wiggle and is seeded in both trees.

        Each tree stores maxima by value rank. Its range query finds the best
        previous sum among eligible values in O(log N); update records the best
        sum found so far for one rank and direction.
    */
    SegmentTreeMax<long long> memory_neg(cc_arr.size(), MIN);
    SegmentTreeMax<long long> memory_pos(cc_arr.size(), MIN);

    int LAST_RANK = 0;
    int TOP_RANK = cc_arr.size()-1;

    // Left-to-right processing ensures every transition uses earlier elements.
    for (int ele : arr) {
        const int rank = find_rank(cc_arr, ele);

        /*
            Make a down-step to ele. The previous value must be greater, and
            its last step must have been up. Query only ranks above rank so
            equal values cannot create a zero step.
        */
        long long prev_pos_best = (rank == TOP_RANK ? MIN : memory_pos.query(rank+1, TOP_RANK));
        long long curr_neg_best = memory_neg.query(rank, rank);

        // If there is no predecessor, ele can still begin a new subsequence.
        if (prev_pos_best == MIN and curr_neg_best == MIN)
            memory_neg.update(
                rank, (long long)ele
            );
        
        // Extend the best predecessor, unless its negative sum would make
        // starting fresh at ele better.
        else if (prev_pos_best != MIN and curr_neg_best == MIN)
            memory_neg.update(
                rank,

                std::max(
                    0LL, prev_pos_best
                ) + ele
            );

        // Keep the better of the state already at this rank and the new
        // candidate. If no predecessor exists but a state does, leave it alone.
        else if (prev_pos_best != MIN and curr_neg_best != MIN) {
            long long prev_best_candidate = std::max(
                0LL, prev_pos_best
            ) + ele;

            memory_neg.update(
                rank,
                std::max(
                    curr_neg_best,
                    prev_best_candidate
                )
            );
        }

        // Make the mirror transition: an up-step needs a smaller previous
        // value whose last step was down. The strict rank range also excludes
        // equal values, which are not a valid step.
        long long prev_neg_best = (rank == LAST_RANK ? MIN : memory_neg.query(LAST_RANK, rank-1));
        long long curr_pos_best = memory_pos.query(rank, rank);

        // As above, start with ele when no valid predecessor or old state exists.
        if (prev_neg_best == MIN and curr_pos_best == MIN)
            memory_pos.update(
                rank, (long long)ele
            );

        // Extend when profitable; otherwise restart at ele rather than keeping
        // a negative prefix.
        else if (prev_neg_best != MIN and curr_pos_best == MIN)
            memory_pos.update(
                rank,
                std::max(
                    0LL,
                    prev_neg_best
                ) + ele
            );

        // Compare the new candidate with the best state already at this rank.
        // If there is no predecessor but an old state exists, keep that state.
        else if (prev_neg_best != MIN and curr_pos_best != MIN) {
            long long prev_best_candidate = std::max(
                0LL,
                prev_neg_best
            ) + ele;

            memory_pos.update(
                rank,
                std::max(
                    curr_pos_best,
                    prev_best_candidate
                )
            );
        }
    }

    // The subsequence may end at any value and in either direction.
    return std::max(
        memory_neg.query(LAST_RANK, TOP_RANK),
        memory_pos.query(LAST_RANK, TOP_RANK)
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nMaximum such answer would be : " << answer << "\n\n";

    return 0;
}