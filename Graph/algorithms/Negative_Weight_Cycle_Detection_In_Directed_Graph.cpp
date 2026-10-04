/*
    This time we will use the same Bellman-Ford algorithm to detect ANY existing NEGATIVE WEIGHT CYCLE IN A DIRECTED GRAPH.
    We have to simply tweak the algorithm a little. That's all.

    with initial consfiguration of Bellman-ford, which we were using to find out minimum distances could not certainly detect a negative weight cycle because....
    We were tightly coupling the algorithm with a starting node. This time. Our target is purely detecting the negative weight cycle.

    For this purpose, we will initialize our distances array with all 0s this time. Why?
    Very simple! See when you initialize the distances array with all 0s, we simulate every node is the source node.
    Therefore there's no question of unreachability against a particular node. We will always be able to relax weights.

    And if negative weight cycle exists, costs will keep decreasing for sure. We have to catch this only. We call it a "Virtual Super Source" trick!
*/

#include <iostream>
#include <vector>
#include "../graph.hpp"

// O(V.E)
bool does_cycle_exist(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    std::vector<int> distances(v, 0);

    for (int i=1; i<v; i++) {
        bool change = false;

        for (int node=0; node<v; node++) {
            for (const auto& edge : adj_list[node]) {
                int target = edge.get_destination();
                int weight = edge.get_weight();

                if (distances[node] + weight < distances[target]) {
                    distances[target] = distances[node] + weight;
                    change = true;
                }
            }
        }

        // same early break
        if (not change)
            return false;
    }

    for (int node=0; node<v; node++) {
        for (const auto& edge : adj_list[node]) {
            int target = edge.get_destination();
            int weight = edge.get_weight();

            // found a further relaxation
            if (distances[node] + weight < distances[target]) 
                return true;

        }
    }

    return false;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();
    if (does_cycle_exist(adj_list))
        std::cout << "\nThere exists one or multiple negative weight cycle(s)";
    else
        std::cout << "\nThere are no negative weight cycles";

    return 0;
}