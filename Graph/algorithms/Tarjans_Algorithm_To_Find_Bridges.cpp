/*
    Before we jump into Tarjan's Algorithm. We need to understand the concept of bridges.

    A BRIDGE is strictly defined for an undirected graph only.
    A BRIDGE IS SUCH AN EDGE AN UNDIRECTED GRAPH, WHOSE REMOVAL BREAKS THE GRAPH INTO TWO OR MULTIPLE COMPONENTS.

    Tarjan's Algorithm is a DFS based algorithm that finds you the bridges in a given undirected graph.
    Tarjan's Algorithm works in O(V+E) since it's a DFS based approach.

    Using the same Idea we will also find out Articulation points (a little tweaked), but for now let us focus on
    finding out bridges.
*/

#include <iostream>
#include <vector>
#include <utility>
#include "../graph.hpp"

void dfs(
    const int curr_node,
    const int parent_node,
    const std::vector<std::vector<Edge>>& adj_list,
    std::vector<std::pair<int, int>>& bridges,
    std::vector<bool>& vis,
    std::vector<int>& tin,
    std::vector<int>& low,
    int& time
) {
    // if node is already visited we do nothing
    if (vis[curr_node])
        return;

    // immediately mark the node as visited
    vis[curr_node] = true;

    // also update the time at which the node is discovered
    tin[curr_node] = low[curr_node] = time++;

    for (const auto& edge : adj_list[curr_node]) {
        int adj_node = edge.get_destination();

        // if not visited yet, go and complete your DFS first!
        if (not vis[adj_node])
            dfs(adj_node, curr_node, adj_list, bridges, vis, tin, low, time);

        // update your low value from every adjacent nodes at the same time. EXCEPT the parent node
        if (adj_node != parent_node)
            low[curr_node] = std::min(low[curr_node], low[adj_node]);   
    }

    /*
        As soon as the DFS ends, the current node checks if the EDGE between him and the parent node can be a bridge or not!
        How? curr_node looks asks the parent "Hey parent, what is your discovery time?"
        If the parent's dicovery time is >= curr_node's low[] value, we can surely say that this edge is NOT A BRIDGE.
        REASON? THERE HAS TO BE ANOTHER CONNECTION THROUGH WHICH THE PARENT CAN BE REACHED FOR SURE! THIS IS WHY WE DO NOT CONSIDER THE PARENT NODE!

        OTHERWISE THE EDGE IS SURELY A BRIDGE!
    */
    if (parent_node != -1 and low[curr_node] > tin[parent_node])
        bridges.emplace_back(curr_node, parent_node);
}

// O(V+E)
std::vector<std::pair<int, int>> find_bridges(const std::vector<std::vector<Edge>>& adj_list) {
    // see how many nodes we have to deal with
    const int v = adj_list.size();

    /*
        As Tarjan's Algorithm is a DFS based algorithm so we must have the generic pre-requisites as usual.
        We need the visited array.
    */
    std::vector<bool> vis(v, false);

    /*
        Apart from that, Tarjan adds further:

            > tin[]: the time at which a node is discovered in the DFS
            > low[]: the minimum time of insertion of every adjacent node including the node itself EXCEPT the parent node
    */
    int time = 0;
    std::vector<int> tin(v);
    std::vector<int> low(v);

    /*
        We need a container to store all the bridges we detect
    */
    std::vector<std::pair<int, int>> bridges;

    /*
        Now we finally run the DFS
    */
    for (int node=0; node<v; node++) {
        if (not vis[node])
            dfs(node, -1, adj_list, bridges, vis, tin, low, time);
    }

    return bridges;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();

    const std::vector<std::pair<int, int>> bridges = find_bridges(adj_list);

    if (bridges.size() == 0)
        std::cout << "\nThere are no bridges in the graph\n\n";

    else {
        std::cout << "\nHere are the bridges : \n\n";
        for (const auto& bridge : bridges)
            std::cout << bridge.first << " - " << bridge.second << "\n";
    }

    std::cout << "\n\n";
    return 0;
}