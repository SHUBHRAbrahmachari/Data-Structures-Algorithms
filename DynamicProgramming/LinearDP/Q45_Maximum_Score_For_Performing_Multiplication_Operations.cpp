/*
    You are given two arrays:
    nums of size N
    muls (multipliers) of size M (M <= N).
    You perform exactly M operations (one for each multiplier in muls).
    The RulesAt Step i (for i = 0, 1, ..., M-1):
        Look at the current nums array.
        You must choose either the first element (left end) OR the last element (right end).
        Let the chosen element be X .Gain Score: 
            Add X*muls[i] to your running score.
            Remove X: Delete that chosen element from nums so the array shrinks for the next step.
    
    Goal: Maximize total score after all M operations.

    suppose nums=[1 2 3 4 5], mul=[3 2]

    initally options are  1 and 5. Choose either.

    1> 1*3 + nums[2 3 4 5] + muls=[2]
    2> 5*3 + nums[1 2 3 4] + muls[2]

    Now continue in the same way!

    1 <= M <= N <= 10^5
    -100 <= muls[i], arr[i] <= 100

*/

#include <iostream>
#include <vector>

long long solve(
    const std::vector<int>& arr,
    const std::vector<int>& muls,
    std::vector<std::vector<long long>>& memory,
    const int st,
    const int en,
    const int i
) {
    if (st > en or i >= muls.size())
        return 0;

    if (memory[st][en] != -1)
        return memory[st][en];

    long long option1 = arr[st]*muls[i] + solve(arr, muls, memory, st+1, en, i+1);
    long long option2 = arr[en]*muls[i] + solve(arr, muls, memory, st, en-1, i+1);

    return memory[st][en] = std::max(
        option1, option2
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    int m;
    std::cout << "\nEnter the size of the mutipliers array : ";
    std::cin >> m;

    std::vector<int> muls(m);
    std::cout << "\nKeep entering the multipliers : \n\n";
    for (int i=0; i<m; i++)
        std::cin >> muls[i];

    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(size, -1)
    );

    const long long answer = solve(arr, muls, memory, 0, size-1, 0);
    std::cout << "\nThe maximum score would be : " << answer << "\n\n";

    return 0;
}
