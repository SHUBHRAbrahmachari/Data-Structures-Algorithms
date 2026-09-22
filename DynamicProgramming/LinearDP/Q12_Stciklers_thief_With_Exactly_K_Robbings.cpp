/*
    Given an array of positive integers representing wealth in each house.
    You are planning to rob the houses. But there are two conditions.

        1> You cannot rob two consecutive houses otherwise you'll get caught.
        2> You can rob exactly K houses.


    What is the maximum wealth you can collect?

    1 <= N <= 10^5
    1 <= K <= (N+1)/2       // maximum number of non-consecutive houses
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& houses, const int k) {
    const size_t size = houses.size();

    if (size == 1 and k == 1)
        return houses[0];

    // we cannot initialize with zero this time! we have to initialize with MIN
    std::vector<std::vector<long long>> memory_without_robbing(
        size,
        std::vector<long long>(k+1, MIN)
    );

    std::vector<std::vector<long long>> memory_with_robbing(
        size,
        std::vector<long long>(k+1, MIN)
    );

    for (int i=0; i<size; i++)
        memory_without_robbing[i][0] = 0;
        
    memory_with_robbing[0][1] = houses[0];


    for (int i=1; i<size; i++) {
        for (int t=k; t>=1; t--) {
            /*
                Suppose we decide not to make a theft tonight
            */
            memory_without_robbing[i][t] = std::max(
                (i > 0 ? memory_without_robbing[i-1][t] : 0),
                (i > 0 ? memory_with_robbing[i-1][t] : 0)
            );

            /*
                Suppose we decide to make a theft here
            */
            memory_with_robbing[i][t] = std::max(
                (i > 0 ? memory_without_robbing[i-1][t-1] : 0),
                (i > 1 ? memory_with_robbing[i-2][t-1] : 0)
            ) + houses[i];
        }
    }

    return std::max(
        memory_with_robbing[size-1][k],
        memory_without_robbing[size-1][k]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of houses : ";
    std::cin >> size;

    std::vector<int> houses(size);
    std::cout << "\nKeep entering the wealths of the houses : ";
    for (size_t i=0; i<size; i++)
        std::cin >> houses[i];

    int k;
    std::cout << "\nEnter the total number of houses to rob : ";
    std::cin >> k;

    const long long answer = solve(houses, k);
    std::cout << "\nThe maximum wealth we can collect would be : " << answer << "\n\n";

    return 0;
}