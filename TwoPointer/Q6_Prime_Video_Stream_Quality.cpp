/*
    you're given a string stream having uppercase english letters representing frame quality and an integer K.
    you can modify atmost K characters to any other upper case letter.
    Return the maximum possible length of a contiguous substring containing identical letters

    1 <= K <= |s| <= 10^5
    'A' <= s[i] <= 'Z'

*/
/*
    The trick is that a window is valid until window_length - maximum_frequency <= k
*/

#include <iostream>
#include <vector>
#include <algorithm>


size_t find_longest_substring_length(const std::string& stream, const size_t k) {
    const size_t size = stream.size();

    // get a vector to track frequencies
    std::vector<size_t> frequencies(27, 0);

    size_t left = 0;
    size_t right = 0;
    size_t max_length = 0;

    while (right < size) {
        // take this character into account
        const size_t index = stream[right] - 'A';

        // increase the frequency
        frequencies[index] += 1;

        // shrink the window as long as this particular condition is satisfied
        while ((right - left + 1) - *std::max_element(frequencies.begin(), frequencies.end()) > k) {
            const size_t index_to_reduce_frequency = stream[left] - 'A';
            frequencies[index_to_reduce_frequency] -= 1;
            left++;
        }

        max_length = std::max(
            max_length,
            right - left + 1
        );

        right++;
    }

    return max_length;
}

int main() {
    std::string stream;
    std::cout << "\nEnter the stream : ";
    std::cin >> stream;

    size_t k;
    std::cout << "\nEnter the maximum number of switches possible : ";
    std::cin >> k;


    const size_t answer = find_longest_substring_length(stream, k);
    std::cout << "\nThe maximum substring length would be : " << answer << std::endl << std::endl;

    return 0;
}