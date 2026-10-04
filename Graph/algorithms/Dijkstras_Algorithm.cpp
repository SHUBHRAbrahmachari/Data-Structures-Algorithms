/*
    Given an undirected/directed graph with non-negative edge weights!
    You are also given a source node.

    Find out minimum possible costs to reach every other node from source node.
    If a node is not reachable put INT_MAX. 

    We see Dijkstra's Algorithm Here.
    Dijkstra's Algorithm is a "Single Source Shortest Path" algorithm that finds otu minimum distance to every other node from
    a given source node.
    Dijkstra's Algorithm ccan be implemented on both Undirected and Directed graph. 
    The only constraint with Dijkstra's Algorithm is that, Dijkstra's Algorithm cannot work when your graph contains NEGATIVE EDGE WEIGHTS.

    Apart from negative edge weights, Dijkstra's Algorithm works in O(ElogV)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "../graph.hpp"

#define INF std::numeric_limits<int>::max()

/*
    A custom comparator to compare Edge objects
*/
class Comparator {
    public:
        // min-heap configuration is required so '>' operator is overridden
        bool operator()(const Edge& e1, const Edge& e2) const {
           return e1.get_weight() > e2.get_weight();
        }
};

// O(ElogV)
std::vector<int> find_minimum_distances(const int src, const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    // need to get a priority queue (min heap) first which makes sure we pick up a node with minimum reaching distance first
    std::priority_queue<Edge, std::vector<Edge>, Comparator> pq;

    // we also need to have a visited array
    std::vector<int> vis(v, false);

    // we also need to have a distances array to track minimum distances
    std::vector<int> dis(v, INF);

    // initialize Dijkstra's algorithm
    pq.emplace(src, 0);
    dis[src] = 0;

    /*
        Since we see every node only once, we will mark it visited only when we pick it out.
        We will ignore the node if it has already been marked, we will also put it if it has not already been tracked. Just a little optimization.
    */
    while (not pq.empty()) {
        int node = pq.top().get_destination();
        int weight = pq.top().get_weight();
        pq.pop();

        /*
            This is a little optimization part. Think about it carefully.
            Suppose first time you pushed (5, 10) into your priority queue. Nice!
            But before even fethcing it, you again pushed (5, 8) into your priority queue.

            Now when you tackle 5, according to priority queue you will receive (5, 8) and not (5, 10) right?
            After consideration of (5, 8), Do you think considering (5, 10) again makes any sense? Ofcourse not.

            Even in future if you again come up with 5, you must have come back through a loop only, and that loop would cost higher only.
            So every node is entertained atmost once only.
            To prevent unnecessary computation, we have implemented this step. You could have avoided it.
            But in that case you would up ended up doing a lot of unnecessary computation.
        */
        if (not vis[node]) {
            // immediately mark this node as visited
            vis[node] = true;

            // look which nodes we can visit from this node
            for (const auto& edge : adj_list[node]) {
                int target_node = edge.get_destination();
                int add_weight = edge.get_weight();

                // we got a better path with lower cost
                if (weight + add_weight < dis[target_node]) {

                    // update with lower cost
                    dis[target_node] = weight + add_weight;

                    // push this candidate into the priority queue
                    pq.emplace(target_node, dis[target_node]);
                }
            }
        }
    }

    return dis;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();
    
    int src;
    std::cout << "\nEnter the source node : ";
    std::cin >> src;

    std::vector<int> distances = find_minimum_distances(src, adj_list);

    for (int i=0; i<adj_list.size(); i++) {
        if (i != src) {
            std::cout << "\n\t\t\t\t\t\t\t\t\tNode " << i << " -> " << (distances[i] != INT_MAX ? std::to_string(distances[i]) : "INF"); 
        }
    }

    std::cout << "\n\n";

    return 0;
}