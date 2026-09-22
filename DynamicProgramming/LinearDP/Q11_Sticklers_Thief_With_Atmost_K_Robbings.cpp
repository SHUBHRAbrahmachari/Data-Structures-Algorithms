/*
    Given an array of positive integers representing wealth in each house.
    You are planning to rob the houses. But there are two conditions.

        1> You cannot rob two consecutive houses otherwise you'll get caught.
        2> You can rob at most K houses.


    What is the maximum wealth you can collect?

    1 <= N <= 10^5
    1 <= K <= (N+1)/2       // maximum number of non-consecutive houses
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& houses, const int k) {
    const int size = houses.size();

    // With positive wealth, robbing the only house is always optimal here.
    if (size == 1 and k == 1)
        return houses[0];

    /*
        The second dimension is a robbery limit. A state may use fewer than t
        robberies because this is an "at most k" problem.

        memory_with_robbing[i][t]:
            Maximum wealth from houses [0..i], using at most t robberies, where
            house i is robbed.

        memory_without_robbing[i][t]:
            Maximum wealth from houses [0..i], using at most t robberies, where
            house i is not robbed.

        Every state for t=0 is zero because wealth is positive and robbing no
        houses gives wealth zero. Zero initialization also lets a state carry
        forward a solution that uses fewer than t robberies, which is valid.
    */
    std::vector<std::vector<long long>> memory_with_robbing(
        size,
        std::vector<long long>(k+1)
    );

    std::vector<std::vector<long long>> memory_without_robbing(
        size,
        std::vector<long long>(k+1)
    );

    for (int i=0; i<size; i++) {
        // t=0 is already represented by the zero-initialized DP rows.
        for (int t=k; t>=1; t--) {
            /*
                Do not rob house i.

                The previous house may or may not have been robbed, so take the
                better of both states from i-1. The robbery count remains t.
            */
            memory_without_robbing[i][t] = std::max(
                (i > 0 ? memory_without_robbing[i-1][t] : 0),
                (i > 0 ? memory_with_robbing[i-1][t] : 0)
            );

            /*
                Rob house i while using a limit of t robberies.

                    To avoid consecutive robberies, house i-1 must not be robbed.
                    Therefore, the previous valid position is either:
                        - i-1 in the without-robbing state, or
                        - i-2 in the with-robbing state.

                    Add the wealth of house i after choosing the better option.
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


