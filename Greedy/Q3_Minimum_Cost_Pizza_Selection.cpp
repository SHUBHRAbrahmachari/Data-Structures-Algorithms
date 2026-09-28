/*
    Given the area of SMALL, MEDIUM ad LARGE pizzas as s, m and l.
    Their respective costs are cs, cm and cl.
    Find the minimum amout of money to buy pizzas whose total area is atleast x.
    You may buy any number of pizzas of each type.

    Example:

        Input: x = 16, s = 3, m = 6, l = 9, cs = 50, cm = 150, cl = 300
        Output: 300
        We want at least 16 sq. units of Pizza. 
        One unit of each s, m and l = 3 + 6 + 9 = 18 sq units, Cost = 500. 
        6 units of s = 18 sq units, Cost = 300 
        2 units of l = 18 sq units, Cost = 600 etc. 
        Of all the Arrangements, Minimum Cost is Rs. 300.

    1 <= x, cs, cm, cl <= 10^5
    1 <= s, m, l <= 10^5
*/

/*
    Let me tweak the problem a bit.
    Let me say that i want to reach atleast 0 from x with minimum cost.
*/

#include <iostream>
#include <vector>

long long solve(int x, int s, int m, int l, int cs, int cm, int cl) {
    return 0;
}

int main() {
    int x;
    std::cout << "\nEnter the minimum size of the pizza : ";
    std::cin >> x;

    int s, cs;
    std::cout << "\nEnter the small size amount of pizza and its cost : ";
    std::cin >> s >> cs;

    int m, cm;
    std::cout << "\nEnter the medium size amount of pizza and its cost : ";
    std::cin >> m >> cm;

    int l, cl;
    std::cout << "\nEnter the large size amount of pizza and its cost : ";
    std::cin >> l >> cl;

    const long long answer = solve(x, s, m, l, cs, cm, cl);
    std::cout << "\nThe minimum cost would be : " << answer << "\n\n";

    return 0;
}