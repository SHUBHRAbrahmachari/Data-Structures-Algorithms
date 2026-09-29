/*
    You have N slots on a shelf. On each slot you can keep a book.
    To place a HARDCOVER book on i-th slot incurs cost h[i].
    To place a PAPERBACK book on i-th slot incurs cost p[i].
    HARDCOVER books cannot be placed with each other.

    MINIMIZE the total cost to keep N books.

    1 <= N <= 10^5
    1 <= h[i], p[i] <= 10^5
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& h, const std::vector<int>& p) {
    const int size = h.size();

    if (size == 1)
        return std::min(h[0], p[0]);

    long long curr_h = h[0], next_h;
    long long curr_p = p[0], next_p;

    for (int i=1; i<size; i++) {
        next_h = curr_p + h[i];
        next_p = std::min(curr_h, curr_p) + p[i];

        curr_h = next_h;
        curr_p = next_p;
    }

    return std::min(curr_h, curr_p);
}

int main() {
    int size;
    std::cout << "\nEnter the number of total slots on the book shelf : ";
    std::cin >> size;

    std::vector<int> h(size), p(size);
    std::cout << "\nKeep entering the costs to place HARDCOVER books in each slot : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> h[i];

    std::cout << "\nKeep entering the costs to place PAPERBACK books in each slot : \n\n";
    for (int i=0; i<size; i++)
        std::cin >> p[i];

    const long long answer = solve(h, p);
    std::cout << "\nthe minimum cost will be : " << answer << "\n\n";

    return 0;
}