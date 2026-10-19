/*
    Given an integer array `coins` representing coins of different denominations.
    We are also given an integer `amount` representing the total amount of money we need to make.

    Return the fewest number of coins needed to reach that particular amount.
    If not possible also print that one.

    1 <= |coins[]| <= 10^5
    1 <= coins[i] <= 10^5
    1 <= amount <= 10^5
*/

#include <iostream>
#include <vector>
#include <queue>

int solve(const std::vector<int>& coins, const int amount) {
    // get a tracker
    std::vector<bool> vis(amount+1, false);

    // get a queue to run the BFS
    std::queue<int> que;

    // initialize the BFS
    que.emplace(0);
    vis[0] = true;

    // minimum count o coins required
    int count = 0;

    while (not que.empty()) {
        const int size = que.size();

        for (int i=0; i<size; i++) {
            int curr_amount = que.front();
            que.pop();

            // we have reached the target amount
            if (curr_amount == amount)
                return count;

            for (const int& coin : coins) {
                const int next_amount = curr_amount + coin;
                if (next_amount <= amount and not vis[next_amount]) {
                    que.emplace(next_amount);
                    vis[next_amount] = true;
                }
            }
        }

        // increase coin count
        count++;
    }
    
    // target amount is not reachable
    return -1;
}

int main() {
    int size;
    std::cout << "\nEnter total type of available coins : ";
    std::cin >> size;

    std::vector<int> coins(size);
    std::cout << "\nKeep entering the coin denominations : ";
    for (int i=0; i<size; i++)
        std::cin >> coins[i];

    int amount;
    std::cout << "\nEnter the final amount to make : ";
    std::cin >> amount;
    
    const int ans = solve(coins, amount);

    if (ans == -1)
        std::cout << "\nTarget amount is never reachable!\n\n";
    else
        std::cout << "\nWe need atleast " << ans << " coin(s)\n\n";

    return 0;
}