/*
    Before discussing about Kruskal's Algorithm, we must know what is a spanning Tree!
    
    "   A Spanning Tree is simply undirected graph and V nodes and exactly V-1 edges such that there exists NO CYCLE in the graph
        and EVERY NODE IS REACHABLE FROM EVERY OTHER NODE IN THE GRAPH!
    "

    Baiscally you are suuposed to have a single component where every node is reachable to every other node without any cycles being present.
    Such an undirected graph is called a Spanning Tree.

    One Undirected Graph can have multiple Spanning Trees. Out of all those spanning trees, the set of spanning trees whose sum of edge weights is minimum,
    we call them the Minimum Spanning Tree (MST).

    When the edge weights are unique, there will always be a single unique MST. Otherwise you can have multiple MSTs as well.
    Kruskal's Algorithm is such a famous algorithm to find MST out of an Undirected Graph.
    Kruskal's Algorithm uses DisjointSet data structure to dynamically figure our connection between nodes to avoid cycle formation.
    Let's see how we do it! Kruskal's Algorithm is a greedy algorithm.

    Kruskal's Algorithm is edge-centric algorithm which is faster for sparse graphs i.e. |E| << |V^2|
    But for dense graphs, we have another thing called Prim's Algorithm which is faster on dense graphs i.e. |E| ~ |V^2|.

    SPANNING TREES ARE A CONCEPT ONLY DEFINED FOR UNDIRECTED GRAPHS.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "../graph.hpp"
#include "../disjoint_set.hpp"

class Comparator {
    public:
        bool operator()(const std::vector<int>& edge1, const std::vector<int>& edge2) const {
            return edge1[2] < edge2[2];
        }
};

// returns a valid graph only (MST) as a adjacency list
// O(ElogE + E.alpha(V))
std::vector<std::vector<Edge>> find_mst(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    /*
        We need to collect the complete edges in the form of {U, V, W} and sort them in ascending order of weights.
    */
    std::vector<std::vector<int>> edges;

    for (int node=0; node<v; node++) {
        for (const auto& edge : adj_list[node]) {
            int target = edge.get_destination();
            int weight = edge.get_weight();

            const std::vector<int> new_edge = {node, target, weight};
            edges.emplace_back(new_edge);
        }
    }

    // sort them
    std::sort(edges.begin(), edges.end(), Comparator());

    // get a DisjointSet data- structure to keep track of connected compnents.
    // So that we don't accidentally add loops/cycles in our MST
    DisjointSet ds(v);

    // get you mst
    std::vector<std::vector<Edge>> mst(v, std::vector<Edge>());

    int edge_count = 0;

    for (const auto& edge : edges) {
        int s = edge[0];
        int d = edge[1];
        int w = edge[2];

        // if and only if they are not connected
        if (not ds.is_connected(s, d)) {
            ds.make_union(s, d);
            mst[s].emplace_back(d, w);
            mst[d].emplace_back(s, w);
            edge_count++;
        }

        // small optimization as early break as soon as we hit exactly V-1 edges
        if (edge_count == v-1)
            break;
    }

    return mst;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();
    const std::vector<std::vector<Edge>> mst = find_mst(adj_list);

    show_adjacency_list(mst);

    return 0;
}