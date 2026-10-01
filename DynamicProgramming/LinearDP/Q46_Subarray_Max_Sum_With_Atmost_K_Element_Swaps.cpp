/*
    Given an array of integers.
    Choose a contiguous subarray from arr after atmost K element swaps to bring larger elements into your chosen subarray.
    Maximize the subarray sum.

    1 <= K <= N <= 1000
    -10^3 <= A[i] <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>
#include <set>

// O(N^2.log N + N^2.min(K, N))
long long solve(const std::vector<int>& arr, const int k) {
    const int n = arr.size();

    /*
        This problem is a bit more complex than any of the previous.
        To solve this problem efficiently, we can iterate over all possible subarrays A[i...j]
        and use a greedy strategy with DYNAMIC TRACKING to compute the maximum sum after atmost K swaps.

        For any chosen contiguous subarray A[i...j]:
            1> Inside set(IN): The elements inside A[i...j]
            2> Outside set(OUT): All reemaining elements A[0...i-1] U A[j+1...N-1]

        To maximize the sum of IN using atmost K swaps:
            We should greedily replace the smallest elements in IN with the largest element in OUT.
            A swap is only beneficial if and only if OUTe > INe

        1> Initialize the left endpoint i(0 <= i <= N-1)
        2> initialize IN and OUT:
            -> IN initially contains just A[i]
            -> OUT contains every element except A[i]
            -> Keep IN sorted in ASCENDING ORDER and OUT sorted in DESCENDING ORDER.

        3> expand right endpoint j from i to N-1:
            -> for j>i move A[j] from OUT TO IN
            -> calculate base sum for IN
            -> Iterate simultaneously through smallest elements of IN and largest elements of OUT:
                -> if OUTe > INe and total swaps performed < K, add (OUTe-INe) to current subarray sum.
                -> Otherwise break early
            -> Update  global maximum subarray sum
    */
    long long max_sum = std::numeric_limits<long long>::min();

    for (int i = 0; i < n; ++i) {
        std::multiset<int> IN;
        std::multiset<int, std::greater<int>> OUT;

        // initially add all the elements into OUT except arr[i]
        for (int k = 0; k < n; ++k) {
            if (k != i) OUT.insert(arr[k]);
        }

        // add only arr[i] to IN
        IN.insert(arr[i]);

        // current maximum best sum is obviously arr[i]
        int base_sum = arr[i];

        for (int j = i+1; j < n; ++j) {
            // adding this element into IN from OUT and removing that from OUT
            OUT.erase(OUT.find(arr[j]));
            IN.insert(arr[j]);
            base_sum += arr[j];

            long long current_swapped_sum = base_sum;
            int swaps = 0;

            auto it_in = IN.begin();
            auto it_out = OUT.begin();

            while (swaps < k and it_in != IN.end() and it_out != OUT.end()) {
                // if and only if OUTe is greater than INe
                if (*it_out > *it_in) {
                    current_swapped_sum += (*it_out - *it_in);
                    ++it_in;
                    ++it_out;
                    ++swaps;
                } 
                
                else
                    break;
            }

            max_sum = std::max(max_sum, current_swapped_sum);
        }
    }

    return max_sum;
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum number of performable swaps : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nMaximum possible subarray sum would be : " << answer << "\n\n";

    return 0;
}