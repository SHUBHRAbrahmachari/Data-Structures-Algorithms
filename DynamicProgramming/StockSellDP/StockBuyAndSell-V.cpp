/*
    Given the price of a stock on each day, find the maximum profit obtainable
        by making any number of buy/sell transactions.

        Rules:
        - We may buy only when we are not already holding a stock.
        - We may sell only when we are holding a stock.
        - We pay the transaction fee F whenever we sell.
        - We are allowed to make atmost K transactions only

        Constraints:
        2 <= N <= 10^7
        1 <= A[i] <= 10^9
        1 <= K <= 10^5
        0 <= F <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2


long long solve(const std::vector<int>& prices, const int k, const int fee) {
    // `size` is the number of available trading days.
    const size_t size = prices.size();

    /*
        DP state definitions:

        max_net_worths[d][t]:
            The maximum net worth at the end of day `d` while holding one stock,
            where the stock belongs to transaction number `t` or earlier.
            Buying a stock decreases net worth by its price.

        max_net_profits[d][t]:
            The maximum realized profit at the end of day `d` after completing
            at most `t` transactions. In this problem, a transaction is counted
            when its stock is sold, and the fee is paid at that time.

        The first dimension is the day. The second dimension is the maximum
        number of transactions allowed so far.
    */
    // A holding state can be impossible for a given state transition, so it is
    // initialized to a very small value instead of being initialized to zero.
    std::vector<std::vector<long long>> max_net_worths(
        size,
        std::vector<long long>(k+1, MIN)
    );

    // Profit is initialized to zero because doing no transaction is always valid.
    std::vector<std::vector<long long>> max_net_profits(
        size,
        std::vector<long long>(k+1)
    );

    /*
        BASE CASE - day 0:

        If we buy on the first day, our net worth is -prices[0]. This is valid
        for every transaction budget because buying the first stock is possible
        regardless of how many total transactions are permitted.

        No sale can be completed on the first day, so every profit state remains
        zero, as established by the vector initialization above.
    */
    for (size_t t=0; t<=k; t++)
        max_net_worths[0][t] = -prices[0];


    // Day 0 is initialized above; each remaining day is processed in order.
    for (size_t day=1; day<size; day++) {
        // The current day's price is used for either buying or selling.
        const int price = prices[day];

        /*
            Process transaction budgets from larger to smaller values.
            The loop ends at t=1 because t=0 represents no transaction and is
            only a base state; it does not need to be updated.
        */
        for (size_t t=k; t>=1; t--) {
            /*
                Update the best state while holding a stock.

                Option 1: Continue holding the stock from yesterday. The
                transaction budget does not change while holding it.

                Option 2: Buy today using the best profit available after at
                most t-1 completed transactions. Buying the next stock starts
                transaction t, and therefore reduces net worth by `price`.
            */
            max_net_worths[day][t] = std::max(
                max_net_worths[day-1][t],
                max_net_profits[day-1][t-1] - price
            );

            /*
                Update the best realized profit after at most t transactions.

                Option 1: Do not sell today, so carry forward yesterday's best
                realized profit. This carry-forward is essential after a price
                decline because an earlier sale may still be optimal.

                Option 2: Sell the stock held yesterday. Add today's price and
                subtract the transaction fee because the sale completes the
                transaction.
            */
            max_net_profits[day][t] = std::max(
                max_net_profits[day-1][t],
                max_net_worths[day-1][t] + price - fee
            );
        }
    }

    // After the final day, return the best profit using at most k transactions.
    return max_net_profits[size-1][k];
}

int main() {
    // Read the number of days for which stock prices are provided.
    size_t size;
    std::cout << "\nEnter the total number of listing days : ";
    std::cin >> size;

    // Read one stock price for each day, in chronological order.
    std::vector<int> prices(size);
    std::cout << "\nKeep entering the prices : ";
    for (size_t day=0; day<size; day++)
        std::cin >> prices[day];

    // Read the maximum number of buy/sell transactions allowed.
    int k;
    std::cout << "\nEnter the maximum possible transactions allowed : ";
    std::cin >> k;

    // The fee is charged once for every completed sale.
    int fee;
    std::cout << "\nEnter the transaction fee : ";
    std::cin >> fee;

    // Solve the problem and display the maximum achievable profit.
    const long long answer = solve(prices, k, fee);
    std::cout << "\nMaximum possible profit after atmost " << k << " transactions will be : " << answer << "\n";

    // Report successful program completion.
    return 0;
}