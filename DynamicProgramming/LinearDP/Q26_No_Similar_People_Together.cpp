/*
    Given a matrix with N rows and 3 columns.
    Every row has 3 element options to pick, not necessarily unique.

    No two consecutive selected elements must match.

    Find the minimum possible sum of collected elements!

    1 <= N <= 10^5
    1 <= mat[i][c] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<long long>::max()/2

long long find(
    const std::vector<std::vector<long long>>& mat,
    const std::vector<long long>& memory,
    const int index,
    const long long exclude
) {
    long long minimum = MAX;

    for (int i=0; i<3; i++) {
        if (mat[index][i] != exclude)
            minimum = std::min(
                minimum,
                memory[i]
            );
    }

    return minimum;
}

long long solve(const std::vector<std::vector<long long>>& mat) {
    const int size = mat.size();

    /*
        Let us define our DP states next:
            memory[i]: minimum possible sum upto any index considering last element that was considered belongs to index i
    */
    std::vector<long long> memory(3);
    memory[0] = mat[0][0];
    memory[1] = mat[0][1];
    memory[2] = mat[0][2];

    for (int i=1; i<size; i++) {
        long long candidate0 = find(mat, memory, i-1, mat[i][0]);
        long long candidate1 = find(mat, memory, i-1, mat[i][1]);
        long long candidate2 = find(mat, memory, i-1, mat[i][2]);

        memory[0] = candidate0 + mat[i][0];
        memory[1] = candidate1 + mat[i][1];
        memory[2] = candidate2 + mat[i][2];
    }

    return std::min(
        memory[0],
        std::min(
            memory[1],
            memory[2]
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the number of rows : ";
    std::cin >> size;

    std::vector<std::vector<long long>> mat(
        size,
        std::vector<long long>(3)
    );

    std::cout << "\nKeep entering the 3 choices for each row : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> mat[i][0] >> mat[i][1] >> mat[i][2];

    const long long answer = solve(mat);

    if (answer >= MAX)
        std::cout << "\nYou won't be able to make a sequence anyway!\n\n";
    else
        std::cout << "\nThe minimum sum would be : " << answer << "\n\n";

    return 0;
}