/*
    We are supposed to transmit a signal at either Band B1 or Band B2 every minute.
    Costs to transmit the signal at i-th minute with B1 and B2 are respectively B1[i] and B2[i].
    If you switch between bands, you need to pay a switching cost of S.
    Band B2 cannot be used more than K consecutive minutes.

    What is the minimum cost to transmit the signal for N minutes?

    1 <= N <= 10^5
    1 <= B1[i], B2[i], S <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& b1, const std::vector<int>& b2, int s, int k){
    const int size = b1.size();

    if (size == 1)
        return std::min(b1[0], b2[0]);

    /*
        See that we do not have any restriction on B1 band right?
        The only restriction is on band B2 that we cannot use it consecutively for more than K minutes consecutively!
        Fine! Let us develop our DP memory state following that only!

        memory_b1[i]: upto i-th minute, what is the minimum cost to run the server if we have transmitted the signal with band B1 this minute.
        memory_b2[i][t]: upto i-th minute, what is the minimum cost to run the server if we have transmitted the signal with band B2 for atmost consecutive t-th time this minute?
    */
    long long curr_memory_b1 = b1[0], next_memory_b1;
    std::vector<long long> curr_memory_b2(k+1, b2[0]), next_memory_b2(k+1);
    curr_memory_b2[0] = b1[0] + s; // because when we call it from next_memory_b2[1] we must consider the penalty right?

    for (int i=1; i<size; i++) {
        // since B1 does not have necessary restriction, we can simply update that per day basis
        next_memory_b1 = std::min(
            curr_memory_b1,
            curr_memory_b2[k] + s
        ) + b1[i];

        for (int t=k; t>=0; t--) {

            // because we are not all using the B2 band to transmit the signal, neither in the previous minute, nor in this inute
            if (t == 0)
                next_memory_b2[t] = curr_memory_b1 + b1[i] + s;       // same logic why we are adding the penalty beforehand!
            
            else
                next_memory_b2[t] = std::min(
                    curr_memory_b2[t-1],
                    curr_memory_b1 + s
                ) + b2[i];
        }

        curr_memory_b1 = next_memory_b1;
        curr_memory_b2 = next_memory_b2;
    }

    return std::min(
        curr_memory_b1, curr_memory_b2[k]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of minutes to transmit the signal : ";
    std::cin >> size;

    std::vector<int> b1(size), b2(size);
    std::cout << "\nKeep entering the cost to transmit the signal at band B1 at each minute : ";
    for (int i = 0; i < size; i++)
        std::cin >> b1[i];

    std::cout << "\nKeep entering the cost to transmit the signal at band B2 at each minute : ";
    for (int i = 0; i < size; i++)
        std::cin >> b2[i];

    int s;
    std::cout << "\nEnter the band switching cost : ";
    std::cin >> s;

    int k;
    std::cout << "\nEnter the maximum number of consecutive minutes to use band B2 : ";
    std::cin >> k;

    const long long answer = solve(b1, b2, s, k);
    std::cout << "\nThe minimum cost to transmit the signal for " << size << " minutes is : " << answer;

    return 0;
}
