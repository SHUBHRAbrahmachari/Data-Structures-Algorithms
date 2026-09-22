/*
    Given an array of positive integers repersenting wealth in each house. Houses are arranged in a circular manner.
    You are planning to rob the houses. But there is a condition.

    You cannot rob two consecutive houses otherwise you'll get caught.

    What is the maximum wealth you can collect?

    1 <= N <= 10^5
    1 <= A[i] <= 10^5
*/

/*
    You must have been thinking of appending the array to itself to introduce cycle nature.
    And then run a loop to solve standard Stockler's Thief from indices o to N-1.

    Nice! But that would cost O(N^2)! We have a better approach.

    See what is the rule? No two consecutive houses can be robbed right?
    Since houses are arrnaged ina cicular manner, so now index 0 and N-1 are now adjacent.

    If you rob house at index 0, you cannot rob house at index N-1
    If you rob house at index N-1, you cannot rob index 0.

    So, basically if you consider index 0, you can never consider index N-1,
    If you consider index N-1, you  can never consider index 0

    Thereby, our circular theft reduces to two simple subproblems:

    max(
        stickler's thief[0.... N-2],
        stickler's thief[1.....N-1]
    )

    Simple O(N) approach!
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int> houses) {
    const int size = houses.size();

    if (size == 1)
        return houses[0];

    std::vector<long long> memory_without_robbing(size);
    std::vector<long long> memory_with_robbing(size);

    memory_without_robbing[0] = 0;
    memory_with_robbing[0] = houses[0];

    for (int i=1; i<size; i++) {
        memory_without_robbing[i] = std::max(
            memory_without_robbing[i-1],
            memory_with_robbing[i-1]
        );

        memory_with_robbing[i] = std::max(
            memory_without_robbing[i-1],
            (i > 1 ? memory_with_robbing[i-2] : 0)
        ) + houses[i];
    }

    return std::max(
        memory_with_robbing[size-1],
        memory_without_robbing[size-1]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of houses : ";
    std::cin >> size;

    std::vector<int> houses(size);
    std::cout << "\nKeep entering the wealth in those respective houses : ";
    for (int i=0; i<size; i++)
        std::cin >> houses[i];

    // otherwise code would crash at solve() method
    if (size == 1) {
        std::cout << "\nThe maximum possible collection would be : " << houses[0] << "\n\n";
        std::exit(0);
    }

    const long long answer = std::max(
        solve(std::vector<int>(houses.begin(), houses.end()-1)),
        solve(std::vector<int>(houses.begin()+1, houses.end()))
    );

    std::cout << "\nThe maximum possible collection would be : " << answer << "\n\n";

    return 0;   
}