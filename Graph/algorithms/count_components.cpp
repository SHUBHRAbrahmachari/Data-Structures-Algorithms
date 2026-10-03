/*
    Given an undirected graph with N vertices and M edges.
    We need to count how many components are there in the graph!
*/

#include <iostream>
#include <vector>
#include <queue>
#include "../graph.hpp"
#include "../disjoint_set.hpp"

void bfs(const int node, const std::vector<std::vector<Edge>>& adj_list, std::vector<bool>& vis) {
    std::queue<int> q;

    q.emplace(node);
    vis[node] = true;

    while (not q.empty()) {
        int curr_node = q.front();
        q.pop();

        for (const auto& edge : adj_list.at(curr_node)) {
            int adj_node = edge.get_destination();

            if (not vis[adj_node]) {
                q.emplace(adj_node);
                vis[adj_node] = true;
            }
        }
    }
}

// O(V+E)
int count_components_bfs(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();
    std::vector<bool> vis(v,false);
    int comps = 0;

    for (int node=0; node<v; node++) {
        if (not vis[node]) {
            /*
                Run a BFS as soon as we find an untouched node.
                This node represents a new component.
                This BFS tracks down every node associated with this particular component so that we do not track them again.
            */
            bfs(node, adj_list, vis);

            /*
                Since this is an undirected graph,
                so in each component every node will be definitely reachable from any other node.
                As soon as the BFS ends that means that we have completed traversing over a component.
                This is what we are counting here.
            */
            comps++;
        }
    }

    /*
        Return the number of components we got!
    */
    return comps;
}

// O((V+E).α(V)) ~ O(V+E)
int count_components_ds(const std::vector<std::vector<Edge>>& adj_list) {
    /*
        this implementation we are going to make using a Disjoint Set data structure.
    */
    const int v = adj_list.size();

    // get a DisjointSet object
    DisjointSet ds(v);

    for (int node=0; node<v; node++) {
        for (const auto& edge : adj_list.at(node)) {
            int node1 = node;
            int node2 = edge.get_destination();

            ds.make_union(node1, node2);
        }
    }

    /*
        Now how do we find out how many compoents do we have?
        Inside that parents array, the count of elements that are parent to themselves will be the number of components wihtut a say!
    */
    
    return ds.count_components();
}

int main() {
    const auto adj_list = unweighted_graph_init();

    int components = count_components_ds(adj_list);
    std::cout << "\nThe number of components are : " << components << "\n\n";

    return 0;
}