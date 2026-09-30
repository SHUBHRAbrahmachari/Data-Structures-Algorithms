/*
    Given an array of size N.
    We need to break this array into K contiguous partitions of length atmost K.
    For every partiton we replace all elements by the maximum element of the partition.
    Find the maximum sum of the array!

    1 <= N <= 10^5
    1 <= K <= 10^3
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

/*
    We will directly jump with the tabulation approach now.
    As of now we're well capable of doing that!
*/
long long solve(const std::vector<int>& arr, const int k) {
    const int size = arr.size();

    if (size == 1)
        return arr[0];

    /*
        Let us define our DP state first! The same question we asked while defining our Memoization DP! 
        We will just calculate in reverse order this is it!

            memory[i]: from index i if we make furthermore partitions, what the maximum possible partition sum we are going to have from them?
    */
    std::vector<long long> memory(size);

    // base case initialization
    memory[size-1] = arr[size-1];

    for (int i=size-2; i>=0; i--) {
        long long best_sum = MIN;
        long long curr_max = MIN;

        for (int start=i; start<std::min(size, i+k); start++) {
            // step 1> update curr_max
            curr_max = std::max(
                curr_max,
                (long long)arr[start]
            );

            // update best sum for atmost K length
            best_sum = std::max(
                best_sum,
                (start-i+1)*curr_max + (start + 1 < size ? memory[start+1] : 0)
            );
        }

        // finally update your DP state in this position
        memory[i] = best_sum;
    }
    
    return memory[0];
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
    std::cout << "\nEnter the maximum window size : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum sum of the elements will be : " << answer << "\n\n";

    return 0;
}