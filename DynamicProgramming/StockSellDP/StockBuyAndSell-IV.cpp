/*
        Given the price of a stock on each day, find the maximum profit obtainable
        by making any number of buy/sell transactions.

        Rules:
        - We may buy only when we are not already holding a stock.
        - We may sell only when we are holding a stock.
        - We pay the transaction fee F whenever we sell.
        - After buying, we must hold the stock for at least one complete day before
            selling it. Therefore, a stock bought on day d can first be sold on day d + 2.
        - After selling, the following day is a cooldown day. We may buy again only
            from day d + 2 when the sale happened on day d.

        The answer must respect both cooldown rules while allowing multiple
        transactions.

        Constraints:
        2 <= N <= 10^7
        1 <= A[i] <= 10^9
        0 <= F <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>

/*
    A very small sentinel represents an impossible profit. Dividing the
    minimum value by two leaves enough room for the arithmetic performed when
    a price and a fee are added to it.
*/
#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<long long>& prices, const long long fee) {
    const size_t size = prices.size();

    /*
        A transaction needs at least three days: one day to buy, one mandatory
        cooldown day, and one day to sell.
    */
    if (size < 3)
        return 0;

    /*
        We use two DP arrays. For every day d:

        max_net_worths[d] is the greatest value of our money and stock position
        at the end of day d while still holding one stock. Since buying costs
        price[d], this value is normally negative.

        max_net_profits[d] is the greatest realized profit at the end of day d
        when we are not holding a stock. It includes the possibility that we
        sold on day d.

        We look back to day d - 2 when starting a new action. This skips the
        day immediately after the previous buy or sell, which is the required
        cooldown day. Looking back only one day would incorrectly allow an
        immediate sell or re-buy.
    */
    std::vector<long long> max_net_worths(size);
    std::vector<long long> max_net_profits(size);

    /*
        On day 0, the only possible way to hold a stock is to buy it that day.
        No sale is possible yet because selling the next day is forbidden.
    */
    max_net_worths[0] = -prices[0];

    for (size_t day=1; day<size; day++) {
        const long long price = prices[day];

        /*
            To be holding a stock at the end of today, we either:
            1. Continue holding the stock we already had yesterday, or
            2. Buy today using the best profit available two days ago.

            The second option is allowed to use zero when day == 1 because
            buying the stock for the first time is always possible. It cannot
            produce a profit yet because selling tomorrow is forbidden.
        */
        max_net_worths[day] = std::max(
            max_net_worths[day-1],
            (day > 1 ? max_net_profits[day-2] : 0) - price
        );

        /*
            To be without a stock at the end of today, we either:
            1. Keep the best profit we already had yesterday, or
            2. Sell today a stock held two days ago and subtract the fee.

            Using max_net_worths[day - 2] guarantees that the stock was not
            bought yesterday, so selling today obeys the mandatory holding day.
            The MIN sentinel prevents an impossible sale on day 1.
        */
        max_net_profits[day] = std::max(
            max_net_profits[day-1],
            (day > 1 ? max_net_worths[day-2] : MIN) + price - fee
        );
    }

    return max_net_profits[size-1];
}

int main() {
    size_t size;
    /* Read the number of trading days and then the price for each day. */
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<long long> prices(size);
    std::cout << "\nKeep entering the prices : ";
    for (size_t i=0; i<size; i++)
        std::cin >> prices[i];

    long long fee;
    /* The fee is charged once for every completed sell transaction. */
    std::cout << "\nEnter the fee : ";
    std::cin >> fee;

    const long long answer = solve(prices, fee);
    std::cout << "\nThe maximum possible earnable profit is : " << answer << "\n\n";

    return 0;
}