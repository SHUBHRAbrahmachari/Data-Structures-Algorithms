/*
    You are given a binary array `workload`. And a positive integer K.
    Return total number of non-empty contiguous subarrays with a total sum equal to goal.

    1 <= k <= N <= 10^5
*/

/*
    Yes we can do with using atmost(k) - atmost(k-1) logic
    But i think, we have already learned something to tackle this probelm.

    count of subarray with target sum? remeber? here target == k
*/

#include <iostream>
#include <vector>
#include <unordered_map>

int count_subarrays(const std::vector<int>& array, const int k) {
    std::unordered_map<int, int> freq;
    int cum_sum = 0;
    int counter = 0;

    for (int bit : array) {
        cum_sum += bit;

        // ok we got a subarray equal to target
        if (cum_sum == k)
            counter++;

        // now look if we have the counterpart against this cum_sum
        const int target = cum_sum - k;

        auto itr = freq.find(target);
        if (itr != freq.end())
            counter += itr->second;

        // also we need to store it for future preference
        itr = freq.find(cum_sum);
        if (itr != freq.end())
            itr->second += 1;
        else
            freq.emplace(cum_sum, 1);
    }

    return counter;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "\nKeep entering the pulses : ";
    for (int i=0; i<size; i++)
        std::cin >> array[i];

    int k;
    std::cout << "\nEnter the target : ";
    std::cin >> k;

    const int answer = count_subarrays(array, k);
    std::cout << "\nThere are total " << answer << " such subarray(s) \n\n";

    return 0;
}

