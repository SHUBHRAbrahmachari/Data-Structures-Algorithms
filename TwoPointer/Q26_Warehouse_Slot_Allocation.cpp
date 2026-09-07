/*
    Given a binary array `bins`.
    Return the maximum number of consecutive 1's you can obtain
    such that you can toggle atmost K zero's

    1 <= N <= 10^6
*/

#include <iostream>
#include <vector>
#include <deque>

int solve(const std::vector<int>& bins, const int k) {
    const int size = bins.size();

    std::deque<int> indices;
    int left = 0;
    int right = 0;
    int counter = 0;
    int max_length = 0;

    while (right < size) {
        if (bins[right] == 0) {
            counter++;
            indices.emplace_back(right);
        }

        // the moment we breach the maximum toggle limit
        if (counter > k) {
            left = indices.front() + 1;
            indices.pop_front();
            counter--;
        }

        max_length = std::max(
            max_length,
            right - left + 1
        );

        right++;
    }

    return max_length;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> bins(size);
    std::cout << "\nKeep entering the elements : ";
    for (int i=0; i<size; i++)
        std::cin >> bins[i];

    int k;
    std::cout << "\nEnter the maximum number of toggles : ";
    std::cin >> k;

    const int answer = solve(bins, k);
    std::cout << "\nThe maximum length of such subarray would be : " << answer << std::endl << std::endl;

    return 0;
}