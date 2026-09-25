/*
    You are given 3 positive integer arrays of length N: t1[], t2[] and t3[]
    t3 is the most high effort task and t1 is the one with lowest effort.

    value at any index i represents point earned by performing that particular task.

    There are some safety guidelines for the workers:
        1> if at any day you're doing task-3, the next day you cannot do any of the tasks.
        2> if at any day you're doing task-2, the next day you can only do task-1 but not not task-2 or task-3
        3> if at any day you're doing task-1, the next day you can only do any of the tasks except task 3

    There are also some regular guidelines:
        1> at any day you can either rest or do exactly 1 type of task
        2> the task is your selection

    If you have N days appointed to you and you can do atmost K tasks including all types, what is the maximum point you can earn?

    1 <= N <= 10^5
    1 <= K <= 10^3
    1 <= t1[i], t2[i], t3[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(
    const std::vector<int>& t1,
    const std::vector<int>& t2,
    const std::vector<int>& t3,
    const int k
) {
    const int size = t1.size();

    if (size == 1)
        return std::max(
            t1[0],
            std::max(
                t2[0], t3[0]
            )
        );

    /*
        Let us define our DP memory first:

        memory_idle[i][t]: maximum possible collectable points upto index i with atmost t tasks done till now
        memory_t1[i][t]: maximum possible collectable points upto index i with atmost t tasks done till now including task-1 being done today
        memory_t2[i][t]: maximum possible collectable points upto index i with atmost t tasks done till now including task-2 being done today
        memory_t3[i][t]: maximum possible collectable points upto index i with atmost t tasks done till now including task-3 being done today
    */
    std::vector<std::vector<long long>> memory_idle(size, std::vector<long long>(k+1, 0));
    std::vector<std::vector<long long>> memory_t1(size, std::vector<long long>(k+1, 0));
    std::vector<std::vector<long long>> memory_t2(size, std::vector<long long>(k+1, 0));
    std::vector<std::vector<long long>> memory_t3(size, std::vector<long long>(k+1, 0));

    // base case initialization
    for (int t=k; t>=1; t--) {
        memory_t1[0][t] = t1[0];
        memory_t2[0][t] = t2[0];
        memory_t3[0][t] = t3[0];
    }

    for (int i=1; i<size; i++) {
        for (int t=k; t>=1; t--) {
            // since we are not doing any task today
            memory_idle[i][t] = std::max(
                std::max(
                    memory_idle[i-1][t],
                    memory_t1[i-1][t]
                ),

                std::max(
                    memory_t2[i-1][t],
                    memory_t3[i-1][t]
                )
            );

            // we decide to do task-1 today
            memory_t1[i][t] = std::max(
                std::max(
                    memory_idle[i-1][t-1],
                    memory_t1[i-1][t-1]     // yes i can do task-1 the previous day
                ),

                std::max(
                    memory_t2[i-1][t-1],    // yes i can also do task-2 the previous day
                    (i > 1 ? memory_t3[i-2][t-1] : 0)   // but i cannot do task-3 the previous day
                )
            ) +  t1[i];

            // we decide to do task-2 today
            memory_t2[i][t] = std::max(
                std::max(
                    memory_idle[i-1][t-1],
                    memory_t1[i-1][t-1]
                ),

                (i > 1 ? std::max(memory_t2[i-2][t-1], memory_t3[i-2][t-1]) : 0)
            ) + t2[i];

            // we decide to do task-3 today
            memory_t3[i][t] = std::max(
                std::max(
                    memory_idle[i-1][t-1],
                    (i > 1 ? memory_t1[i-2][t-1] : 0)       // no i also cannot do task-1 the previous day
                ),

                (i > 1 ? std::max(memory_t2[i-2][t-1], memory_t3[i-2][t-1]) : 0)
            ) + t3[i];
        }
    }

    return std::max(
        std::max(
            memory_idle[size-1][k],
            memory_t1[size-1][k]
        ),

        std::max(
            memory_t2[size-1][k],
            memory_t3[size-1][k]
        )
    );
}


int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> t1(size), t2(size), t3(size);
    std::cout << "\nKeep entering the prices for each day for t1, t2 and t3 respectively : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> t1[i] >> t2[i] >> t3[i];

    int k;
    std::cout << "\nEnter the maximum number of tasks they can do : ";
    std::cin >> k;

    const long long answer = solve(t1, t2, t3, k);
    std::cout << "\nThe maximum possible points would be : " << answer << "\n\n";

    return 0;
}