/*
    We have 3 types of servers.
    cost[i][0]: cost to run the task on server A for i-th minute
    cost[i][1]: cost to run the task on server B for i-th minute
    cost[i][2]: cost to run the task on server C for i-th minute

    If we use the server at i-th minute and switch to another server for (i+1)-th minute,
    We are required to pay a penalty of p.

    What is the the minimum cost to run the task for N minutes?

    1 <= cost[i][0], cost[i][1], cost[i][2] <= 10^5
    1 <= p <= 10^3
*/

#include <iostream>
#include <vector>

const long long solve(const std::vector<std::vector<int>>& cost, const int p) {
    const int size = cost.size();

    if (size == 1)
        return std::min(cost[0][0], std::min(cost[0][1], cost[0][2]));

    /*
        Let us define the DP states:

        memory_A: minimum cost to run the task upto any minute i where we run the task on server A for i-th minute
        memory_A: minimum cost to run the task upto any minute i where we run the task on server B for i-th minute
        memory_A: minimum cost to run the task upto any minute i where we run the task on server C for i-th minute
    */

    long long min_memory_A = cost[0][0];
    long long min_memory_B = cost[0][1];
    long long min_memory_C = cost[0][2];
    
    for (int i=1; i<size; i++) {
        const long long curr_memory_A = min_memory_A;
        const long long curr_memory_B = min_memory_B;
        const long long curr_memory_C = min_memory_C;

        // suppose we want to run this task on server A this minute
        min_memory_A = std::min(
            curr_memory_A,
            std::min(
                curr_memory_B,
                curr_memory_C
            ) + p
        ) + cost[i][0];

        // suppose we want to run this task on server B this minute
        min_memory_B = std::min(
            curr_memory_B,
            std::min(
                curr_memory_A,
                curr_memory_C
            ) + p
        ) + cost[i][1];

        // suppose we want to run this task on server C this minute
        min_memory_C = std::min(
            curr_memory_C,
            std::min(
                curr_memory_A,
                curr_memory_B
            ) + p
        ) + cost[i][2];
    }

    return std::min(
        min_memory_A,
        std::min(
            min_memory_B, min_memory_C
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of minutes to run the task : ";
    std::cin >> size;

    std::vector<std::vector<int>> cost(
        size,
        std::vector<int>(3)
    );

    std::cout << "\nKeep entering the costs to run the task on each server for every minute : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    int p;
    std::cout << "\nEnter the penalty for server switch : ";
    std::cin >> p;

    const long long answer = solve(cost, p);
    std::cout << "\nMinimum cost will be : " << answer << "\n\n";

    return 0;
}