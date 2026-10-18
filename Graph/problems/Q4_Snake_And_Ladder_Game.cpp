/*
    Given a NxN board for a snake ladder game to br played.
    You start from cel number 1 and you have to reach cell N^2.

    You have a dice which gives you the face values in range [1, 6] as usual.

    As usual you have snakes and ladders on the board.

    > Start of a ladder and Mouth of a snake woudn't ever be at the same cell.
    > End of a snake and Start of a ladder wouldn't be at the same cell either.
    > Two snake mouths cannot share same cell.
    > Start of two ladders cannot start at a same cell.

    What is the minimum number of moves required to reach the last cell?
    If you cannot reach the last cell return -1

    1 <= N <= 3000
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>

// O(N^2)
int solve(const int n, const std::unordered_map<int, int>& snakes, const std::unordered_map<int, int>& ladders) {
    // first we must figure out the target cell we want to reach
    const int TARGET = n*n;

    // we must also consider having a visited marker
    std::vector<bool> vis(TARGET+1, false);

    // we need to have a queue which would be required for the BFS
    std::queue<int> que;

    // initialize the current steps to reach the target
    int steps = 0;

    // initiallize the BFS
    que.emplace(1);
    vis[1] = true;

    // start the further BFS
    while (not que.empty()) {
        // see how many cells we can reach in this iteration
        const int size = que.size();

        for (int i=0; i<size; i++) {
            const int cell = que.front();
            que.pop();

            // see if we have reached the target cell
            if (cell == TARGET)
                return steps;

            /*
                Now from this cell we must see what unvisited cells we can reach further.
                Dice face values are in range [1, 6]
            */
            for (int dice=1; dice<=6; dice++) {
                int next_cell = cell+dice;

                // if next_cell falls under range only then we must go to it
                if (next_cell <= TARGET) {
                    // case 1: we might be standing at a stair/ladder
                    if (ladders.find(next_cell) != ladders.end())
                        next_cell = ladders.at(next_cell);

                    // case 2: we might be at a mouth of the snake
                    else if (snakes.find(next_cell) != snakes.end())
                        next_cell = snakes.at(next_cell);

                    // now we must add this next reachable cell to our QUEUE if not already visited
                    if (not vis[next_cell]) {
                        que.emplace(next_cell);
                        vis[next_cell] = true;
                    }
                }

                // no need to check any further as stretch is going to increase only
                else
                    break;
            }
        }

        // increase the steps
        steps++;
    }

    // not possible to reach
    return -1;
}

int main() {
    int n;
    std::cout << "\nEnter the number of rows or columns in the board : ";
    std::cin >> n;

    int ladder_count;
    std::cout << "\nEnter how many ladders are there : ";
    std::cin >> ladder_count;

    std::unordered_map<int, int> ladders;

    if (ladder_count > 0) {
        std::cout << "\nKeep entering the ladder start and stop cells in a pairwise manner : \n\n";
        for (int i=0; i<ladder_count; i++) {
            int ladder_start, ladder_end;
            std::cin >> ladder_start >> ladder_end;
            
            ladders[ladder_start] = ladder_end;
        }
    }

    int snake_count;
    std::cout << "\nEnter how many snakes are there : ";
    std::cin >> snake_count;

    std::unordered_map<int, int> snakes;

    if (snake_count > 0) {
        std::cout << "\nKeep entering the snake start and stop cells in a pairwise manner : \n\n";
        for (int i=0; i<snake_count; i++) {
            int snake_start, snake_end;
            std::cin >> snake_start >> snake_end;

            snakes[snake_start] = snake_end;
        }
    }

    int steps = solve(n, snakes, ladders);

    if (steps == -1)
        std::cout << "\nYou cannot reach the last cell\n\n";
    else
        std::cout << "\nYou need atleast " << steps << " step(s) to reach the last cell\n\n";

    return 0;
}