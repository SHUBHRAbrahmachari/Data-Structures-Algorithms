/*
    You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around:

    Turning '9' up gives '0'.
    Turning '0' down gives '9'.

    Each move consists of turning one wheel one slot up or down.
    The lock initially starts at "0000".
    You are given a list of deadends.
    If the lock displays any code present in deadends, the wheels stop turning and you cannot rotate them any further from that state.

    Given a string target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock.
    Return -1 if it is impossible.

    We always start from all zeroes. Both start and end code does not belong to the deadends.

    Examples
    Example 1
    Input:

    deadends = ["0201", "0101", "0102", "1212", "2002"]
    target = "0202"

    Output: 6

    Explanation:
    A sequence of valid moves would be:
    "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
    Total turns: 6.

    Example 2
    Input:
    deadends = ["8888"]
    target = "0009"

    Output: 1

    Explanation:
    We can turn the last wheel down once: "0000" -> "0009".
    Total turns: 1.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

int solve(std::unordered_set<std::string>& deadends, const std::string& target) {
    // we will use the same set as the tracker
    // first we need a queue
    std::queue<std::string> que;

    // we need the length of the code
    const int code_len = target.size();

    // get the start code
    std::string START = "";
    for (int i=0; i<code_len; i++)
        START += "0";

    // initaulize the BFS
    deadends.emplace(START);
    que.emplace(START);
    int steps = 0;

    // start the BFS
    while (not que.empty()) {
        const int size = que.size();

        for (int i=0; i<size; i++) {
            std::string curr_code = que.front();
            que.pop();

            if (curr_code == target)
                return steps;

            for (int pos=0; pos<code_len; pos++) {
                char original_char = curr_code[pos];

                if (original_char == '0') {
                    std::string next_word = curr_code;
                    next_word[pos] = '9';

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }

                    next_word[pos] = original_char+1;

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }
                }

                else if (original_char == '9') {
                    std::string next_word = curr_code;
                    next_word[pos] = original_char-1;

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }

                    next_word[pos] = '0';

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }
                }

                else {
                    std::string next_word = curr_code;
                    next_word[pos] = original_char-1;

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }

                    next_word[pos] = original_char+1;

                    if (deadends.find(next_word) == deadends.end()) {
                        que.emplace(next_word);
                        deadends.emplace(next_word);
                    }
                }

                // put it back
                curr_code[pos] = original_char;
            }
        }

        // increase the steps
        steps++;
    }

    return -1;
}

int main() {
    std::string target;
    std::cout << "\nEnter the target code : ";
    std::cin >> target;

    int deadend_count;
    std::cout << "\nEnter the total number of deadends : ";
    std::cin >> deadend_count;

    std::cout << "\nKeep entering the deadends : ";
    std::string deadend;

    std::unordered_set<std::string> deadends;

    for (int i=0; i<deadend_count; i++) {
        std::cin >> deadend;
        deadends.emplace(deadend);
    }

    const int ans = solve(deadends, target);
    if (ans == -1)
        std::cout << "\nThe target code is never reachable!\n\n";
    else
        std::cout << "\nWe need atleast " << ans << " transformation(s)\n\n";

    return 0;
}
