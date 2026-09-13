/*
    Given an array of positive integers denoting the prices of a listed stcok in each day.
    You are a stock trader. You want to earn by buying and selling a stock.

    Although you can make atmost 1 transaction and with the completed transaction you must pay a transaction fees F.

    > you can only buy a stock when you don't already have a stock
    > you can only sell a stock when you already hold a stock
    > you can make as many as transactions as you want

    What is the maximum profit you can earn?

    2 <= N <= 10^7
    1 <= A[i] <= 10^9
    0 <= F <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& prices, const int fee) {
    /*
        We use two dynamic-programming states while scanning the prices from
        left to right. Each state represents the best result after processing
        all days seen so far.

        1. max_net_profit:
           The maximum cash available when we do not currently hold a stock.
           Any number of complete buy/sell transactions may already have been
           performed. This is also the state returned as the final answer.

        2. max_net_worth:
           The maximum cash remaining after buying and currently holding one
           stock. Buying changes cash into cash - price, so this value can be
           negative. MIN means that no valid holding state exists yet.

        For a current price p, the transitions are:

            hold = max(previous_hold, previous_profit - p)
            profit = max(previous_profit, previous_hold + p - fee)

        The first transition means either keep holding the existing stock or
        buy today using the best cash from completed transactions.

        The second transition means either keep the previous cash or sell the
        held stock today and pay the transaction fee exactly once.

        Both transitions must use the states from before today. The snapshots
        below prevent a stock bought today from also being sold today and make
        each iteration represent a valid sequence of transactions.

        Every price is processed once, so the algorithm uses O(N) time and
        O(1) extra space.
    */

    long long max_net_worth = MIN;
    long long max_net_profit = 0;

    for (int price : prices) {
        const long long curr_net_worth = max_net_worth;
        const long long curr_net_profit = max_net_profit;

        /*
            Holding transition:
            keep the previous stock, or buy today's stock using the best
            available cash from completed transactions.
        */
        max_net_worth = std::max(
            curr_net_worth,
            curr_net_profit - price
        );

        /*
            Selling transition:
            keep the previous cash, or sell the previously held stock today.
            The fee is charged when the sale is completed.
        */
        max_net_profit = std::max(
            curr_net_profit,
            curr_net_worth + price - fee
        );
    }

    return max_net_profit;
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of days for stock price listing : ";
    std::cin >> size;

    std::vector<int> prices(size);
    std::cout << "\nKeep entering the prices : ";
    for (size_t i=0; i<size; i++)
        std::cin >> prices[i];

    int fee;
    std::cout << "\nEnter the fee : ";
    std::cin >> fee;

    const long long answer = solve(prices, fee);
    std::cout << "\nThe maximum possible earnable profit is : " << answer << "\n\n";

    return 0;
}