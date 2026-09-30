/*
    You have a sequence of books to place onto shelves.
    Each shelf has a maximum allowed width W. The total width of all books must not exceed W.

    You must place the books in the exact order they are given in input. You cannot swap or reorder them.

    The height of a shelf is determined by the tallest book placed on that shelf.
    We are required to find the minimum total height of all the shelves!
    IT IS ASSUMED THAT NO BOOK HAS GREATER WIDTH THAT SHELF WIDTH W.

    1 <= N <= 10^5
    1 <= h[i], w[i], W <= 500
*/

/*
    This is simple array partitioning problem in disguise.
    Here the constraint is not length, rather total width <= W
    Pretty simple.
*/

#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<long long>::max()/2

long long solve(const std::vector<int>& h, const std::vector<int>& w, const int ws) {
    const int size = h.size();

    /*
        Similar way!

            memory[i]: what is the minimum total height of the books if we keep placing books from this index into different shelves?
    */
    std::vector<long long> memory(size);

    for (int i=size-1; i>=0; i--) {
        long long wc = 0;
        long long max_height = -1;
        long long best_option = MAX;

        for (int start=i; ; start++) {
            wc += w[start];

            if (wc > ws)
                break;

            // update max_height
            max_height = std::max(
                max_height,
                (long long)h[start]
            );

            // find the minimum sum of heights from here
            best_option = std::min(
                best_option,
                max_height + (start+1 < size ? memory[start+1] : 0)
            );

        }

        memory[i] = best_option;
    }

    return memory[0];
}

int main() {
    int size;
    std::cout << "\nEnter the number of books you have : ";
    std::cin >> size;

    std::vector<int> h(size);
    std::cout << "\nKeep entering the heights of the books : ";
    for (int i=0; i<size; i++)
        std::cin >> h[i];

    std::vector<int> w(size);
    std::cout << "\nKeep entering the widths of the books : ";
    for (int i=0; i<size; i++)
        std::cin >> w[i];

    int ws;
    std::cout << "\nEnter the width of the shelves : ";
    std::cin >> ws;

    const long long answer = solve(h, w, ws);
    std::cout << "\nThe minimum sum of heights would be : " << answer << "\n\n";

    return 0;
}