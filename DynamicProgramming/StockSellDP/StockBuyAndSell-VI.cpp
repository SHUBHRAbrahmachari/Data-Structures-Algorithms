/*
    Given the price of a stock on each day, find the maximum profit obtainable
    by making any number of buy/sell transactions.

    Rules:
    - We may buy only when we are not already holding a stock.
    - We may sell only when we are holding a stock.
    - We pay the transaction fee F whenever we sell.
    - We are allowed to make atmost K transactions only
    - We cannot sell the stock the right next day of buying it or buy it right next day of selling it. That day is counted as a "cooldown day"

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
    const int size = prices.size();

    if (size < 3)
        return 0;

    /*
        Let us define our DP states now:

            memory_worth[d][t]:
                maximum possible net worth we could be having at the end of day d and atmost t-th transaction being initiated

            memory_profit[d][t]:
                maximum possible net profit we could be having at the end of day d and atmost t-th transaction being completed
    */

    std::vector<std::vector<long long>> memory_worth(
        size,
        std::vector<long long>(
            k+1, MIN
        )
    );

    std::vector<std::vector<long long>> memory_profit(
        size,
        std::vector<long long>(
            k+1, 0
        )
    );

    // at the end of day 0, with any t-th transaction being intiated, maximum possible net worth is always -prices[0]
    for (int t=k; t>=1; t--)
        memory_worth[0][t] = -prices[0];

    for (int day=1; day<size; day++) {
        const int price = prices[day];
        for (int t=k; t>=1; t--) {
            /*
                Suppose i am hoding a stock today!
                What could be the best possible net worth today?

                1> i was already holding a stock yesterday while initiating atmost t-th transaction, so keep holding the stock today as well
                2> i was not holding a stock after atmost (t-1) successful transactions the day before yesterday, so i buy the stock today to initiate atmost t-th transaction
            */
            memory_worth[day][t] = std::max(
                memory_worth[day-1][t],
                (day > 1? memory_profit[day-2][t-1] : 0LL) - price
            );

            /*
                Suppose i am not holding a stock today!
                what could be the best possible net profit i could be having?

                1> i was already not holding a stock yesterday with atmost t-th transaction being completed, so i continue with that
                2> i intiated atmost t-th transaction the day before yesterday, so i sell it today to complete t-th transaction
            */
            memory_profit[day][t] = std::max(
                memory_profit[day-1][t],
                (day > 1? memory_worth[day-2][t] : MIN) + price - fee
            );
        }
    }

    return memory_profit[size-1][k];
}

int main() {
    int size;
    std::cout << "\nEnter the number of days for stock price listing : ";
    std::cin >> size;

    std::vector<int> prices(size);
    std::cout << "\nKeep entering the stock prices : ";
    for (int i=0; i<size; i++)
        std::cin >> prices[i];

    int fee;
    std::cout << "\nEnter the transaction fee : ";
    std::cin >> fee;

    int k;
    std::cout << "\nEnter the maximum number of transactions to be done : ";
    std::cin >> k;

    const long long answer = solve(prices, k, fee);
    std::cout << "\nThe maximum possible earning would be : " << answer << "\n\n";

    return 0;
}