/*
    You are given a set of questions.
    If you attempt q[i] you earn p[i] points but you cannot attempt next c[i] questions.
    What is the maximum points you can earn?

    1 <= N <= 10^5
    1 <= p[i] <= 10^5
    1 <= c[i] <= 10^3
*/

#include <iostream>
#include <vector>

long long solve_memoization(
    const std::vector<int>& p,
    const std::vector<int>& c,
    std::vector<long long>& memory,
    int curr=0
) {
    if (curr >= p.size())
        return 0;

    if (memory[curr] != -1)
        return memory[curr];

    long long option1 = solve_memoization(p, c, memory, curr+1);
    long long option2 = p[curr] + solve_memoization(p, c, memory, curr+c[curr]+1);

    return memory[curr] = std::max(
        option1, option2
    );
}

// to call memoization helper
long long solve(const std::vector<int>& p, const std::vector<int>& c) {
    std::vector<long long> memory(
        p.size(), -1
    );

    return solve_memoization(p, c, memory);
}

long long solve_tabulation(const std::vector<int>& p, const std::vector<int>& c) {
    const int size = p.size();

    std::vector<long long> memory(
        size, -1
    );

    // step 1> reverse the loop of memoization
    for (int i=size-1; i>=0; i--) {
        // step2 > simply copy the same recurrence
        long long option1 = (i+1 < size) ? memory[i+1] : 0;
        long long option2 = p[i] + ((i + c[i] + 1 < size) ? memory[i+c[i]+1] : 0);

        memory[i] = std::max(option1, option2);
    }

    return memory[0];
}

int main() {
    int size;
    std::cout << "\nEnter the number of questions : ";
    std::cin >> size;

    std::vector<int> p(size);
    std::cout << "\nKeep entering the points for each question : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> p[i];

    std::vector<int> c(size);
    std::cout << "\nKeep entering how many questions we cannot attempt further after attempting that : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> c[i];

    // solved by observing the Memoization approach!
    const long long answer = solve_tabulation(p, c);
    std::cout << "\nThe maximum earnable points would be : " << answer << "\n\n";
    
    return 0;
}