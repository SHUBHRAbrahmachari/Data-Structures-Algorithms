/*
    Given a matrix mat[][] of shape (N, 3)
    N denotes the number of houses in row.
    In each column we see cost to paint a particular house with 3 different colors.

    We need to paint each house with exactly one color but we also need to make sure that two consecutive houses do not have same colors painted on them.
    Find the minimum cost to paint all those houses.

    1 <= N <= 10^5
    1 <= mat[i][0], mat[i][1], mat[i][2] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<std::vector<int>>& cost) {
    const int size = cost.size();

    /*
        Let us define our DP state first.
        memory[i]: minimum cost upto any index where we decide to pain this house at index i with paint-type i 
    */

    std::vector<long long> curr(3);
    std::vector<long long> next(3);

    for (int i=0; i<size; i++) {
        next[0] = std::min(
            curr[1], curr[2]
        ) + cost[i][0];

        next[1] = std::min(
            curr[0], curr[2]
        ) + cost[i][1];

        next[2] = std::min(
            curr[0], curr[1]
        ) + cost[i][2];

        curr = next;
    }

    return std::min(curr[0], std::min(curr[1], curr[2]));
}

int main() {
    int size;
    std::cout << "\nEnter the number of houses to paint : ";
    std::cin >> size;

    std::vector<std::vector<int>> cost(size, std::vector<int>(3));
    std::cout << "\nKeep entering the tree cost options to paint each house in rows : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    const long long answer = solve(cost);
    std::cout << "\nThe minimum cost will be : " << answer << "\n\n";

    return 0;
}