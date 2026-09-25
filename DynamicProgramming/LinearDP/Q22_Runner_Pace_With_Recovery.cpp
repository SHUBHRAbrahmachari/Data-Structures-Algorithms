/*
    A runner is attempting a marathon.
    Every minute the runner can take either of these 3 decisons.

        1> runner can sprint at i-th minute. But doing that he loses s[i] energy but covers S distance
        2> runner can jog at i-th minute. But doing that he loses j[i] energy but covers J distance
        3> runner can rest at i-th minute. Doing that he gains r[i] energy and covers 0 distance.

    if a decison makes his energy < 0, he cannot take that decison as well.
    What is the maximum distance he can cover in that N minutes. The runner starts with initial energy K, and maximum energy can be K as well.

    1 <= |s[]| = |j[]| = |r[]| <= 10^5
    1 <= s[i], j[i], r[i] <= 10^5
    1 <= J < S <= 10^5
    1 <= K <= 100
*/

#include <iostream>
#include <vector>

// O(NE)
long long solve_memoization(
    const std::vector<int>& s,
    const std::vector<int>& j,
    const std::vector<int>& r,
    const int s_dis,
    const int j_dis,
    const int max_energy,
    std::vector<std::vector<long long>>& memory,
    const int index,
    const int curr_energy
) {
    if (index >= s.size())
        return 0;

    if (memory[index][curr_energy] != -1)
        return memory[index][curr_energy];

    // case 1: the runner wants to rest this minute
    long long option1 = solve_memoization(s, j, r, s_dis, j_dis, max_energy, memory, index+1, std::min(max_energy, curr_energy+r[index]));      // `curr_energy` must not exceed `max_energy`

    // case 2: the runner wants to jog this minute
    long long option2 = 0;
    if (curr_energy - j[index] >= 0)
        option2 = j_dis + solve_memoization(s, j, r, s_dis, j_dis, max_energy, memory, index+1, curr_energy-j[index]);

    // case 3: the runner wants to sprint this minute
    long long option3 = 0;
    if (curr_energy - s[index] >= 0)
        option3 = s_dis + solve_memoization(s, j, r, s_dis, j_dis, max_energy, memory, index+1, curr_energy-s[index]);

    return std::max(
        option1,
        std::max(
            option2,
            option3
        )
    );
}

long long solve_tabulation(
    const std::vector<int>& s,
    const std::vector<int>& j,
    const std::vector<int>& r,
    const int s_dis,
    const int j_dis,
    const int energy
) {
    const int size = s.size();

    // for all energy, at index=size distance has to be zero

    // next DP represents index+1, curr_dp represents curr_index
    std::vector<long long> next_dp(energy+1), curr_dp(energy+1);

    // just reversing the parameter directions
    for (int index=size-1; index>=0; index--) {
        for (int e=0; e<=energy; e++) {
            // option 1> rest this minute
            int next_energy_rest = std::min(
                energy,
                e+r[index]
            );

            long long option1 = next_dp[next_energy_rest];

            // option 2> jog
            long long option2 = 0;
            if (e >= j[index])
                option2 = j_dis + next_dp[e-j[index]];

            // option 3> sprint
            long long option3 = 0;
            if (e >= s[index])
                option3 = s_dis + next_dp[e-s[index]];

            curr_dp[e] = std::max(
                option1,
                std::max(
                    option2,
                    option3
                )
            );
        }

        next_dp = curr_dp;
    }

    return next_dp[energy];
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

    std::cout << "\nHe can cover atmost (using memoization approach)" << solve_memoization(s, j, r, sprint_distance, jog_distance, init_energy, memory, 0, init_energy) << " distance\n\n";
    std::cout << "\nHe can cover atmost (using tabulation approach)" << solve_tabulation(s, j, r, sprint_distance, jog_distance, init_energy) << " distance\n\n";

    return 0;
}