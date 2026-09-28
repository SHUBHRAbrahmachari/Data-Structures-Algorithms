/*
    We're tasked to build a N sized array.
    For each index we can either pick any odd number or any even number.
    For index i, picking an odd number costs odd[i] & picking an even number costs even[i].
    We cannot have more than K elements consecutively with same parity.

    What is the minimum cost to build the array?

    1 <= N <= 10^5
    1 <= odd[i], even[i] <= 10^5
*/


#include <iostream>
#include <vector>
#include <limits>

#define MAX std::numeric_limits<long long>::max()/2

long long solve(const std::vector<int>& odd, const std::vector<int>& even, const int k) {
    const int size = odd.size();

    if (size == 1)
        return std::min(odd[0], even[0]);

    /*
        We will start using space optimized approach now on as we have understood the funda!
            memory_odd[t]: minimum possible cost at the end of any index to build the array where we are picking atmost t-th consecutive odd element
            memory_even[t]: minimum possible cost at the end of any index to build the array where we are picking atmost t-th consecutive even element

            curr_ => represents index [i-1]
            next_ => represents index [i]

        We have reduced our space complexity to O(K) from O(NK)
    */
    std::vector<long long> curr_odd(k+1, MAX), next_odd(k+1, MAX);
    std::vector<long long> curr_even(k+1, MAX), next_even(k+1, MAX);

    // base case initialization is again very important
    for (int t=k; t>=0; t--) {
        if (t == 0) {
            // atmost 0 odd elements are picked i.e. we must have picked an even element
            curr_odd[0] = even[0];

            // atmost 0 even elements are picked i.e. we must have picked an odd element
            curr_even[0] = odd[0];
        }

        else {
            // atmost t(t>0) odd elements are picked i.e. no matter what t it is minimum cost is odd[0]
            curr_odd[t] = odd[0];

            // atmost t(t>0) even elements are picked i.e. no matter what t it is minimum cost is even[0]
            curr_even[t] = even[0];
        }
    }

    for (int i=1; i<size; i++) {
        // at this point atmost 0 odd elements were picked, that means previous to that atmost (k-1) even elements were picked and we pick atmost k-th even element.
        next_odd[0] = curr_even[k-1]+even[i];

        // at this point atmost 0 even elements were picked, that means previous to that atmost (k-1) odd elements were picked and we pick atmost k-th odd element.
        next_even[0] = curr_odd[k-1]+odd[i];

        for (int t=k; t>0; t--) {
            /*
                Suppose we are willing to pick an odd element here at this index.
                What are the possible options?

                1> upto previous index we have picked atmost (t-1)-th odd element and now we can pick atmost t-th consecutive odd element.
                2> upto previous index we have picked atmost k consecutive even elements so now we can easiliy pick first odd element
            */
            long long prev_odd_best = std::min(
                curr_odd[t-1], curr_even[k]
            );

            // update if and only if we have valid previous result
            if (prev_odd_best != MAX)
                next_odd[t] = prev_odd_best + odd[i];

            /*
                Suppose we are willing to pick an even element here at this index.
                What are the possible options?

                1> upto previous index we have picked atmost (t-1)-th even element and now we can pick atmost t-th consecutive even element.
                2> upto previous index we have picked atmost k consecutive odd elements so now we can easiliy pick first even element
            */
            long long prev_even_best = std::min(
                curr_even[t-1], curr_odd[k]
            );

            // again update if and only if we have valid previous result
            if (prev_even_best != MAX)
                next_even[t] = prev_even_best + even[i];
        }

        curr_odd = next_odd;
        curr_even = next_even;
    }

    return std::min(
        curr_even[k], curr_odd[k]
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> even(size), odd(size);
    std::cout << "\nKeep entering the costs to pick odd elements : ";
    for (int i=0; i<size; i++)
        std::cin >> odd[i];

    std::cout << "\nKeep entering the costs to pick even elements : ";
    for (int i=0; i<size; i++)
        std::cin >> even[i];

    int k;
    std::cout << "\nEnter the maximum times same parity can be picked consecutively : ";
    std::cin >> k;

    const long long answer = solve(odd, even, k);
    std::cout << "\nMinimum possible cost will be : " << answer << "\n\n";

    return 0;
}