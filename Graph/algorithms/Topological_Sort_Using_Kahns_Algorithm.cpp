/*
    The same problem of finding a topological sort can also be implemented using Kahn's Algorthm.

    Kahn's Algorithm is a BFS based approach which not only figures out a valid topologically sorted sequence of vertices,
    but also it verifies whether your directed graph has a cycle in it or not.

    It is possible because of its underlying property of tracking INDEGREES of nodes.

    Initially we need to count indegree of each and every node in our node in our graph.
    We push every such node having an indegree 0 to our queue.
    Once a node is done visiting, we simulate removing this node from the graph.
    At the end we will have a topological sort of size exactly V if the input graph was a DAG in nature.
    Otherwise the topological sort would not contain exactly V vertices because at some point there would not be any node with indegree exactly 0.
    So we won't be able to push anyone into the queue and our BFS will stop.

    WE DO NOT EVEN NEED A VISITED ARRAY HERE. Since the indegree[] array filters which nodes to fit explicitly.

    TIP: WHENEVER SOMEONE ASKS YOU TO FIND WHETHER THERE EXISTS A CYCLE IN A DIRECTED GRAPH OR NOT, USE Kahn's Algorithm to answer that.

    Let's see how we do it!
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include "../graph.hpp"

// O(V+E)
std::vector<int> topological_sort(const std::vector<std::vector<Edge>>& adj_list) {
    // see how many nodes do we have
    const int v = adj_list.size();

    // now we need to maintain a indegrees[] array to check indegrees for each node dynamically
    std::vector<int> indegrees(v, 0);

    // Kahn's algorithm uses a queue to process currently available vertices. Similar to BFS but a bit tweaked.
    std::queue<int> q;

    // finally we need a answer array which we are supposed to return
    std::vector<int> topo;

    /*
        Step 1> we need to count indegrees for each and every node
    */
    for (int node=0; node<v; node++) {
        for (const auto& edge : adj_list[node]) {
            int adj_node = edge.get_destination();
            indegrees[adj_node]++; 
        }
    }

    /*
        Step 2> we need to push each and every node to queue which are having indegree exactly 0
    */
    for (int i=0; i<v; i++) {
        if (indegrees[i] == 0)
            q.emplace(i);
    }

    /*
        Now while doing a BFS , i do not even need to look for every node explicitly.
        The reason being that we are pushing the nodes into the queue based on their indegrees being 0.
        So even if there are multiple components we are making sure that there is atleast one node from each component into the queue at first.
        So naturally we end up traversing the whole graph
    */
    while (not q.empty()) {
        int node = q.front();
        topo.emplace_back(node);
        q.pop();
            
        // We conceptually remove this node and all of its outgoing edges.
        // Therefore, decrease the indegree of every adjacent node.
        for (const auto& edge : adj_list[node]) {
            int adj_node = edge.get_destination();
            indegrees[adj_node]--;

            // if you find some adjacent node's indegree becoming 0, push it to queue
            if (indegrees[adj_node] == 0)
                q.emplace(adj_node);
        }
    }

    /*
        if the size of the topo array is not equal to V itself,
        We are damn sure that there is a cycle in our graph.
        Hence this is not a DAG & therefor topological sort is UNDEFINED
    */
    if (topo.size() < v)
        throw std::logic_error("\t\t\t\t\t\tThis graph consists of one or multiple cycles. Therefore topological sort is undefined");

    return topo;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();

    try {
        const std::vector<int> topo = topological_sort(adj_list);
        std::cout << "\nHere's the topological sort : ";
        for (const int& ele : topo)
            std::cout << ele << " ";
    } catch (const std::logic_error& e) {
        std::cout << e.what() << "\n\n";
    }

    return 0;

}