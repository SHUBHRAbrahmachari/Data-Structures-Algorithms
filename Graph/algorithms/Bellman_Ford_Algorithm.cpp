/*
    Bellman Ford Algorithm is again a "Single Source Shortest Path" algorithm.
    Bellman Ford algorithm also provided us minimum cost to reach to every other node from a given source node.

    But we already have Dijkstra's Algorithm. Then why do we need Bellman Ford?
    Dijkstra could not help us with negative edge weights remember? Bellman Ford can sort it out. Although Bellman-Ford is a bit costlier.

    1> Bellman-ford is capable of detecting minimum costs to reach every other node provided that there is no NEGATICE WEIGHT CYCLE in the graph.
    2> If there exists atleast a NEGATIVE WEIGHT CYCLE that is reachable from a given node, Bellman-ford can DETECT it for you.

    Just like Kahn's Algorithm can detect whether a given graph is a DAG or not, Bellman Ford can detect whether a graph is having a NEGATIVE WEIGHT CYCLE (if reachable)

    There is a common misconception that Bellman-Ford can only be implemented on a Directed Graph! Absolutely wrong!
    Bellman Ford can be implemented on both Directed and Undirected graph, The thing is a bit different!

    See in an undirected graph even a single negative edge weight would make Bellman-Ford assume that here is a negative weight cycle. This is why generally come up with this misconception.

    Another huge misconception is that Bellman-Ford can detect any negative weight cycle in a graph. No dear!
    The thing is that the negative weight cycle MUST BE REACHABLE FROM THE GIVEN SOURCE NODE. OTHERWISE BELLMAN-FORD CAN NEVER KNOW ABOUT IT!
    We will see how we detect any negative weight cycle in a graph using same Bellman-Ford certainly, But for now! Let us focus on SINGLE SOURCE SHORTEST PATH

    Given a directed graph with V nodes and M vertices. There could be one or multiple negative weight cycles in the graph.
    If reachable negative weight cycles exists, you don't need to find minimum distances. Otherwise find minimum distances to every other node.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include "../graph.hpp"

#define INF std::numeric_limits<int>::max()

std::vector<int> find_minimum_distances(int src, const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();

    // we want a single distance array that's it!
    std::vector<int> distances(v, INF);

    // distance of source to itself is always 0
    distances[src] = 0;

    // this outer loop would run ATMOST v-1 TIMES. EVEN AFTER THAT IF WE OBSERVE ANY CHANGES, THIS GUARANTEES THAT WE HAVE A NEGATICE WEIGHT CYCLE
    for (int t=1; t<v; t++) {

        // to track relaxation in each iteration
        bool change = false;

        // for every single edge we have to perform relaxation
        for (int node=0; node<v; node++) {
            for (const auto& edge : adj_list[node]) {
                int target_node = edge.get_destination();
                int weight  = edge.get_weight();

                if (distances[node] != INF and distances[node] + weight < distances[target_node]) {
                    distances[target_node] = distances[node] + weight;

                    // yeah we have observed a change, next iteration would be required
                    change = true;
                }
            }
        }

        // early break
        if (not change)
            return distances;
    }

    // if the last iteration comes out  with a change, we must check for a last sprint. If we see a change here, surely negative weight cycle exists
    // for every single edge we have to look for possible relaxation again
    for (int node=0; node<v; node++) {
        for (const auto& edge : adj_list[node]) {
            int target_node = edge.get_destination();
            int weight  = edge.get_weight();

            // found a relaxation. Sure negative weight cycle exists
            if (distances[node] != INF and distances[node] + weight < distances[target_node])
                throw std::logic_error("The graph contains one or multiple reachable negative weight cycle(s). Minimum distances cannot be defined");
        }
    }

    // we did not find any relaxation in the last rep, means minimum distances were found successfully
    return distances;

}

int main() {
    const std::vector<std::vector<Edge>> adj_list = weighted_graph_init();

    int src;
    std::cout << "\nEnter the source node : ";
    std::cin >> src;

    try {
        const std::vector<int> distances = find_minimum_distances(src, adj_list);
        for (int i=0; i<adj_list.size(); i++){
            if (i != src)
                std::cout << "\n\t\t\t\t\t\t\t\t\t" << "Node " << i << " : " << (distances[i] == INF ? "INF" : std::to_string(distances[i]));
        }
    }

    catch (const std::logic_error& e) {
        std::cout << e.what();
    }

    std::cout << "\n\n";
    return 0;
}