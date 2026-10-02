#include <iostream>
#include <vector>
#include "edge.hpp"

class UndirectedGraph {
    public:
        static std::vector<std::vector<Edge>> init(int v, std::vector<std::vector<int>> edges, bool weighted=false) {
            std::vector<std::vector<Edge>> adj_list(v, std::vector<Edge>());

            for (auto edge : edges) {
                int source = edge[0];
                int destination = edge[1];
                int weight = weighted ? edge[2] : 0;

                // because the edges are undirected so two-way communication has to be there
                adj_list.at(source).emplace_back(destination, weight);
                adj_list.at(destination).emplace_back(source, weight);
            }

            return adj_list;
        }
};

class DirectedGraph {
    public:
        static std::vector<std::vector<Edge>> init(int v, std::vector<std::vector<int>> edges, bool weighted=false) {
            std::vector<std::vector<Edge>> adj_list(v, std::vector<Edge>());

            for (auto edge : edges) {
                int source = edge[0];
                int destination = edge[1];
                int weight = weighted ? edge[2] : 0;

                adj_list.at(source).emplace_back(destination, weight);
            }

            return adj_list;
        }
};

void show_adjacency_list(const std::vector<std::vector<Edge>>& adj_list, bool weighted=false) {
    std::cout << std::endl;
    int size = adj_list.size();

    for (int s=0; s<size; s++) {
        std::cout << "\t\t\t\t\t\t\t\t\t";
        std::cout << s << " : ";
        for (auto edge : adj_list.at(s))
            if (weighted)
                std::cout << "(" << edge.get_destination() << ", " << edge.get_weight() << ") ";
            else
                std::cout << edge.get_destination() << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    return;
}