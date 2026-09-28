/*
    There are 3 types of buliding.
    The heights can be either 1, 2 or 3.
    You need to make N buildings such that no two consecutive buildings has absolute height  difference more than 1.

    Cost to make a certain type  of bulding at i-th position is given by cost[i][t]

    What is the minimum cost to build N buildings?

    1 <= N <= 10^5
    1 <= cost[i][0], cost[i][1], cost[i][2] <= 10^5 
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<std::vector<int>>& cost) {
    const int size = cost.size();

    if (size == 1)
        return std::min(cost[0][0], std::min(cost[0][1], cost[0][2]));

    long long min_0 = cost[0][0];
    long long min_1 = cost[0][1];
    long long min_2 = cost[0][2];

    for (int i=1; i<size; i++) {
        const long long curr_0 = min_0;
        const long long curr_1 = min_1;
        const long long curr_2 = min_2;

        min_0 = std::min(
            curr_0, curr_1
        ) + cost[i][0];

        min_1 = std::min(
            curr_1,
            std::min(curr_0, curr_2)
        ) + cost[i][1];

        min_2 = std::min(
            curr_1, curr_2
        ) + cost[i][2];
    }

    return std::min(min_0, std::min(min_1, min_2));
}

int main() {
    int size;
    std::cout << "\nEnter the number of buildings to make : ";
    std::cin >> size;

    std::vector<std::vector<int>> cost(size, std::vector<int>(3));
    std::cout << "\nKeep entering the costs for making each type of building at each position : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    const long long ans = solve(cost);

    std::cout << "\nThe minimum cost to build " << size << " buildings is : " << ans << std::endl;

    return 0;
}