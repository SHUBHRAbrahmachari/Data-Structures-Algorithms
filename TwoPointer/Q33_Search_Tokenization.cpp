/*
    Given an array of positive integers.
    Count the total number of subarrays having atmost K distinct elements

    1 <= K <= N <= 10^5
*/

#include <iostream>
#include <vector>
#include <unordered_map>

int solve(const std::vector<int>& arr, const int k) {
    const int size = arr.size();

    int left = 0;
    int right = 0;
    int counter = 0;

    std::unordered_map<int, int> freq;

    while (right < size) {
        // adding current element to our subarray
        auto itr = freq.find(arr[right]);

        if (itr != freq.end())
            itr->second += 1;
        
        else
            freq.emplace(arr[right], 1);

        // shrink the window as long as we exceed maximum unique elements
        while (freq.size() > k) {
            freq.at(arr[left]) -= 1;

            // this element no more exists
            if (freq.at(arr[left]) == 0)
                freq.erase(arr[left]);

            left++;
        }

        // for this right, all possible left values
        counter += right - left + 1;

        right++;
    }

    return counter;
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
    std::cout << "\nEnter the maximum number of distinct elements to have : ";
    std::cin >> k;

    const int answer = solve(arr, k);
    std::cout << "\nThere are " << answer << " such total subarrays\n\n";

    return 0;
}