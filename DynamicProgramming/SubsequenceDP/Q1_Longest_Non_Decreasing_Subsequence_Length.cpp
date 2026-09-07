/*
    Given an array of integers, find the length of its longest
    non-decreasing subsequence.

    A subsequence keeps the original order of the elements, but elements do not
    need to be adjacent. "Non-decreasing" means every element is greater than
    or equal to the element before it.

    Constraints:
        1 <= N <= 10^5
        -10^9 <= array element <= 10^9

    The solution uses binary search and runs in O(N log N) time.
*/

#include <iostream>
#include <vector>

// Return the index of the first value in tracker that is strictly greater than ele.
int find(const std::vector<int>& tracker, const int ele) {
    const int size = tracker.size();

    int left = 0;
    int right = size-1;

    // If no value is greater than ele, solve() will append ele to tracker.
    int ans = -1;

    while (left <= right) {
        int mid = (left+right)/2;

        // This may be the answer, but continue searching to its left for the first one.
        if (tracker[mid] > ele) {
            ans = mid;
            right = mid - 1;
        }

        else
            left = mid + 1;
    }

    return ans;
}

// Return the length of the longest non-decreasing subsequence in arr.
int solve(const std::vector<int>& arr) {
    const int size = arr.size();

    // An empty or one-element array has a subsequence of the same length.
    if (size < 2)
        return size;

    /*
        tracker[i] stores the smallest possible ending value of a
        non-decreasing subsequence of length i + 1 found so far.

        tracker is always sorted. For each new element ele:

        1. Find the first tracker value greater than ele.
        2. Replace that value with ele. A smaller ending value leaves more
           room for future elements to extend the subsequence.
        3. If no value is greater than ele, append ele. This means a longer
           non-decreasing subsequence has been found.

        Replacing values does not preserve the actual subsequence. However,
        it preserves the best possible ending value for every length, so the
        number of values in tracker is the required maximum length.
    */
   std::vector<int> tracker;

   // Process each element once; find() takes O(log N) time.
   for (int ele : arr) {
        int desired_index_to_replace = find(tracker, ele);

        // No greater ending value exists, so extend the longest length.
        if (desired_index_to_replace == -1)
            tracker.emplace_back(ele);

        // Improve the ending value for a subsequence of this length.
        else
            tracker[desired_index_to_replace] = ele;
   }

   return tracker.size();
}

int main() {
    int size;
    std::cout << "\nEnter the number og elements you have : ";
    std::cin >> size;

    // Read the input array.
    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    const int answer = solve(arr);
    std::cout << "\nThe length of longest possible non-decreasing subsequence would be : " << answer << std::endl << std::endl;

    return 0;
}