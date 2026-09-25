/*
    You are given 3 positive integer arrays of length N: t1[], t2[] and t3[]
    t3 is the most high effort task and t1 is the one with lowest effort.

    value at any index i represents point earned by performing that particular task.

    There are some safety guidelines for the workers:
        1> if at any day you're doing task-3, the next day you cannot do any of the tasks.
        2> if at any day you're doing task-2, the next day you can only do task-1
        3> if at any day you're doing task-1, the next day you can only do any of the tasks

    There are also some regular guidelines:
        1> at any day you can either rest or do exactly 1 type of task
        2> the task is your selection

    If you have N days appointed to you, what is the maximum point you can earn?

    1 <= N <= 10^5
    1 <= t1[i], t2[i], t3[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>

long long solve(const std::vector<int>& t1, const std::vector<int>& t2, const std::vector<int>& t3) {
    const int size = t1.size();

    if (size == 1)
        return std::max(
            t1[0],
            std::max(
                t2[0], t3[0]
            )
        );

    /*
        Let us define our DP states now!

        memory_idle[i]: maximum collectable points upto day i when we are doing no task at day i
        memory_t1[i]: maximum collectable points upto day i when we are doing task 1 at day i
        memory_t2[i]: maximum collectable points upto day i when we are doing task 2 at day i
        memory_t3[i]: maximum collectable points upto day i when we are doing task 3 at day i
    */
    std::vector<long long> memory_idle(size);
    std::vector<long long> memory_t1(size);
    std::vector<long long> memory_t2(size);
    std::vector<long long> memory_t3(size);

    // initiating the base cases
    memory_idle[0] = 0;
    memory_t1[0] = t1[0];
    memory_t2[0] = t2[0];
    memory_t3[0] = t3[0];

    for (int i=1; i<size; i++) {
        // no restriction on resting for any day
        memory_idle[i] = std::max(
            std::max(
                memory_idle[i-1],
                memory_t1[i-1]
            ),

            std::max(
                memory_t2[i-1],
                memory_t3[i-1]
            )
        );

        memory_t1[i] = std::max(
            std::max(
                memory_idle[i-1],
                memory_t1[i-1]                              // i could've done task-1 the previous day
            ),

            std::max(
                memory_t2[i-1],                             // i could have also done task-2 the previous day
                (i > 1 ? memory_t3[i-2] : 0)                // but i couldn't do task-3 the previous day
            )
        ) + t1[i];

        memory_t2[i] = std::max(
            std::max(
                memory_idle[i-1],
                memory_t1[i-1]                              // i could surely do task 1 the previous day
            ),
            
            (i > 1 ? std::max(memory_t2[i-2], memory_t3[i-2]) : 0)      // i could not do either task-2 or task-3 the previous day
        ) + t2[i];

        memory_t3[i] = std::max(
            std::max(
                memory_idle[i-1],
                memory_t1[i-1]                              // i could do task-1 the previous day
            ),
            
            (i > 1 ? std::max(memory_t2[i-2], memory_t3[i-2]) : 0)      // but i could not do either task-2 or task-3 the previous day
        ) + t3[i];   
    }

    return std::max(
        std::max(
            memory_idle[size-1],
            memory_t1[size-1]
        ),

        std::max(
            memory_t2[size-1],
            memory_t3[size-1]
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> t1(size), t2(size), t3(size);
    std::cout << "\nKeep entering the points rewardable for each day regrading t1, t2 and t3 respectively : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> t1[i] >> t2[i] >> t3[i];

    const long long answer = solve(t1, t2, t3);
    std::cout << "\nMaximum earnable points would be : " << answer << "\n\n";

    return 0;
}

