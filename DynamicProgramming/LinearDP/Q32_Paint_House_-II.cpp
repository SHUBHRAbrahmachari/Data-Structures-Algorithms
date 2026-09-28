/*
    Given a matrix mat[][] of shape (N, 3)
    N denotes the number of houses in positioned in a row.
    In each column we see cost to paint a particular house with 3 different colors.

    We need to paint each house with exactly one color but we also need to make sure that no more than K consecutive houses the have same color painted on them.
    Find the minimum cost to paint all those houses.

    1 <= N <= 10^5
    1 <= mat[i][0], mat[i][1], mat[i][2] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<long long>::max()/2


long long solve(const std::vector<std::vector<int>>& cost, const int k) {
    const int size = cost.size();

    if (size == 1)
        return std::min(cost[0][0], std::min(cost[0][1], cost[0][2]));

    /*
        Let us see how our DP state is going to look like:

        memory_red[i][t]: minimum possible cost to paint houses upto index i where house at index i has been painted with color item 0 as atmost t-th consecutive house.
        memory_blue[i][t]: minimum possible cost to paint houses upto index i where house at index i has been painted with color item 1 as atost t-th consecutive house.
        memory_green[i][t]: minimum possible cost to paint house upto index i where house at index i has been painted with color item 2 as atmost t-th consecutive house.
    */
    std::vector<std::vector<long long>> memory_red(
        size,
        std::vector<long long>(k+1, MAX)
    );

    std::vector<std::vector<long long>> memory_blue(
        size,
        std::vector<long long>(k+1, MAX)
    );

    std::vector<std::vector<long long>> memory_green(
        size,
        std::vector<long long>(k+1, MAX)
    );

    // base case initialization 
    for (int t=k; t>=0; t--) {
        // with atmost t=0! what does it mean?
        // i.e. we have not all applied the color we were supposed to paint
        // so we take the minimum cost of the other two possible options
        if (t == 0) {
            // we're not applying red color right? so we must take minimum of blue and green
            memory_red[0][t] = std::min(
                cost[0][1], cost[0][2]
            );

            // same idea
            memory_blue[0][t] = std::min(
                cost[0][0], cost[0][2]
            );

            // same idea
            memory_green[0][t] = std::min(
                cost[0][0], cost[0][1]
            );
        }

        else {
            // upto index 0, with atmost t(t>0) consecutive houses being painted with red-color is incuring cost of cost[0][0]
            memory_red[0][t] = cost[0][0];

            // upto index 0, with atmost t(t>0) consecutive houses being painted with blue-color is incuring cost of cost[0][1]
            memory_blue[0][t] = cost[0][1];

            // upto index 0, with atmost t(t>0) consecutive houses being painted with green-color i incuring cost of cost[0][2]
            memory_green[0][t] = cost[0][2];
        }
    }

    for (int i=1; i<size; i++) {
        // upto this index i, with atmost 0 consecutive houses being painted with red/blue/green what is the best cost?
        // we already know what does it mean!

        // exactly: what is the best cost by applying blue/green color atmost k times
        memory_red[i][0] = std::min(
            memory_blue[i][k], memory_green[i][k]
        );

        memory_blue[i][0] = std::min(
            memory_red[i][k], memory_green[i][k]
        );

        memory_green[i][0] = std::min(
            memory_blue[i][k], memory_blue[i][k]
        );

        for (int t=k; t>=1; t--) {
            /*
                Suppose i want to put red-color in this house!
                What are the possible options?

                1> i paint this house as red which will be atmost t-th house that is being painted as the red one
                2> i paint this house as red but the previous house was painted with blue color but does not matter for what consecutive time, we can easily consider k
                3> i paint this house as red but the previous house was painted with green color but does not matter for what consecutive time, we can easily consider k 
            */
            const long long prev_red_best = std::min(
                memory_red[i-1][t-1],
                std::min(
                    memory_blue[i-1][k],
                    memory_green[i-1][k]
                )
            );

            if (prev_red_best != MAX)
                memory_red[i][t] = prev_red_best + cost[i][0];

            const long long prev_blue_best = std::min(
                memory_blue[i-1][t-1],
                std::min(
                    memory_red[i-1][k],
                    memory_green[i-1][k]
                )
            );

            if (prev_blue_best != MAX)
                memory_blue[i][t] = prev_blue_best + cost[i][1];

            const long long prev_green_best = std::min(
                memory_green[i-1][t-1],
                std::min(
                    memory_red[i-1][k],
                    memory_blue[i-1][k]
                )
            );

            if (prev_green_best != MAX)
                memory_green[i][t] = prev_green_best + cost[i][2];
        } 
    }

    return std::min(
        memory_red[size-1][k],
        std::min(
            memory_blue[size-1][k], memory_green[size-1][k]
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the number of houses to paint : ";
    std::cin >> size;

    std::vector<std::vector<int>> cost(size, std::vector<int>(3));
    std::cout << "\nKeep entering the tree cost options to paint each house in rows : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    int k;
    std::cout << "\nEnter the maximum number of consecutive houses that can be painted with same color : ";
    std::cin >> k;

    const long long answer = solve(cost, k);
    std::cout << "\nThe minimum cost will be : " << answer << "\n\n";

    return 0;
}