/*
    Given an array of integers.
    You can either pick an element or skip and element.
    If you pick an element, you cannot consider picking x-1 and x+1 anywhere in this array, where x being the element you picked.

    What is the best possible score you can have?

    1 <= N <= 10^5
    1 <= A[i] <= 10^5
*/

/*
    This thing is a bit tricky.
    The moment we pick an element that particular decision influences
    all the decisons we have made in past and all the decisons we'll be making in the future.

    So one thing is for sure! ORDER DOES NOT MATTER.

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
    Key observation:
    The rule is not about positions, it is about values.
    If we decide to take value x, then we must ignore x - 1 and x + 1 as well,
    which makes this very similar to the classic House Robber problem on the unique values.

    So the first major step is to compress the array by value:
    - all occurrences of the same number are merged together
    - their total contribution becomes the score of that number
    - then we only reason over distinct values in sorted order

    This is valid because every occurrence of the same value behaves identically:
    taking one copy of x means taking all copies of x, and the same "cannot pick adjacent values"
    restriction applies to the value itself, not to each individual index.
*/

long long solve(std::vector<int>& arr) {
    const int size = arr.size();

    if (size == 1)
        return arr[0];

    /*
        Sort so that equal numbers become adjacent.
        After sorting, duplicates are easy to combine into one bucket.
    */
    std::sort(arr.begin(), arr.end());

    /*
        Why do we accumulate the same element sums?
        Because the problem allows us to "collect" the value of each number as many times as it appears.
        If the number 5 appears 3 times, then taking 5 means we gain 5 + 5 + 5 = 15 in total.
        Once we group all equal values into one total, we reduce the problem to a simpler DP over distinct values.
        This preserves the real meaning of the problem while removing redundant repeated states.
    */
    std::unordered_map<int, long long> sums;
    std::vector<int> unique_nums;

    for (int ele : arr) {
        auto itr = sums.find(ele);

        if (itr == sums.end()){
            unique_nums.emplace_back(ele);
            sums.emplace(ele, ele);
        }

        else
            itr->second += ele;
    }

    /*
        DP state idea:
        memory_with_cons[x] = maximum score if we decide to take value x
        memory_without_cons[x] = maximum score if we skip value x
        We process unique values in sorted order, just like a house-robber DP on values.
    */
    std::unordered_map<int, long long> memory_with_cons;
    std::unordered_map<int, long long> memory_without_cons;
    long long max_score = -1;

    for (int i=0; i<unique_nums.size(); i++) {
        const int ele = unique_nums[i];

        if (i == 0) {
            memory_with_cons[ele] = sums[ele];
            memory_without_cons[ele] = 0;

            max_score = std::max(
                max_score,
                std::max(
                    memory_with_cons[ele],
                    memory_without_cons[ele]
                )
            );

            continue;
        }

        /*
            prev_ele is the immediately previous distinct value.
            If the gap between prev_ele and current ele is more than 1, then they do not conflict.
            In that case, we can safely take the best value from the previous state and add the current value's total.
        */
        const int prev_ele = unique_nums[i-1];

        /* Best score seen up to the previous unique value. */
        long long prev_ele_best = std::max(
            memory_with_cons[prev_ele],
            memory_without_cons[prev_ele]
        );

        /*
            If prev_ele is far enough away, then the current value does not interfere with the previous decision.
            This means we can add the current total to the best score from the previous step.
        */
        if (prev_ele < ele-1) {
            memory_with_cons[ele] = prev_ele_best + sums[ele];
            memory_without_cons[ele] = prev_ele_best; 
        }

        /*
            Otherwise, the current value is adjacent to the previous value,
            so it cannot be chosen together with it.
            In this case, we must compare against the value before the previous one.
        */
        else {
            const int target = (i > 1 ? unique_nums[i-2] : -1);

            /* There is no earlier value before the previous one, so the current value can just start fresh. */
            if (target == -1)
                memory_with_cons[ele] = sums[ele];

            /*
                If there is a valid earlier value, then we consider the best result up to that earlier value.
            */
            else {
                long long target_best = std::max(
                    memory_with_cons[target],
                    memory_without_cons[target]
                );

                memory_with_cons[ele] = target_best+sums[ele];
            }

            /* Skipping the current value simply carries forward the best score from the previous unique value. */
            memory_without_cons[ele] = prev_ele_best;
        }
        
        max_score = std::max(
            max_score,
            std::max(
                memory_with_cons[ele],
                memory_without_cons[ele]
            )
        );
    }

    return max_score;
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
    std::cout << "\nThe maximum collectable score would be " << answer << "\n\n";

    return 0;
}

