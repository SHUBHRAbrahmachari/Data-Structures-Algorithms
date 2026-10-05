/*
    Pre-requisite: Spanning Tree, Minimum Spanning Tree (MST) & Kruskal's Algorithm using DisjointSet data structure.

    We have already learned about Spanning Trees and Minimum Spanning Trees. We also know how to generate a MST out of an undirected graph using Kruskal's Algorithm.
    Kruskal's Algorithm works really well and fast in most of real life scenarios where we face sparse graphs i.e. |E| << |V^2|

    But for dense graphs i.e. |E| ~ |V^2| we have a faster algorithm to find MST that is the Prim's Algorithm.
    Prim's Algorithm is a node-centric algorithm. You can start with any node of your choice, it does not count.

    Prim's Algorithm is a node centric MST finding algorithm working in O(ElogV)
*/

#include <iostream>
#include <vector>
#include <queue>
#include "../graph.hpp"

class Comparator {
    public:
        bool operator()(const std::vector<int>& edge1, const std::vector<int>& edge2) const {
            return edge1[2] > edge2[2];     // since we need min-heap
        }
};

// O(ElogV)
std::vector<std::vector<Edge>> find_mst(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    /*
        we need to collect all the edges in a min-heap
    */
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Comparator> pq;

    /*
        We would again require a visited array here.
        Think it like since we are not using DisjointSet class here, we must keep a track of connected components.
        So we must explicitly maintain a visited array
    */
    std::vector<bool> vis(v, false);

    /*
        Get you mst to store selected edges
    */
    std::vector<std::vector<Edge>> mst(v, std::vector<Edge>());

    /*
        As said earlier, we can start with any node. That won't matter since your MST would anyhow contain every node right?
        Let's start with 0.

        These two conditions are to be kept in mind:
            1> We will consider a node if and only if it is not earler visited.
            2> We will again only consider to push a node if and only if it is not visited earlier.
    */
    std::vector<int> FIRST_EDGE = {0, -1, -1};      // node is 0, we are coming from nowhere and weight is also not there. This is a fake edge
    pq.emplace(FIRST_EDGE);

    while (not pq.empty()) {
        const auto edge = pq.top();
        int node = edge[0];
        int parent = edge[1];     // if this is -1 we know that this is a fake edge
        int weight = edge[2];
        pq.pop();

        // only consider the node if and only if not already visited
        if (not vis[node]) {
            // mark the node to be visited immediately
            vis[node] = true;

            // yes we can add this edge to our MST
            if (parent != -1) {
                mst[node].emplace_back(parent, weight);
                mst[parent].emplace_back(node, weight);
            }

            // look for the adjacent nodes
            for (const auto& edge : adj_list[node]) {
                int adj_node = edge.get_destination();
                int next_weight = edge.get_weight();

                // only consider it pushing into the min-heap if and only if the adj_node is not yet visited
                if (not vis[adj_node]) {
                    std::vector<int> new_edge = {adj_node, node, next_weight};
                    pq.emplace(new_edge);
                }
            }
        }
    }

    return mst;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();
    const auto mst = find_mst(adj_list);

    show_adjacency_list(mst);
    return 0;
}