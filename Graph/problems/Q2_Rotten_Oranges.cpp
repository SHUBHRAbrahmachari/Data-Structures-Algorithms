/*
    We are given a MxN maze.
    Each cell consists of only three integers.

    0: empty cell
    1: fresh orange
    2: rotten orange

    Every minute, any fresh orage that is 4 directionally adjacent orange (up, down, right & left) gets rotten.
    We can rot one fresh orange once only.
    Find minimum number of minutes for all oranges to rotten.

    If all oranges cannot be rotten, return -1.
    If no fresh oranges are there simply return 0
*/

/*
    This is classic case of Multi-Source BFS.
    We need to track down all rotten oranges together.
    Since all rot fresh oranges together.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

// O(M.N)
int solve(std::vector<std::vector<int>>& maze) {
    const int m = maze.size();
    const int n = maze[0].size();

    // to count how many fresh oranges do we currently have
    int fresh_count = 0;

    // to track down the rotten oranges
    std::queue<std::pair<int, int>> que;

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (maze[i][j] == 1)
                fresh_count++;

            else if (maze[i][j] == 2)
                que.emplace(i, j);
        }
    }

    // if no fresh oranges are present there's no point of checking further
    if (fresh_count == 0)
        return 0;

    // minimum time to rot all the oranges 
    int time = 0;

    while (not que.empty()) {
        // for this generation, these many rotten oranges we currently have
        const int size = que.size();

        for (int i=0; i<size; i++) {
            const std::pair<int, int> p = que.front();
            que.pop();

            const int cr = p.first;
            const int cc = p.second;

            // check right
            if (cc+1 < n and maze[cr][cc+1] == 1) {
                maze[cr][cc+1] = 2;
                que.emplace(cr, cc+1);
                fresh_count--;
            }

            // check down
            if (cr+1 < m and maze[cr+1][cc] == 1) {
                maze[cr+1][cc] = 2;
                que.emplace(cr+1, cc);
                fresh_count--;
            }

            // check left
            if (cc-1 >= 0 and maze[cr][cc-1] == 1) {
                maze[cr][cc-1] = 2;
                que.emplace(cr, cc-1);
                fresh_count--;
            }

            // check up
            if (cr-1 >= 0 and maze[cr-1][cc] == 1) {
                maze[cr-1][cc] = 2;
                que.emplace(cr-1, cc);
                fresh_count--;
            }
        }

        // increase the generation
        time++;

        // as soon as all the fresh oranges are rotten, return the time immediately
        if (fresh_count == 0)
            return time;
    }

    // all fresh oranges cannot be rotten
    return -1;
}

int main() {
    int m, n;
    std::cout << "\nEnter the number of rows & columns in the maze : ";
    std::cin >> m >> n;

    std::vector<std::vector<int>> maze(m, std::vector<int>(n));
    std::cout << "\nInitialize the maze : \n\n";

    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            std::cin >> maze[i][j];

    const int time = solve(maze);
    if (time == -1)
        std::cout << "\nAll fresh oranges cannot be rotten!";

    else
        std::cout << "\nWe need atleast " << time << " minutes to rot all the oranges";

    std::cout << "\n\n";
    return 0;
}