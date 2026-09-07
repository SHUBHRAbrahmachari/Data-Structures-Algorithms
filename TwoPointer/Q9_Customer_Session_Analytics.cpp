/*
    An analytics engine processes continuous user activity logs as an array of user IDs.
    Find the total number of contiguous session subarrays that contain exactly K distinct user IDs.

            1 <= K <= N <= 10^5
*/
/*
    tweak this problem a bit:

    exactly K = atmost K - atmost (k-1)

    at_most is universal helper function
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

size_t count_subarrays(const std::vector<int>& logs, const size_t k) {
    const size_t size = logs.size();

    size_t right = 0;
    size_t left = 0;
    size_t counter = 0;

    std::unordered_map<int, size_t> frequencies;

    while (right < size) {
        int user_id = logs[right];

        auto itr = frequencies.find(user_id);
        if (itr == frequencies.end())
            frequencies.emplace(user_id, 1);
        else
            frequencies.at(user_id) += 1;

        // invalidate them
        while (frequencies.size() > k) {
            int left_user_id = logs[left];
            frequencies.at(left_user_id) -= 1;

            if (frequencies.at(left_user_id) == 0)
                frequencies.erase(left_user_id);

            left++;
        }

        // for this right, all left pointers are taken
        counter += (right - left + 1);
        right++;
    }

    return counter;

}

int main() {
    size_t size;
    std::cout << "\nEnter the length of the array : ";
    std::cin >> size;

    std::vector<int> logs(size);
    std::cout << "\nKeep entering the user IDs as logs : ";
    for (size_t i=0; i<size; i++)
        std::cin >> logs[i];

    size_t k;
    std::cout << "\nEnter the exact number of unique user ids to have : ";
    std::cin >> k;

    const size_t answer = count_subarrays(logs, k) - count_subarrays(logs, k-1);
    std::cout << "\nThere are total " << answer << " such subarray(s) present" << "\n\n";

    return 0;
}

