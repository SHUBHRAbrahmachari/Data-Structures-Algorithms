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


std::vector<std::vector<Edge>> unweighted_graph_init() {
    int v;
    std::cout << "\nEnter the number of nodes you want : ";
    std::cin >> v;

    int m;
    std::cout << "\nEnter the number of edges you want : ";
    std::cin >> m;

    bool directed;
    std::cout << "\nDo you want your graph to be directed? (0/1) : ";
    std::cin >> directed;

    std::vector<std::vector<int>> edges(m, std::vector<int>(2));
    std::cout << "\nKeep entering the edges : \n\n";
    for (int i=0; i<m; i++)
        std::cin >> edges.at(i).at(0) >> edges.at(i).at(1);

    if (directed)
        return DirectedGraph::init(v, edges, false);
    else
        return UndirectedGraph::init(v, edges, false);
}

std::vector<std::vector<Edge>> weighted_graph_init() {
    int v;
    std::cout << "\nEnter the number of nodes you want : ";
    std::cin >> v;

    int m;
    std::cout << "\nEnter the number of edges you want : ";
    std::cin >> m;

    bool directed;
    std::cout << "\nDo you want your graph to be directed? (0/1) : ";
    std::cin >> directed;

    std::vector<std::vector<int>> edges(m, std::vector<int>(3));
    std::cout << "\nKeep entering the edges : \n\n";
    for (int i=0; i<m; i++)
        std::cin >> edges.at(i).at(0) >> edges.at(i).at(1) >> edges.at(i).at(2);

    if (directed)
        return DirectedGraph::init(v, edges, true);
    else
        return UndirectedGraph::init(v, edges, true);
}

void show_adjacency_list(const std::vector<std::vector<Edge>>& adj_list) {
    std::cout << std::endl;
    int size = adj_list.size();

    for (int s=0; s<size; s++) {
        std::cout << "\t\t\t\t\t\t\t\t\t";
        std::cout << s << " : ";
        for (auto edge : adj_list.at(s))
            std::cout << "(" << edge.get_destination() << ", " << edge.get_weight() << ") ";

        std::cout << std::endl;
    }

    std::cout << std::endl;
    return;
}