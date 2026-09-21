/*
    Given an array of positive integers repersenting wealth in each house.
    You are planning to rob the houses. But there is a condition.

    You cannot rob two consecutive houses otherwise you'll get caught.

    What is the maximum wealth you can collect?

    1 <= N <= 10^5
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& houses) {
    const int size = houses.size();

    if (size == 1)
        return houses[0];

    /*
        What is the idea? let us create two vectors to store best memory over conditions

        memory_with_robbing[i]: maximum possible collected wealth if i have robbed the house at index i last
        memory_without_robbing[i]: maximum possible collected weatlth if i have not robbed house at index i last
    */
    std::vector<long long> memory_with_robbing(size);
    std::vector<long long> memory_without_robbing(size);

    for (int i=0; i<size; i++) {
        /*
            If we're willing to rob this house,
                option 1> either skip the previous and see the maximum collectable wealth upto that previous house without robbing it
                option 2> see what was the best collectable wealth after robbing last house at inde i-2 (since 1 house gap is required)
        */
        memory_with_robbing[i] = std::max(
            (i > 0 ? memory_without_robbing[i-1] : 0),
            (i > 1 ? memory_with_robbing[i-2] : 0)
        ) + houses[i];

        /*
            If we're willing to not rob this house,

                option 1> see what was the best after not robbing house at index i-1
                option 2> see what was the best after robbing house at index i-1
        */
        memory_without_robbing[i] = std::max(
            (i > 0 ? memory_without_robbing[i-1] : 0),
            (i > 0 ? memory_with_robbing[i-1] : 0)
        );
    }

    return std::max(
        memory_with_robbing[size-1],
        memory_without_robbing[size-1]
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of houses : ";
    std::cin >> size;

    std::vector<int> houses(size);
    std::cout << "\nKeep entering the wealth in each house : ";
    for (size_t i=0; i<size; i++)
        std::cin >> houses[i];

    const long long answer = solve(houses);
    std::cout << "\nThe maximum collectable wealth is : " << answer << "\n\n";
    
    return 0;
}