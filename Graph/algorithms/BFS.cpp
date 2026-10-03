#include <iostream>
#include <vector>
#include <queue>
#include "../graph.hpp"

void run_bfs(
    int node,
    const std::vector<std::vector<Edge>>& adj_list,
    std::vector<bool>& visited,
    std::vector<int>& ans
) {
    // we need to define a queue first because BFS is actually a level-order traversal
    std::queue<int> que;

    // push the node into the queue and at the same time mark it as visited
    que.emplace(node);
    visited[node] = true;

    while (not que.empty()) {
        int node_self = que.front();
        que.pop();

        // add it to the answer
        ans.emplace_back(node_self);

        // look for the adjacent nodes
        for (const auto& edges: adj_list.at(node_self)) {
            int adj_node = edges.get_destination();

            // add it to queue if and only if we're reaching at this node for the very first time
            if (not visited[adj_node]) {
                que.emplace(adj_node);
                visited[adj_node] = true;
            }
        }
    }
}

std::vector<int> bfs(const std::vector<std::vector<Edge>>& adj_list) {
    int v = adj_list.size();
    std::vector<bool> visited(v, false);
    std::vector<int> ans;

    /*
        Now as mentioned eralier,
        the graph might not be connected.
        So we must traverse all the nodes
    */
    for (int node=0; node<v; node++)
        if (not visited[node])
            run_bfs(node, adj_list, visited, ans);

    return ans;
}

int main() {
    auto adj_list = unweighted_graph_init();
    auto traversal = bfs(adj_list);

    std::cout << "\nHere's the BFS traversal : ";
    for (const int& node : traversal)
        std::cout << node << " ";

    return 0;
}