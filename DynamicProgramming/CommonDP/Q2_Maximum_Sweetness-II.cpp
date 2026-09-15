/*
    Problem summary:
      - s[i] : sweetness of the i-th sweet type
      - t[i] : time needed to prepare that sweet
      - c[d] : the time Adam has on day d

    Adam can prepare each sweet type at most once, and on each day he can prepare as many sweets as possible
    as long as the total preparation time does not exceed that day's available time.

    Goal:
      maximize the total sweetness collected across all days.

    Constraints:
      1 <= |s| = |t| <= 10^5
      1 <= |c| <= 10^5
      1 <= s[i] <= 10^5
      1 <= c[i], t[i] <= 10^5

    Important note:
      This is a class of NP-hard problem. In other words, it belongs to a family of computational problems
      for which no known scalable polynomial-time solution exists in general. Even though a DP-style approach
      may work efficiently for some structured or constrained instances, it does not guarantee a universally
      optimized and scalable solution for large inputs.
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Sweet {
    private:
        int sweetness;
        int time;

    public:
        Sweet(const int sweetness, const int time) {
            this->sweetness = sweetness;
            this->time = time;
        }

        int get_sweetness() const {
            return this->sweetness;
        }

        int get_time() const {
            return this->time;
        }
};


class Comparator {
    public:
        bool operator()(const Sweet& s1, const Sweet& s2) const {
            return s1.get_time() < s2.get_time();
        }
};

long long solve_recurrence(
    const std::vector<Sweet>& sweets,
    std::vector<std::vector<long long>>& memory,
    std::vector<bool>& tracker,
    const int rem,
    const int last_index,
    const int curr_index=0
) {
    if (curr_index > last_index)
        return 0;

    if (memory[curr_index][rem] != -1)
        return memory[curr_index][rem];

    // Case 1:
    // Either this sweet has already been used earlier, or it is too expensive for the remaining time.
    // In either situation, we skip it and continue to the next candidate.
    if (tracker[curr_index] or sweets[curr_index].get_time() > rem)
        return memory[curr_index][rem] = solve_recurrence(sweets, memory, tracker, rem, last_index, curr_index+1);

    // Case 2:
    // The current sweet can still fit within the remaining time budget.
    // We consider two choices: take it now, or leave it and move forward.
    long long option1 = sweets[curr_index].get_sweetness() + solve_recurrence(sweets, memory, tracker, rem-sweets[curr_index].get_time(), last_index, curr_index+1);
    long long option2 = solve_recurrence(sweets, memory, tracker, rem, last_index, curr_index+1);

    return memory[curr_index][rem] = std::max(
        option1, option2
    );
}

long long solve(std::vector<Sweet>& sweets, std::vector<int>& c) {
    const int n = sweets.size();
    const int m = c.size();

    // The input is sorted to keep the search space more structured and to make state transitions easier to reason about.
    // This helps reduce unnecessary checks while exploring feasible sweet selections per day.
    std::sort(c.begin(), c.end());
    std::sort(sweets.begin(), sweets.end(), Comparator());

    // A global tracker is used to ensure that a sweet is never reused across the whole process after it has been chosen once.
    std::vector<bool> tracker(n, false);

    size_t day = 0;
    size_t last_index = 0;
    long long sweetness = 0;

    while (day < m) {
        int time = c[day];

        // First, we keep only those sweets that are feasible within the current day's available time.
        while (last_index < n and sweets[last_index].get_time() <= time)
            last_index++;

        /*
            DP memory table:
            memory[i][rem] = maximum sweetness obtainable when we are at sweet index i and
            rem time units are left to spend within the current day.
        */
        std::vector<std::vector<long long>> memory(
            last_index+1,       // Extra safety for the boundary case when last_index is zero.
            std::vector<long long>(
                time+1, -1
            )
        );

        // We only consider indices up to last_index, because any sweet beyond that boundary is too expensive
        // for the current day's time budget. The tracker ensures that once a sweet has been selected once,
        // it cannot be chosen again in future iterations.
        sweetness += solve_recurrence(sweets, memory, tracker, time, last_index);

        /*
            The recurrence gives the best possible sweetness value, but it does not explicitly tell us which sweets
            were chosen to achieve that optimum. To mark the selected items, we compare the DP value at a state with
            the contribution from taking the current sweet.

            If the optimal value equals:
                current_sweetness + value_of_next_state
            then the current sweet was part of the optimal answer and is marked as used.

            This reconstruction step is done carefully so that it does not disturb the dynamic programming recurrence itself.
        */

        for (size_t i = 0; i <= last_index; i++) {
            if (tracker[i])
                continue;

            int t = sweets[i].get_time();
            int s = sweets[i].get_sweetness();

            if (t <= time) {
                // If (i + 1) is still within inclusive last_index, fetch its memoized score; otherwise 0
                long long next_state_val = (i + 1 <= last_index && memory[i + 1][time - t] != -1) ? memory[i + 1][time - t] : 0;

                // Check if the winning score at memory[i][rem] was achieved by TAKING sweet i
                if (memory[i][time] == s + next_state_val) {
                    tracker[i] = true; // Mark as taken globally
                    time -= t;  // also reduce time before going to next state to check
                }
            }
        }

        day++;
    }

    return sweetness;
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of sweets : ";
    std::cin >> size;

    std::vector<Sweet> sweets;
    int sweetness, time;
    std::cout << "\nKeep entering the sweetness and time unit required as pairs : \n\n";
    for (size_t i=0; i<size; i++) {
        std::cin >> sweetness >> time;
        sweets.emplace_back(sweetness, time);
    }

    size_t m;
    std::cout << "\nEnter the total number of days Adam have : ";
    std::cin >> m;

    std::vector<int> c(m);
    std::cout << "\nKeep entering the time units he has on those days : ";
    for (size_t i=0; i<m; i++)
        std::cin >> c[i];

    const long long answer = solve(sweets, c);
    std::cout << "\nThe maximum sweetness score would be : " << answer << "\n\n";

    return 0;
}