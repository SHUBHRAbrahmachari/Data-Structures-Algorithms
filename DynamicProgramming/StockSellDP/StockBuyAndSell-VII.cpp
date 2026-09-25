/*
    Given the price of a stock on each day, find the maximum profit obtainable
    by making any number of buy/sell transactions.

    Rules:
    - We may buy only when we are not already holding a stock.
    - We may sell only when we are holding a stock.
    - We pay the transaction fee F whenever we sell.
    - We are allowed to make EXACTLY K transactions only
    - We cannot sell the stock the right next day of buying it or buy it right next day of selling it. That day is counted as a "cooldown day"

    Constraints:
        2 <= N <= 10^7
        1 <= A[i] <= 10^9
        1 <= K <= floor(N/4)
        0 <= F <= 10^3
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& prices, const int k, const int fee) {
    const int size = prices.size();

    /*
        We need to tweak our DP states again!

            memory_worth[d][t]:
                maximum possible net worth at the end of day d with exactly t-th transaction being initiated

            memory_profit[d][t]:
                maximum possible net worth at the end of day d with exactly t-th transaction being completed
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
            k+1, MIN
        )
    );

    // at the end of day 0, only with 1st transaction being initiated maximum net worth can be -prices[0]
    memory_worth[0][1] = -prices[0];

    // at the end of any day, with 0 complete transactions, maximum profit is always 0
    for (int day=0; day<size; day++)
        memory_profit[day][0] = 0;

    for (int day=1; day<size; day++) {
        const int price = prices[day];

        for (int t=k; t>=1; t--) {
            /*
                Case 1>
                    Suppose i am holding a stock today while exactly t-th transaction being initiated.
                    What could be the maximum possible net worth?

                    1> i was holding the stock yesterday as well with exactlt t-th transaction being initiated
                    2> i was not holding the stock day before yesterday with exactly (t-1) transactions being completed, so i buy today
            */

            // case 1A: there's no option to look for best previous profit
            if (day == 1) {
                // Special case for t = 1 on Day 1: we can buy today as prior profit is 0
                if (t == 1)
                    memory_worth[day][t] = std::max(memory_worth[day-1][t], (long long)-price);

                else
                    memory_worth[day][t] = memory_worth[day-1][t];
            }

            // case 1B: there is a chance that we can get best previuous profit
            else {
                if (memory_worth[day-1][t] != MIN and memory_profit[day-2][t-1] == MIN)
                    memory_worth[day][t] = memory_worth[day-1][t];

                else if (memory_worth[day-1][t] == MIN and memory_profit[day-2][t-1] != MIN)
                    memory_worth[day][t] = memory_profit[day-2][t-1] - price;
                
                else if (memory_worth[day-1][t] != MIN and memory_profit[day-2][t-1] != MIN)
                    memory_worth[day][t] = std::max(
                        memory_worth[day-1][t],
                        memory_profit[day-2][t-1] - price
                    );
            }

            /*
                Case 2>
                    Suppose i am not holding a stock today while exactly t-th transaction being initiated.
                    What could be the maximum possible net profit?

                    1> i was not holding the stock yesterday as well with exactlt t transactions completed
                    2> i was holding the stock day before yesterday with exactly t-th transactions being initiated, so i sell today
            */
            
            // case 2A: there's no way to look for previous best worth
            if (day == 1)
                memory_profit[day][t] = memory_profit[day-1][t];

            // case 2B: there's a way we can look for previous best worth
            else {
                if (memory_worth[day-2][t] != MIN and memory_profit[day-1][t] == MIN)
                    memory_profit[day][t] = memory_worth[day-2][t] + price - fee;
                
                else if (memory_worth[day-2][t] == MIN and memory_profit[day-1][t] != MIN)
                    memory_profit[day][t] = memory_profit[day-1][t];

                else if (memory_worth[day-2][t] != MIN and memory_profit[day-1][t] != MIN)
                    memory_profit[day][t] = std::max(
                        memory_profit[day-1][t],
                        memory_worth[day-2][t] + price - fee
                    );
            }
        }
    }

    return memory_profit[size-1][k];
}

int main() {
    int size;
    std::cout << "\nEnter the total number of days for stock price listing : ";
    std::cin >> size;

    std::vector<int> prices(size);
    std::cout << "\nKeep entering the listed prices : ";
    for (int i=0; i<size; i++)
        std::cin >> prices[i];

    int fee;
    std::cout << "\nEnter the transaction fee : ";
    std::cin >> fee;

    int k;
    std::cout << "\nEnter the total number of transactions to make : ";
    std::cin >> k;

    const long long answer = solve(prices, k, fee);
    if (answer == MIN)
        std::cout << "\nYou cannot make exactly " << k << " transactions \n\n";
    else
        std::cout << "\nThe maximum profit would be : " << answer << "\n\n";

    return 0;
}
