/*
    Today we will learn another important shortest distance finding algorithm.
    The name of the algorithm is Floyd-Warshall's Algorithm.

    But unlike Dijkstra's Algorithm or Bellman-Ford, Floyd-Warshall is a
    "Multi Source Shortest Path Algorithm"

    Floyd-Warshall helps you to find minimum distances to reach every node from every other node simultaneously!
    That's true. You assume each one to be the source node.

    Floyd-Warshall works in O(V^3).

    Floyd-Warshall is a Dynamic Programming based minimum disance finding algorithm.
    The intuition is very much simple.

    Suppose there is an edge to V from U. 
    You simply say, ok i can reach V from U directly. But what is i go through some other node K and see whether i can reach V with
    a lower cost or not. In simple terms..

    cost[u][v] = min(cost[u][v], cost[u][k]+cost[k][v]) for every other K node in the graph

    This is the simple DP intuition of Floyd-Warshall's Algorithm.

    Floyd-Warshall works for both Directed and Undirected Graphs. Floyd-Warshall
    can also detect negative weight cycle.

    if cost of a node to reach itself goes < 0, we are very sure that there exists atleast one negative weight cycle.
    Floyd-Wasrshall can deterministically find it out!

    But again! Just like Bellman-Ford, in an undirected graph even a single negative edge is enough to confuse floyd-Warshall as a false negative weight cycle detetion.
    So again DO NOT USE IT WITH UNDIRECTED GRAPHS WITH NEGATICE EDGE WEIGHTS!
*/

#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include "../graph.hpp"

#define INF std::numeric_limits<int>::max()

std::vector<std::vector<int>> find_minimum_distances(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    /*
        We need to prepare a cost matrix and then we must initualize it!
    */
    std::vector<std::vector<int>> cost(v, std::vector<int>(v, INF));

    for (int node=0; node<v; node++) {
        cost[node][node] = 0;
        for (const auto& edge : adj_list[node]) {
            int target = edge.get_destination();
            int weight = edge.get_weight();

            cost[node][target] = weight;
        }
    }

    /*
        Initualization Done! Now begins the real game of Floyd-Warshall
    */
    // allow vertex k to be used as intermediate vertex for any pair of vertices
    for (int k=0; k<v; k++) {
        // if starting from this node
        for (int i=0; i<v; i++) {
            // and we want to reach this node
            for (int j=0; j<v; j++) {
                if (cost[i][k] != INF and cost[k][j] != INF)
                    cost[i][j] = std::min(
                        cost[i][j], cost[i][k] + cost[k][j]
                    );
            }
        }
    };

    // negative cycle check
    for (int i=0; i<v; i++)
        if (cost[i][i] < 0)
            throw std::logic_error("Your graph contains one or multiple negative weight cycle(s). So minimum cost is not defined");

    return cost;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();
    const std::vector<std::vector<int>> cost = find_minimum_distances(adj_list);

    try {
        const std::vector<std::vector<int>> cost = find_minimum_distances(adj_list);
        std::cout << " ";
        for (int i=0; i<cost.size(); i++)
            std::cout << "\t" << i << " ";

        std::cout << "\n\n";

        for (int i=0; i<cost.size(); i++) {
            std::cout << i << "\t";
            for (int j=0; j<cost.size(); j++) {
                std::cout << (cost[i][j] != INF ? std::to_string(cost[i][j]) : "INF") << "\t";
            }
            std::cout << "\n";
        }
    }

    catch (const std::logic_error& e) {
        std::cout << e.what() << "\n\n";
    }

    std::cout << "\n\n";
    return 0;
}