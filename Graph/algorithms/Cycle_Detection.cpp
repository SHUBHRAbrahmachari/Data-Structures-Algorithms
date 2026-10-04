/*
    Given an undirected graph with V nodes and M edges.
    You need to find if there exists a cycle in the graph.

    Note: do not consider a single edge as a cycle
*/

#include <iostream>
#include <vector>
#include "../graph.hpp"

/*
    In an undirected graph, every edge appears in both endpoint's adjacency lists.
    Therefore, when traversing from a node to its neighbor, that neighbor will see the current node as an already-visited node.
    We must ignore the edge back to the parent, otherwise every ordinary edge would be incorrectly identified as a cycle.
*/

bool search_cycle(
    const std::vector<std::vector<Edge>>& adj_list,
    const int curr_node,
    const int par_node,
    std::vector<bool>& vis
) {
    // We reached an already-visited node through a non-parent edge,
    // which means that a cycle exists.
    if (vis[curr_node])
        return true;

    // mark this node as visited
    vis[curr_node] = true;

    for (const auto& edge : adj_list.at(curr_node)) {
        const int adj_node = edge.get_destination();

        // since reaching at a visited node gives us the cycle, we must go to every adjacent node but not the parent node
        if (adj_node != par_node) {
            // if this search returns false, we must check for other adjacent nodes as well.
            if (search_cycle(adj_list, adj_node, curr_node, vis))
                return true;
        }
    }

    // this is for a single node, who only has the parent as adjacent node (terminal nodes)
    return false;
}

bool does_cycle_exist(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();
    std::vector<bool> vis(v, false);

    for (int node=0; node<v; node++) {
        // try traversing from this node if and only if we have not explored this node yet!
        if (not vis[node]) {

            // look for a cycle in this component. If we find one we simply return true. Else we wait and check for next components
            // -1 means no previous parent exists for this node
            if (search_cycle(adj_list, node, -1, vis))
                return true;
        }
    }

    // in case we have not found a single cycle in any of the components.
    return false;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();

    if (does_cycle_exist(adj_list))
        std::cout << "\nCycle exists in this graph!\n\n";
    else    
        std::cout << "\nCycle does not exist in the graph!\n\n";

    return 0;
}