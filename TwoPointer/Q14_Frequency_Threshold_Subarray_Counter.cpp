/*
    Given an array of positive integers nums and a positive integer K.
    Let M be the maximum value present across entrire array.
    Return total number of subarrays where M appears atleast K times.

    1 <= N <= 10^5
    1 <= nums[i] <= 10^9
    1 <= K <= N
*/

/*
    Let us just find out, how many subarrays are there with atmost K-1 M's present
*/

#include <iostream>
#include <vector>
#include <algorithm>

// counts number of subarrays where M appears atmost K times
int count_subarrays(const std::vector<int>& array, const int k, const int m) {
    const size_t size = array.size();

    int m_counter = 0;
    int right = 0;
    int left = 0;
    int count = 0;

    while (right < size) {
        if (array[right] == m)
            m_counter++;

        while (m_counter > k) {
            if (array[left] == m)
                m_counter--;

            left++;
        }

        // count all subarrays ending at `right`
        count += right - left + 1;

        right++;
    }

    return count;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> array[i];

    int k;
    std::cout << "\nEnter the minimum frequency of the maximum value : ";
    std::cin >> k;

    const int m = *std::max_element(array.begin(), array.end());

    int total_possible_subarrays = (size*(size+1))/2;
    int subarrays_to_remove = count_subarrays(array, k-1, m);

    std::cout << "\nTotal " << (total_possible_subarrays - subarrays_to_remove) << " such subarray(s) are present! \n\n";
    
    return 0;
}

