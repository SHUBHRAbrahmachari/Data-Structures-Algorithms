/*
    Problem:
    We have several ice-cream bars with different prices. We want to buy the maximum possible
    number of bars without exceeding budget K, and also the price difference between the most
    expensive and cheapest chosen bar must be at most X.

    Example:
    prices = [1, 2, 3, 4], K = 10, X = 2
    The best choice is [1, 2, 3], whose total cost is 6 and whose price range is 2.
    So the answer is 3.

    Key idea:
    After sorting the prices, we keep a sliding window [left, right].
    The window represents the bars currently under consideration.

    - Add the current bar at the right end.
    - If the window exceeds the budget or the price spread becomes greater than X,
      remove bars from the left until the window becomes valid again.
    - At each step, update the best window size.

    This is a greedy + sliding window solution.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int solve(std::vector<int>& prices, int k, int x) {
    // Sort to make the window naturally increasing in price.
    std::sort(prices.begin(), prices.end());

    int left = 0;
    int right = 0;
    int size = static_cast<int>(prices.size());

    // max_count keeps the best valid answer found so far.
    int max_count = 0;

    // curr_cost stores the total cost of the current window.
    int curr_cost = 0;

    while (right < size) {
        // Include the current price in the valid range we are considering.
        curr_cost += prices[right];

        // If the current window is invalid, remove from the left until it becomes valid again.
        // Invalid means either:
        // 1) total cost > budget
        // 2) max price - min price > allowed difference X
        while (curr_cost > k || prices[right] - prices[left] > x) {
            curr_cost -= prices[left];
            left++;
        }

        // Update the best count for this valid window.
        max_count = std::max(max_count, right - left + 1);

        right++;
    }

    return max_count;
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of ice-cream bars as options : ";
    std::cin >> size;

    std::vector<int> prices(size);
    std::cout << "\nKeep entering the prices : ";
    for (size_t i = 0; i < size; i++)
        std::cin >> prices[i];

    int k;
    std::cout << "\nEnter the budget : ";
    std::cin >> k;

    int x;
    std::cout << "\nEnter the maximum price difference : ";
    std::cin >> x;

    int answer = solve(prices, k, x);
    std::cout << "\nThe maximum number of ice-cream bars you can buy is : " << answer << "\n\n";

    return 0;
}