/*
    A runner is attempting a marathon.
    Every minute the runner can take either of these 3 decisons.

        1> runner can sprint at i-th minute. But doing that he loses s[i] energy but covers S distance
        2> runner can jog at i-th minute. But doing that he loses j[i] energy but covers J distance
        3> runner can rest at i-th minute. Doing that he gains r[i] energy and covers 0 distance.

    if a decison makes his energy < 0, he cannot take that decison as well.
    What is the maximum distance he can cover in that N minutes. The runner starts with initial energy K, and maximum energy can be K as well.

    1 <= |s[]| = |j[]| = |r[]| <= 10^5
    1 <= s[i], j[i], r[i] <= K <= 10^5
    1 <= J < S <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>

long long solve(
    const std::vector<int>& s,
    const std::vector<int>& j,
    const std::vector<int>& r,
    const int s_dis,
    const int j_dis,
    const int energy
) {
    const int size = s.size();

    /*
        What is going to be our DP state?

        memory[i][e]: with remaining energy e, what is the maximum distance the runner could cover upto i-th minute?
    */
    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(energy+1, -1)
    );

    // upto 0-th minute if we're at same energy, we must have rested that minute
    memory[0][energy] = 0;

    // in case jogging and sprinting requires same energy at 0-th minute
    if (j[0] == s[0] and energy >= j[0])
        memory[0][energy-j[0]] = std::max(
            s_dis, j_dis
        );
    
    // otherwise we need to set them differently 
    else {
        memory[0][energy-j[0]] = j_dis;
        memory[0][energy-s[0]] = s_dis;
    }

    for (int i=1; i<size; i++) {
        for (int e=energy; e>=0; e--) {
            // we just need to think, what were the ways that we could reach at this energy level!

            /*
                From which energy levels can we reach energy level e by resting?
                Any valid energy state starting from e >= r[i] right?
            */
            long long option1 = -1;
            if (e >= r[i]) {
                for (int start = e-r[i]; start <= std::min(e, energy); start++)
                    option1 = std::max(
                        option1,
                        memory[i-1][start]
                    );
            }

            /*
                From which energy levels can we reach energy level e by jogging?
                We must have been in energy level e+j[i] to cut j[i] energy right? that means e+j[i] <= energy
            */
            long long option2 = -1;
            if (e + j[i] <= energy and memory[i-1][e+j[i]] != -1)
                option2 = memory[i-1][e+j[i]] + j_dis;

            /*
                From which energy levels can we reach energy level e by sprinting?
                We must have been in energy level e+s[i] to cut s[i] energy right? that means e+s[i] <= energy
            */
            long long option3 = -1;
            if (e + s[i] <= energy and memory[i-1][e+s[i]] != -1)
                option3 = memory[i-1][e+s[i]] + s_dis;

            memory[i][e] = std::max(
                option1,
                std::max(option2, option3)
            );
        }
    }

    return *std::max_element(memory[size-1].begin(), memory[size-1].end());
}


int main() {
    int size;
    std::cout << "\nEnter the size of the arrays : ";
    std::cin >> size;

    std::vector<int> s(size), j(size), r(size);
    std::cout << "\nKeep entering the energy lost at respective minutes for sprinting and jogging and energy gained by resting respectively : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> s[i] >> j[i] >> r[i];

    int sprint_distance, jog_distance;
    std::cout << "\nEnter the distances covered by sprinting and jogging respectively : ";
    std::cin >> sprint_distance >> jog_distance;

    int init_energy;
    std::cout << "\nEnter the initial energy : ";
    std::cin >> init_energy;

    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(
            init_energy+1, -1
        )
    );

    const long long answer = solve(s, j, r, sprint_distance, jog_distance, init_energy);
    std::cout << "\nHe can cover atmost " << answer << " distance\n\n";
    
    return 0;
}