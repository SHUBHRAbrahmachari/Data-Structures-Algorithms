/*
    Given an MxN maze.
    Each cell consists either of these 3

    g: a gate
    x: obstacle
    o: empty room

    We need to fill every empty room to the distance from its nearest gate.
*/

/*
    Again a classic Multi-Source BFS problem
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <stdexcept>

#define MAX std::numeric_limits<int>::max()

void solve(std::vector<std::vector<int>>& maze) {
    const int m = maze.size();
    const int n = maze[0].size();

    // get a queue for the BFS
    std::queue<std::pair<int, int>> que;

    // get a tracker
    std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));

    // first put all adjacent cells into the queue that are adjacent to a GATE
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (maze[i][j] == 0) {
                // check right
                if (j+1 < n and maze[i][j+1] == MAX and not vis[i][j+1]) {
                    que.emplace(i, j+1);
                    vis[i][j+1] = true;
                }

                // check down
                if (i+1 < m and maze[i+1][j] == MAX and not vis[i+1][j]) {
                    que.emplace(i+1, j);
                    vis[i+1][j] = true;
                }

                // check left
                if (j-1 >= 0 and maze[i][j-1] == MAX and not vis[i][j-1]) {
                    que.emplace(i, j-1);
                    vis[i][j-1] = true;
                }

                // check up
                if (i-1 >= 0 and maze[i-1][j] == MAX and not vis[i-1][j]) {
                    que.emplace(i-1, j);
                    vis[i-1][j] = true;
                }
            }
        }
    }

    // current distance from closest GATE
    int dis = 1;

    // run the BFS
    while (not que.empty()) {
        // see how many empty cells we have got 
        const int size = que.size();

        for (int i=0; i<size; i++) {
            const std::pair<int, int> p = que.front();
            que.pop();

            const int cr = p.first;
            const int cc = p.second;

            // set the minimum distance
            maze[cr][cc] = dis;

            // look for adjacent empty cells
            // check right
            if (cc+1 < n and maze[cr][cc+1] == MAX and not vis[cr][cc+1]) {
                que.emplace(cr, cc+1);
                vis[cr][cc+1] = true;
            }

            // check down
            if (cr+1 < m and maze[cr+1][cc] == MAX and not vis[cr+1][cc]) {
                que.emplace(cr+1, cc);
                vis[cr+1][cc] = true;
            }

            // check left
            if (cc-1 >= 0 and maze[cr][cc-1] == MAX and not vis[cr][cc-1]) {
                que.emplace(cr, cc-1);
                vis[cr][cc-1] = true;
            }

            // check up
            if (cr-1 >= 0 and maze[cr-1][cc] == MAX and not vis[cr-1][cc]) {
                que.emplace(cr-1, cc);
                vis[cr-1][cc] = true;
            }
        }

        // increase distance
        dis++;
    }
}

int main() {
    int m, n;
    std::cout << "\nEnter the number of rows & columns in the maze : ";
    std::cin >> m >> n;

    std::vector<std::vector<int>> maze(m, std::vector<int>(n));
    char ch;
    std::cout << "\nInitialize the maze : \n\n";

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            std::cin >> ch;

            if (ch == 'g')
                maze[i][j] = 0;
            
            else if (ch == 'x')
                maze[i][j] = -1;

            else if (ch == 'o')
                maze[i][j] = MAX;

            else
                throw std::logic_error("undefined input found!");
        }
    }

    solve(maze);

    std::cout << "\n";
    for (int i=0; i<m; i++) {
        std::cout << "\n";
        for (int j=0; j<n; j++) {
            if (maze[i][j] == 0)
                std::cout << "G ";
            
            else if (maze[i][j] == -1)
                std::cout << "X ";

            // N means not reachable
            else if (maze[i][j] == MAX)
                std::cout << "N ";

            else
                std::cout << std::to_string(maze[i][j]) << " ";
        }
    }

    std::cout << "\n";
    return 0;
}

