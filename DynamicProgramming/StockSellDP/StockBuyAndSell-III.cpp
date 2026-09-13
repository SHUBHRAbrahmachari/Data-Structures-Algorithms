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
        We'll maintain two running varibales here:

        1> max_net_profit: maximum possible net profit at the end of day any day with as many as possible completed transactions
        2> max_net_worth: maximum possible net worth at the end of any day with as many as possible completed transactions
    */   

    long long max_net_worth = MIN;
    long long max_net_profit = 0;

    for (int price : prices) {
        const long long curr_net_worth = max_net_worth;
        const long long curr_net_profit = max_net_profit;

        // update maximum net worth if we were to buy the stock today. Should we?
        max_net_worth = std::max(
            curr_net_worth,
            curr_net_profit - price
        );

        // update maximum net profit if we were to sell the stock today. Should we?
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