/*
    An amazon fufilment center processes an array of packages where package[i]
    represents the monetary value of i-th package. You are given an integer K
    representing the length of a contiguous window of pckages to load onto a single delivery truck, and an integer threshold.
    Calculate the maximum total value of a contiguous sequence of exactly K packages that no single package exceeds the threshold,
    if no such valid window is present then return -1

                            1 <= K <= N <= 10^5
                            1 <= P[i] <= 10^9
                            1 <= T <= 10^9

*/

#include <iostream>
#include <vector>

long long find_maximum_window_sum(const std::vector<long long>& array, const size_t k, const long long t) {
    const size_t size = array.size();

    long long maximum_sum = -1;
    long long current_sum = 0;
    size_t left = 0;
    size_t right = 0;

    while (right < size) {
        if (array[right] > t) {
            right += 1;
            left = right;
            current_sum = 0;
            continue;       // the right next can exceed threshold as well na!
        }

        current_sum += array[right];

        if (right - left + 1 == k) {
            maximum_sum = std::max(
                maximum_sum,
                current_sum
            );

            current_sum -= array[left++];
        }

        right++;
    }

    return maximum_sum;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> array(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> array[i];

    size_t k;
    std::cout << "\nEnter the length of the window : ";
    std::cin >> k;

    long long t;
    std::cout << "\nEnter the threshold : ";
    std::cin >> t;

    long long answer = find_maximum_window_sum(array, k, t);
    std::cout << "\nThe maximum window sum is : " << answer << std::endl << std::endl;

    return 0;
}

