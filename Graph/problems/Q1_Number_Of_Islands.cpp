/*
    An island is formed by joining two or multiple adjacent lands.
    Two diagonally consecutive lands can not be called adjacent.

    A land is defined by a 1 in a 2D maze.
    Water is denoted by 0.

    Given such a maze of size N x N , we need to find out the number of lands in a maze.

    1 <= N <= 10^5
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

// O(N^2)
void bfs(const std::vector<std::vector<int>>& maze, std::vector<std::vector<bool>>& vis, const int r, const int c) {
    const int n = maze.size();

    // get a queue for BFS
    std::queue<std::pair<int, int>> que;

    // initialize the queue
    que.emplace(r, c);
    vis[r][c] = true;

    // run a bfs from this cell
    while (not que.empty()) {
        // fetch the front land
        const std::pair<int, int> land = que.front();
        que.pop();

        const int cr = land.first;
        const int cc = land.second;

        // check right
        if (cc+1 < n and maze[cr][cc+1] == 1 and not vis[cr][cc+1]) {
            que.emplace(cr, cc+1);
            vis[cr][cc+1] = true;
        }

        // check down
        if (cr+1 < n and maze[cr+1][cc] == 1 and not vis[cr+1][cc]) {
            que.emplace(cr+1, cc);
            vis[cr+1][cc] = true;
        }

        // check left
        if (cc-1 >= 0 and maze[cr][cc-1] == 1 and not vis[cr][cc-1]) {
            que.emplace(cr, cc-1);
            vis[cr][cc-1] = true;
        }

        // check up
        if (cr-1 >= 0 and maze[cr-1][cc] == 1 and not vis[cr-1][cc]) {
            que.emplace(cr-1, cc);
            vis[cr-1][cc] = true;
        }
    }
}

int solve(const std::vector<std::vector<int>>& maze) {
    const int n = maze.size();

    // keep a counter to keep track of islands
    int count = 0;

    // keep a tracker to track already visited lands
    std::vector<std::vector<bool>> vis(n, std::vector<bool>(n, false));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (maze[i][j] == 1 and not vis[i][j]) {
                bfs(maze, vis, i, j);
                count++;
            }
        }
    }

    return count;
}

int main() {
    int n;
    std::cout << "\nEnter the size of the maze : ";
    std::cin >> n;

    std::vector<std::vector<int>> maze(n, std::vector<int>(n));

    std::cout << "\nInitialize the maze : \n\n";
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            std::cin >> maze[i][j];

    const int count = solve(maze);
    std::cout << "\nThere are " << count << " island(s) in the maze\n\n";

    return 0;
}