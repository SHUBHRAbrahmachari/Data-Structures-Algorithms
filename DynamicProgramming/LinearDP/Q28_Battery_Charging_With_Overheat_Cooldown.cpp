/*
    Given two integer arrays having positive integers only F[], S[]

    Charging at fast rate adds charge F[i] at i-th minute but adds up heat to +2
    Charging at slow rate adds charge S[i] at i-th minute but reduces heat by -1

    Heat cannot drop below 0 or go beyond 3, otheriwise the battery might get damaged.
    What is the maximum charge you can collect over N minutes?

    1 <= N <= 10^5
    1 <= F[i], S[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>

long long solve(const std::vector<long long>& s, const std::vector<long long>& f) {
    const int size = s.size();

    if (size == 1)
        return f[0];        // at heat level 0 slow charging is illegal

    /*
        memory[i][t]: after i-th minute, with t heat level, what is the best charge i can collect 
    */
    std::vector<std::vector<long long>> memory(
        size,
        std::vector<long long>(4, -1)
    );

    // after 0-th minute, with 2 heat level maximum possible charge would be f[0]
    memory[0][2] = f[0];

    for (int i=1; i<size; i++) {
        /*
            What are the ways that i can reach heat level 0 at i-th minute?
            The only option is that last minute i was at heat level 1 so i put on slow charge this minute
        */
        if (memory[i-1][1] != -1)
            memory[i][0] = memory[i-1][1] + s[i];

        /*
            What are the ways that i can reach heat level 1 at the i-th minute?
            The only option is that in the previous minute i was at heat level 2 so i put slow charge this minute
        */
        if (memory[i-1][2] != -1)
            memory[i][1] = memory[i-1][2] + s[i];

        /*
            What are the ways that i can reach heat level 2 this minute? There are 2 options actually
                1> i was at heat level 0 last minute so i put on fast charge this minute
                2> i was at heat level 3 last minute so i put on slow charge this minute

            Take whatever gives the best result
        */
        memory[i][2] = std::max(
            (memory[i-1][0] != -1 ? memory[i-1][0] + f[i] : -1),
            (memory[i-1][3] != -1 ? memory[i-1][3] + s[i] : -1)
        );

        /*  
            What are the ways i could reach heat level 3 this minute?
            The only option is that i was at heat level 1 last minute so i put on fast charge this minute
        */
        if (memory[i-1][1] != -1)
            memory[i][3] = memory[i-1][1] + f[i];
    }

    return *std::max_element(memory[size-1].begin(), memory[size-1].end());
}

int main() {
    int size;
    std::cout << "\nEnter total number of minutes : ";
    std::cin >> size;

    std::vector<long long> s(size), f(size);
    std::cout << "\nKeep entering the charge provided after slow charging for every minute : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> s[i];

    std::cout << "\nKeep entering the charge provided after fast charging for every minute : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> f[i];

    const long long answer = solve(s, f);
    std::cout << "\nThe maximum charge possible is : " << answer << "\n\n";

    return 0;
}