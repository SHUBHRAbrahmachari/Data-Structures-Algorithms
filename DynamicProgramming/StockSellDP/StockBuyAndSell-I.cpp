/*
    Given an array of positive integers denoting the prices of a listed stcok in each day.
    You are a stock trader. You want to earn by buying and selling a stock.

    Although you can make atmost 1 transaction and with the completed transaction you must pay a transaction fees F.

    > you can only buy a stock when you don't already have a stock
    > you can only sell a stock when you already hold a stock
    > you can make atmost 1 transaction

    What is the maximum profit you can earn?

    2 <= N <= 10^7
    1 <= A[i] <= 10^5
    0 <= F <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<int>::max()/2

int solve(const std::vector<int>& prices, const int fee) {
    /*
        We are allowed to complete at most one transaction: buy once and sell
        once. The answer is allowed to be zero, which means that making no
        transaction is better than accepting a loss.

        Instead of storing every possible buy/sell pair, maintain two pieces
        of information while scanning the days from left to right:

        1. min_buy_price:
           The cheapest price seen on an earlier day. This is the best price
           at which a transaction could have been started before today.

        2. max_profit:
           The best completed transaction found up to the days processed so
           far, after subtracting the transaction fee.

        For a current price p, the transition for selling today is:

            profit_if_sold_today = p - min_buy_price - fee
            max_profit = max(max_profit, profit_if_sold_today)

        After considering a sale today, update the buy state:

            min_buy_price = min(min_buy_price, p)

        The order matters. The sale transition uses only prices from earlier
        days, and the buy update is performed afterward, so the algorithm
        cannot buy and sell on the same day.

        Each day is processed once, giving O(N) time and O(1) extra space.
    */
    int max_profit = 0;
    int min_buy_price = MAX;

    for (int price : prices) {
        /*
            Try completing the one allowed transaction today. The cheapest
            earlier buy produces the highest possible profit for this price.
        */
        max_profit = std::max(
            price - min_buy_price - fee,
            max_profit
        );

        /*
            Keep today's price as a possible future buying price only if it is
            lower than every price seen before it.
        */
        min_buy_price = std::min(
            min_buy_price,
            price
        );
    }

    return max_profit;
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of days for stock price listing : ";
    std::cin >> size;

    std::vector<int> prices(size);
    std::cout << "\nKeep entering the listed stock prices : ";
    for (size_t i=0; i<size; i++)
        std::cin >> prices[i];

    int fee;
    std::cout << "\nEnter the transaction fee : ";
    std::cin >> fee;

    const int answer = solve(prices, fee);
    std::cout << "\nThe maximum profit will be : " << answer << "\n\n";

    return 0;
}