#include <iostream>
#include <vector>
#include "../graph.hpp"

/*
    This is a pre-order DFS approach.
    If you want a post-order DFS appraoch just do not add the node into ans before checking its adjacent nodes.
    Simply add the node after loop ends. Only this much change.
*/
void solve_dfs_preorder(
    int node,
    const std::vector<std::vector<Edge>>& adj_list,
    std::vector<bool>& visited,
    std::vector<int>& ans
) {
    if (visited[node])
        return;
    
    // push it into your answer and mark it as visited
    ans.emplace_back(node);
    visited[node] = true;

    // we don't need to copy the whole arary of edges, just keep a reference
    for (const auto& edge : adj_list.at(node)) {
        int adj_node = edge.get_destination();

        if (not visited[adj_node])
            solve_dfs_preorder(edge.get_destination(), adj_list, visited, ans);
    }
}

std::vector<int> dfs(const std::vector<std::vector<Edge>>& adj_list) {
    int v = adj_list.size();
    std::vector<bool> visited(v, false);
    std::vector<int> ans;


    for (int node=0; node<v; node++) {
        if (not visited[node])
            solve_dfs_preorder(node, adj_list, visited, ans);
    }

    return ans;
}

int main() {
    /*
        Since we are going to implement DFS here, We for now do not require any sort of weights.
        So we will be using a Unweighted undirected graph for this.

        DFS can be implemented on both directed and undirected graph.
        No matter on what you are implementing it make sure, you visit one node exactly once.
        But because there could be multiple components, so make sure you traverse from all the nodes.
    */

    auto adj_list = unweighted_graph_init();
    auto traversal = dfs(adj_list);

    std::cout << "\nHere's the DFS traversal of the graph : ";
    for (int node : traversal)
        std::cout << node << " ";

    return 0;
}