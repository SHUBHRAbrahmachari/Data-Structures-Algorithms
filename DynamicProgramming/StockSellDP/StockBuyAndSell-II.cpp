/*
    Given an array of positive integers denoting the prices of a listed stcok in each day.
    You are a stock trader. You want to earn by buying and selling a stock.

    Although you can make atmost 1 transaction and with the completed transaction you must pay a transaction fees F.

    > you can only buy a stock when you don't already have a stock
    > you can only sell a stock when you already hold a stock
    > you can make atmost 1 transaction

    Another condition is that, you cannot buy the right next day of buying the stock.

    What is the maximum profit you can earn?

    2 <= N <= 10^7
    1 <= A[i] <= 10^5
    0 <= F <= 10^3
*/

#include <iostream>
#include <vector>

int solve(const std::vector<int>& prices, const int fee) {
    const size_t size = prices.size();

    /*
        A valid transaction needs at least one complete day between buying and
        selling. Therefore, if we sell on day d, the stock must have been
        bought on day d-2 or earlier. With fewer than three days, no legal
        buy/sell pair exists, so the best profit is zero.

        We scan the prices from left to right and maintain two values:

        1. min_buy_price:
           The cheapest price from all days that are old enough to be used for
           a sale on the current day.

        2. max_profit:
           The best completed transaction found so far, including the fee.
           It starts at zero because making no transaction is always allowed.

        For the current day d, the transition is:

            profit_if_sold_today = prices[d] - min_buy_price - fee
            max_profit = max(max_profit, profit_if_sold_today)

        After evaluating today's sale, add yesterday's price to the possible
        buy prices:

            min_buy_price = min(min_buy_price, prices[d - 1])

        This update order is essential. Yesterday becomes eligible for a sale
        tomorrow, but it must not be used to sell today; otherwise the required
        one-day gap between buying and selling would be violated.

        Every price is processed once, so the algorithm uses O(N) time and
        O(1) extra space.
    */
    if (size < 3)
        return 0;

    int min_buy_price = prices[0];
    int max_profit = 0;

    /*
        Start at index 2 because this is the first day on which a sale is
        possible: a purchase on index 0 leaves index 1 as the required gap day.
    */
    for (size_t day=2; day<size; day++) {
        const int curr_price = prices[day];
        const int prev_price = prices[day-1];

        /*
            Try selling today. At this moment min_buy_price contains only
            prices through day-2, so the cooldown restriction is respected.
        */
        max_profit = std::max(
            max_profit,
            curr_price - min_buy_price -fee
        );

        /*
            Make yesterday's price available for future sales. It cannot be
            used by the sale just evaluated because this update comes second.
        */
        min_buy_price = std::min(
            min_buy_price,
            prev_price
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
    std::cout << "\nEnter the transaction fees : ";
    std::cin >> fee;

    const int answer = solve(prices, fee);
    std::cout << "\nThe maximum earnable profit is : " << answer << "\n\n";

    return 0;
}