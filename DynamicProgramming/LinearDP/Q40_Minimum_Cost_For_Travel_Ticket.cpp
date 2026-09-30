/*
    You are given an array representing calender days where you must travel.
    Rest of the days you must stay at home.
    
    You have 3 ticket choices:

    1> 1-day pass costs[0]: you can travel on the you buy it.
    2> 7-day pass costs[1]: you can travel for the next 7 days including the day you buy it!
    3> 30-day pass costs[2]: you can travel for the next 7 days including the day you buy it!

    Minimum total cost to cover all travel days.

    input: days=[1 4 6 7 8 20] costs=[2 7 15] => output=11 = 7 + 2 + 2
    input: days=[1 2 3 4 5 6 7 8 9 10] costs[2 7 15] => output=13 = 7 + 2 + 2 + 2

    1 <= |days| <= 365
    1 <= days[i] <= 365
    1 <= costs[i] <= 1000
*/

#include <iostream>
#include <vector>
#include <limits>
#include "../../segment_tree.hpp"

#define MAX std::numeric_limits<int>::max()

int solve(const std::vector<int>& days, const std::vector<int>& costs) {
    const int size = days.size();
    const int LAST_DAY = days[size-1];
    const int FIRST_DAY = days[0];

    /*
        How our DP states would look like?

        memory_1_buy[d]: what is the minimum cost to travel upto day d where at day d we buy a 1-day pass and use it.
        memory_7_buy[d]: what is the minimum cost to travel upto day d where at day d we buy a 7-day pass and use it.
        memory_30_buy[d]: what is the minimum cost to travel upto day d where at day d we buy a 30-day pass and use it.
        memory_7_use[d]: what is the minimum cost to travel upto day d where at day d we re-use a previously bought 7-day pass.
        memory_30_use[d]: what is the minimum cost to travel upto day d where at day d we re-use a previously bought 30-day pass.
    */
    
    std::vector<int> memory_1_buy(LAST_DAY+1, MAX);
    std::vector<int> memory_7_use(LAST_DAY+1, MAX);
    std::vector<int> memory_30_use(LAST_DAY+1, MAX);

    // because we have to do range query!
    SegmentTreeMin<int> memory_7_buy(LAST_DAY+1, MAX);
    SegmentTreeMin<int> memory_30_buy(LAST_DAY+1, MAX);


    // base case initialization
    memory_1_buy[FIRST_DAY] = costs[0];
    memory_7_use[FIRST_DAY] = costs[1];
    memory_30_use[FIRST_DAY] = costs[2];

    memory_7_buy.update(FIRST_DAY, costs[1]);
    memory_30_buy.update(FIRST_DAY, costs[2]);

    // now we start lookong for the 
    for (int i=1; i<size; i++) {
        const int curr_day = days[i];
        const int prev_day = days[i-1];

        // what is the minimum cost to travel upto last day by any of the possible ways
        const int prev_candidate = std::min(
            // what is the minimum cost to travel upto previous day where where we used a 1-day pass to travel the previous day.
            memory_1_buy[prev_day],

            std::min(
                // what is the minimum cost to travel upto previous day where where we used a previously bought 7-days pass to travel the previous day.
                memory_7_use[prev_day],

                // what is the minimum cost to travel upto previous day where where we used a previously bought 7-days pass to travel the previous day.
                memory_30_use[prev_day]
            )
        );

        /*
            Case 1: suppose we want to buy a 1-day pass and travel with it only!
                    what do we need to know? what is the minimum cost to travel upto the previous day
        */
        memory_1_buy[curr_day] = prev_candidate + costs[0];


        /*
            Case 2: suppose we want to buy a 7-day pass and travel with it only!
                    What do we need to know? what is the minimum cost to travel upto last day again!
        */
        memory_7_buy.update(curr_day, prev_candidate + costs[1]);

        /*
            Case 3: suppose we want to buy a 30-day pass and travel with it only!
                    What do we need to know? what is the minimum cost to travel upto last day again!
        */
        memory_30_buy.update(curr_day, prev_candidate + costs[2]);

        /*
            Case 4: suppose we want to use a previously bought 7 day pass today!
                    what should we ask for? what is the minimum cost we beared within last 7 days where we had bought a 7-day pass right?
        */
        int LAST_DAY_OF_BUYING = std::max(0, curr_day-6);
        int LATEST_DAY_OF_BUYING = std::max(0, curr_day-1);
        
        memory_7_use[curr_day] = memory_7_buy.query(LAST_DAY_OF_BUYING, LATEST_DAY_OF_BUYING);


        /*
            Case 5: suppose we want to use a previously bought 7 day pass today!
                    what should we ask for? what is the minimum cost we beared within last 7 days where we had bought a 30-day pass right?
        */
        LAST_DAY_OF_BUYING = std::max(0, curr_day-29);
        memory_30_use[curr_day] = memory_30_buy.query(LAST_DAY_OF_BUYING, LATEST_DAY_OF_BUYING);
    }

    return std::min(
        memory_1_buy[LAST_DAY],
        std::min(
            memory_7_use[LAST_DAY],
            memory_30_use[LAST_DAY]
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the days to travel : ";
    std::cin >> size;

    std::vector<int> days(size);
    std::cout << "\nKeep entering the days in increasing order : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> days[i];
    
    std::vector<int> costs(3);
    std::cout << "\nEnter the costs to buy 1-day, 7-day and 30-day passes repectively : \n\n";
    std::cin >> costs[0] >> costs[1] >> costs[2];

    const long long answer = solve(days, costs);
    std::cout << "\nThe minimum cost would be : " << answer << "\n\n";

    return 0;
}