/*
    Given an array of integers representing cost to jump from each index.
    You can either jump to next index or to next of next index only.

    You have to reach the last index starting from index 0. Once you reach the last index you count that as the cost too.
    Find the minimum posssible cost to reach the last index

    1 <= N <= 10^5
    1 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& costs) {
    const int size = costs.size();

    if (size == 1)
        return costs[0];

    std::vector<long long> memory(size);
    memory[size-1] = costs[size-1];
    memory[size-2] = costs[size-2] + costs[size-1];

    for (int i=size-3; i>=0; i--) {
        memory[i] = std::min(
            memory[i+1], memory[i+2]
        ) + costs[i];
    }

    return memory[0];
}

int main() {
    int size;
    std::cout << "\nEnter how many steps are there : ";
    std::cin >> size;

    std::vector<int> costs(size);
    std::cout << "\nKeep entering the costs to reach the last index : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> costs[i];

    const long long answer = solve(costs);
    std::cout << "\nThe minimum cost would be : " << answer << "\n\n";
    
    return 0;
}

