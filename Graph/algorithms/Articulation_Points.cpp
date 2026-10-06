/**
 * An articulation point is a vertex in an undirected graph whose removal
 * increases the number of connected components in its component.
 *
 * This DFS-based Tarjan algorithm finds all articulation points in O(V + E).
 */

#include <iostream>
#include <vector>
#include "../graph.hpp"

void dfs(
    const int curr_node,
    const int par_node,
    const std::vector<std::vector<Edge>>& adj_list,
    std::vector<bool>& vis,
    std::vector<bool>& marker,
    std::vector<int>& tin,
    std::vector<int>& low,
    int& time
) {
    /** Each vertex is entered once; this also protects against revisiting it. */
    if (vis[curr_node])
        return;

    /** Mark the vertex before exploring its neighbors. */
    vis[curr_node] = true;

    /**
     * tin is the DFS discovery time. low is the earliest discovery time
     * reachable from this vertex or its DFS descendants using tree edges
     * and at most one back edge.
     */
    tin[curr_node] = low[curr_node] = time++;

    /** Count DFS-tree children; the root uses this count for its special rule. */
    int count = 0;

    /** Explore the DFS tree and update low-link values for each neighbor. */
    for (const auto& edge : adj_list[curr_node]) {
        int adj_node = edge.get_destination();

        if (not vis[adj_node]) {
            /** This unvisited neighbor becomes a child in the DFS tree. */
            dfs(adj_node, curr_node, adj_list, vis, marker, tin, low, time);
            count++;

            /** The child's reachable ancestors may also be reachable from this vertex. */
            low[curr_node] = std::min(low[curr_node], low[adj_node]);

            /*
             * For a non-root vertex, this child subtree becomes disconnected
             * when curr_node is removed if it cannot reach an ancestor of
             * curr_node. Equality counts: reaching curr_node itself is not
             * enough once curr_node is removed.
            */
            if (par_node != -1 and low[adj_node] >= tin[curr_node])
                marker[curr_node] = true;
        }

        else {
            /**
             * In a simple undirected graph, ignore the edge back to the DFS
             * parent. Any other visited neighbor gives a back-edge candidate;
             * use its discovery time rather than its low value.
             */
            if (adj_node != par_node)
                low[curr_node] = std::min(low[curr_node], tin[adj_node]);
        }
    }

    /**
     * Removing a DFS root separates one component for each of its DFS-tree
     * children, so it is an articulation point only when it has at least two.
     */
    if (par_node == -1 and count > 1)
        marker[curr_node] = true;
}

std::vector<int> find_articulation_points(const std::vector<std::vector<Edge>>& adj_list) {
    /** The adjacency list contains one entry per vertex. */
    const int v = adj_list.size();

    /** Track DFS state and the discovery/low-link times for every vertex. */
    std::vector<bool> vis(v, false);
    std::vector<int> tin(v), low(v);

    /** A marker prevents adding the same articulation point more than once. */
    std::vector<bool> marker(v, false);
    int time = 0;

    /** Start a DFS in every component, including disconnected components. */
    for (int node=0; node<v; node++)
        if (not vis[node])
            dfs(node, -1, adj_list, vis, marker, tin, low, time);

    std::vector<int> articulation_points;
    /** Scan in vertex order so the returned points are also sorted. */
    for (int i=0; i<v; i++)
        if (marker[i])
            articulation_points.emplace_back(i);

    return articulation_points;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();
    const std::vector<int> ap = find_articulation_points(adj_list);

    if (ap.size() == 0)
        std::cout << "\nThere are no articulation points in the graph";
    else {
        std::cout << "\nThe articulation points are : ";
        for (int node : ap)
            std::cout << node << " ";
    }

    std::cout << "\n\n";
    return 0;
}