/*
    Given two postive integer arrays of same size.

    L[i]: unit power required to run the server in low power for i-th minute
    H[i]: unit power required to run the server in high power for i-th minute

    you cannot run the server in high power for 2 consecutive minutes.

    If you need to keep the server running for N consecutive minutes,
    What is the minimum power consumption you can achieve?

    1 <= N <= 10^5
    1 <= L[i], H[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(
    const std::vector<int>& h,
    const std::vector<int>& l
) {
    const int size = l.size();

    if (size == 1)
        return std::min(
            l[0], h[0]
        );

    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(2, -1)
    );

    memory[0][0] = l[0];
    memory[0][1] = h[0];

    for (int i=1; i<size; i++) {
        // for low effort
        memory[i][0] = std::min(
            memory[i-1][0], memory[i-1][1]
        ) + l[i];

        // for high effort
        memory[i][1] = memory[i-1][0] + h[i];
    }

    return std::min(
        memory[size-1][0], memory[size-1][1]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the number of minutes : ";
    std::cin >> size;

    std::vector<int> l(size), h(size);
    std::cout << "\nEnter the power consumptions for low effort : ";
    for (int i=0; i<size; i++)
        std::cin >> l[i];

    std::cout << "\nEnter the power consumptions for high effort : ";
    for (int i=0; i<size; i++)
        std::cin >> h[i];

    const long long answer = solve(h, l);
    std::cout << "\nThe mainimum possible power consumption would be : " << answer << "\n\n";

    return 0;
}