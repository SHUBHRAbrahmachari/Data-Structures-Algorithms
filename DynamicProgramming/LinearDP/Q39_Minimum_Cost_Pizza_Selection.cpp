/*
    You went at a pizza show to buy pizza of size atleast X.
    You have 3 options:

    1> buy small size pizza with area s and pay cs money
    2> buy medium size pizza with area m and pay cm money
    3> buy large size pizza with area l and pay cl money

    You can buy any option any number of times. What is the minimum cost to reach size atleast X.

    1 <= s, m, l, x <= 10^5
    1 <= cs, cm, cl <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<long long>::max()/2

long long solve(int x, int s, int m, int l, int cs, int cm, int cl) {

    /*
        Let us define our DP state.
            memory[a]: minimum cost to reach pizza size a
    */
    std::vector<long long> memory(x+1, MAX);
    long long option1, option2, option3;

    // base case initialization
    memory[0] = 0;

    for (int a=1; a<=x; a++) {
        option1 = option2 = option3 = MAX;

        // since x is the upper range we have to handle it specially!
        if (a == x) {
            for (int c=std::max(0, x-s); c<x; c++) {
                if (memory[c] != MAX)
                    option1 = std::min(
                        option1,
                        memory[c] + cs
                    );
            }

            for (int c=std::max(0, x-m); c<x; c++) {
                if (memory[c] != MAX)
                    option2 = std::min(
                        option2,
                        memory[c] + cm
                    );
            }

            for (int c=std::max(0, x-l); c<x; c++) {
                if (memory[c] != MAX)
                    option3 = std::min(
                        option3,
                        memory[c] + cl
                    );
            }
        }

        else {
            // how can we reach at size a by buying small size pizza?
            if (a >= s and memory[a-s] != MAX)
                option1 = memory[a-s] + cs;

            // how can you reach at a size a by buying medium size pizza?
            if (a >= m and memory[a-m] != MAX)
                option2 = memory[a-m] + cm;

            // how can you reach at at size a by buying large size pizza?
            if (a >= l and memory[a-l] != MAX)
                option3 = memory[a-l] + cl;
        }

        // set the minimum cost to reach size a
        memory[a] = std::min(
            option1, std::min(option2, option3)
        );
    }

    return memory[x];
}

int main() {
    int x;
    std::cout << "\nEnter the minimum target size to reach : ";
    std::cin >> x;

    int s, cs;
    std::cout << "\nEnter the small size amount & its corresponding cost : ";
    std::cin >> s >> cs;

    int m, cm;
    std::cout << "\nEnter the medium size amount & its corresponding cost : ";
    std::cin >> m >> cm;

    int l, cl;
    std::cout << "\nEnter the large size amount & its corresponding cost : ";
    std::cin >> l >> cl;

    const long long answer = solve(x, s, m, l, cs, cm, cl);
    std::cout << "\nThe minimum cost will be : " << solve(x, s, m, l, cs, cm, cl);

    return 0;
}