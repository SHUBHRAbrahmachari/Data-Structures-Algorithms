/*
    Given an array of integers `packets` representing dynamic network packet sizes
    and a sliding window of size k moving from left to right.
    Return an array containing the maximum element at every window

    1 <= N <= 10^6
    -10^5 <= A[i] <= 10^5
    1 <= K <= N
*/

#include <iostream>
#include <vector>
#include <deque>

std::vector<int> find_max_elements(const std::vector<int>& packets, const int k) {
    const size_t size = packets.size();

    std::vector<int> ans;
    std::deque<int> dq;
    int i = 0;

    while (i < k-1) {
        while (not dq.empty() and packets[i] >= packets[dq.back()])
            dq.pop_back();

        dq.emplace_back(i);
        i++;
    }

    while (i < size) {
        // first, drop those indices that do not even fall under this window
        while (not dq.empty() and dq.front() <= i-k)
            dq.pop_front();

        // now add this element to the current window
        while (not dq.empty() and packets[i] >= packets[dq.back()])
            dq.pop_back();

        dq.emplace_back(i);

        ans.emplace_back(packets[dq.front()]);
        i++;
    }

    return ans;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> packets(size);
    std::cout << "\nKeep entering the packet sizes : ";
    for (size_t i=0; i<size; i++)
        std::cin >> packets[i];

    int k;
    std::cout << "\nEnter the window size : ";
    std::cin >> k;

    const std::vector<int> ans = find_max_elements(packets, k);
    for (int ele : ans)
        std::cout << ele << " ";
    std::cout << std::endl;

    return 0;
}