/*
    On evey intersection i, you are supposed to put either a Red light (cost = r[i]), or a Green light (cost = g[i]) or keep it empty.
    Two consecutive sections cannot have the same light.
    Find the minimum cost to set up these lights across N intersections ensuring every consecutive 2 intersections have atleast one light.

    1 <= N <= 10^5
    1 <= r[i], g[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& r, const std::vector<int>& g) {
    const int size = r.size();

    long long curr_red = r[0], next_red;
    long long curr_green = g[0], next_green;
    long long curr_empty = 0, next_empty;
    
    for (int i=1; i<size; i++) {
        next_red = std::min(
            curr_empty, curr_green
        ) + r[i];

        next_green = std::min(
            curr_empty, curr_red
        ) + g[i];

        next_empty = std::min(
            curr_red, curr_green
        );

        curr_empty = next_empty;
        curr_red = next_red;
        curr_green = next_green;
    }

    return std::min(
        curr_empty,
        std::min(
            curr_red, curr_green
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the total number of intersections : ";
    std::cin >> size;

    std::vector<int> r(size), g(size);
    std::cout << "\nKeep entering the red-light set up cost at each intersection : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> r[i];

    std::cout << "\nKeep entering the green-light set up cost at each intersection : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> g[i];

    const long long answer = solve(r, g);
    std::cout << "\nThe minimum cost would be : " << answer << "\n\n";

    return 0;
}