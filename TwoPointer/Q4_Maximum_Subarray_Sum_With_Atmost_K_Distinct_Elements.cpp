/*
    Given an array of positive integers and an integer K.
    find the maximum sum among all contiguous subarrays that contain atmost K distinct integers.

    1 <= K <= N <= 10^5
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// O(NK)
long long find_maximum_window_sum(const std::vector<long long>& array, const size_t k) {
    const size_t size = array.size();

    // let me maintain a prefix sum so that when i slide, i don't need to re-calculate sum again
    std::vector<long long> prefix_sums(size, array[0]);

    for (size_t i=1; i<size; i++)
        prefix_sums[i] = prefix_sums[i-1] + array[i];

    // a tracker to keep last occurrence index of all the unique elements
    std::unordered_map<long long, size_t> last_indices;
    
    int left = 0;
    int right = 0;
    long long maximum_sum = 0;

    // O(N)
    while (right < size) {

        const long long num = array[right];

        auto itr = last_indices.find(num);

        // ok, this element already exists, no worry!
        if (itr != last_indices.end()) {
            // update last occurrence index
            itr->second = right;
        }

        // ok, this element we have not seen earlier
        else {
            // case 1: we do not already have k unique elements in this window
            if (last_indices.size() < k) {
                // ok we can add this element without worries
                last_indices.emplace(num, right);
            }

            // case 2: we already have k unique elements, we must shrink our window
            else {
                size_t left_most_index = size;
                std::unordered_map<long long, size_t>::iterator itr_to_delete;

                // see which unique element has its last occurrence at left-most index
                // O(K)
                for (auto num_itr=last_indices.begin(); num_itr != last_indices.end(); std::advance(num_itr, 1)) {
                    if (num_itr->second < left_most_index) {
                        left_most_index = num_itr->second;
                        itr_to_delete = num_itr;
                    }
                }

                // slide left to right
                left = left_most_index + 1;

                // delete that unique element
                last_indices.erase(itr_to_delete);

                // add this element to map
                last_indices.emplace(num, right);
            }
        }

        // update maximum sum
        maximum_sum = std::max(
            maximum_sum,
            prefix_sums[right] - (left == 0? 0 : prefix_sums[left-1])
        );

        right++;
    }

    return maximum_sum;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;
    
    std::vector<long long> array(size);
    std::cout << "\nEnter the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> array[i];

    size_t k;
    std::cout << "\nEnter the maximum number of distinct elements in the window : ";
    std::cin >> k;

    const long long answer = find_maximum_window_sum(array, k);
    std::cout << "\nThe maximum window sum would be : " << answer << std::endl << std::endl;

    return 0;
}