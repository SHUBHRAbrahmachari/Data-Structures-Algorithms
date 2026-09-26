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
        energy is both the starting energy and the maximum energy allowed.
        memory[i][e] is the maximum distance after minute i with e energy;
        -1 means that this energy state is unreachable.
    */
    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(energy+1, -1)
    );

    // Resting at the first minute leaves energy at the cap and adds no distance.
    memory[0][energy] = 0;

    // If both activities cost the same energy, retain the greater distance.
    if (j[0] == s[0] and energy >= j[0])
        memory[0][energy-j[0]] = std::max(
            s_dis, j_dis
        );
    
    // Otherwise, sprinting and jogging reach distinct remaining-energy states.
    else {
        memory[0][energy-j[0]] = j_dis;
        memory[0][energy-s[0]] = s_dis;
    }

    for (int i=1; i<size; i++) {
        for (int e=energy; e>=0; e--) {
            // Compute the best distance for energy e from the previous minute's states.

            /*
                A rest gains r[i] energy, capped at energy. Below the cap, only
                predecessor e-r[i] can reach e; at the cap, any predecessor
                from energy-r[i] through energy reaches the same final energy.
            */
            long long option1 = -1;
            if (e >= r[i]) {
                // Excess recovery is discarded, so consider all predecessors that cap at energy.
                if (e == energy)
                    for (int start=e-r[i]; start<=energy; start++)
                        option1 = std::max(
                            option1,
                            memory[i-1][start]
                        );

                else
                    option1 = memory[i-1][e-r[i]];
            }

            // Jogging spends j[i] energy, so its predecessor has e+j[i] energy.
            long long option2 = -1;
            if (e + j[i] <= energy and memory[i-1][e+j[i]] != -1)
                option2 = memory[i-1][e+j[i]] + j_dis;

            // Sprinting spends s[i] energy, so its predecessor has e+s[i] energy.
            long long option3 = -1;
            if (e + s[i] <= energy and memory[i-1][e+s[i]] != -1)
                option3 = memory[i-1][e+s[i]] + s_dis;

            memory[i][e] = std::max(
                option1,
                std::max(option2, option3)
            );
        }
    }

    // The runner may finish with any reachable energy level.
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