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
        Let us define our DP state:

            memory[i][0]: maximum possible earnable points upto day i where we sit idle at day i
            memory[i][t]: maximum possible earnable points upto day i where we perform task-t at day i (t = {1, 2, 3})
    */
    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(
            4, -1
        )
    );

    // at the end of day 0, obviously these are the results
    memory[0][0] = 0;
    memory[0][1] = t1[0];
    memory[0][2] = t2[0];
    memory[0][3] = t3[0];

    for (int i=1; i<size; i++) {
        // case 1: i decide to sit idle today
        memory[i][0] = std::max(
            std::max(
                memory[i-1][0],     // i was also sitting idle yesterday
                memory[i-1][1]      // i performed task-1 yesterday
            ),

            std::max(
                memory[i-1][2],     // i performed task-2 yesterday
                memory[i-1][3]      // i performed task-3 yesterday
            )
        );

        // case 2: i decided to perform task-1 today
        memory[i][1] = std::max(
            std::max(
                memory[i-1][0],     // i was also sitting idle yesterday
                memory[i-1][1]      // i performed task-1 yesterday
            ),

            std::max(
                memory[i-1][2],     // i performed task-2 yesterday
                memory[i-1][3]      // i performed task-3 yesterday
            )
        ) + t1[i];      // collect the point for doing task-1

        // case 3: i decided to perform task-2 today
        memory[i][2] = std::max(
            std::max(
                memory[i-1][0],     // i was sitting idle yesterday
                memory[i-1][1]      // i had done task-1 yesterday
            ),

            // since i cannot precede task-2 or task-3 yesterday just because i am attempting task-2 today. I need to go back to day before yesterday
            (i > 1?  
                std::max(
                    memory[i-2][2],     // i performed task-2 day before yesterday
                    memory[i-2][3]      // i performed task-3 day before yesterday
                ) : 0LL)
        ) + t2[i];      // collect the point for doing task-2

        // case 4: i decided to perform task-3 today
        memory[i][3] = std::max(
            memory[i-1][0],     // i was sitting idle yesterday
            (i > 1 ? 
                std::max(
                    memory[i-2][1],     // i performed task-1 day before yesterday
                    std::max(
                        memory[i-2][2],     // i performed task-2 day before yesterday
                        memory[i-2][3]      // i performed task-3 day before yesterday
                    )
                ) : 0LL
            )
        ) + t3[i];      // collect the point for doing task-3
    }

    return *std::max_element(memory[size-1].begin(), memory[size-1].end());
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

