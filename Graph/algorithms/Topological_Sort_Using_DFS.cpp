/*
    We are given a Directed Acyclic Graph with N nodes and M edges.
    We are required to find any valid Topologically Sorted order of the vertices.

    First of all, A topological sort is only valid in case of a DAG. Why?
    To know whu we must understand the DEFINITION of TOPOLOGICAL SORT first.

    "   In a directed graph, if there is an edge U → V, then U must appear
        before V in the topological ordering, indicating that U is a
        prerequisite/dependency of V.

        There may be other vertices between U and V; only their relative
        order matters.

        If a linear ordering of all vertices satisfies this condition for
        every directed edge in the graph, that ordering is called a
        TOPOLOGICAL ORDERING (or TOPOLOGICAL SORT) of the graph.
    "
    Why Directed?
        -> without a directed edge, how would you define who is the pre-requisite of whom? This is why directed edges are required.
    Why Acyclic?
        -> Since we are talking about pre=requisites, Does that make any sense when we have circular dependencies in our Graph?
           Like this way! U -> V -> U (who is the pre-requiste of whom?)

    Whenever you hear something like it before it or this after this, from now on think about topological sort this might help a lot.
    There are two ways to implement topological sort.

    1> Simple pre-order DFS with a stack (this one would not verify whether the graph is a DAG or not)
    2> Kahn's Algorithm (BFS approach). This one first verifies whether the graph is a DAG or not then only returns a valid topological sort.
       Kahn's Algorithm is the true standard.

    Here we will explicilty make sure that the graph is a DAG since we will be implementing DFS+stack approach
*/

#include <iostream>
#include <vector>
#include <stack>
#include "../graph.hpp"

void dfs(
    const std::vector<std::vector<Edge>>& adj_list,
    std::vector<bool>& vis,
    std::stack<int>& st,
    int node
) {
    if (vis[node])
        return;

    // mark this node as visited
    vis[node] = true;

    for (const auto& edge : adj_list[node]) {
        int adj_node = edge.get_destination();

        if (not vis[adj_node])
            dfs(adj_list, vis, st, adj_node);
    }

    // we need to push this node into our stack as soon as DFS ends from this node
    st.push(node);
}

std::vector<int> topological_sort(const std::vector<std::vector<Edge>>& adj_list) {
    const int v = adj_list.size();
    std::vector<bool> vis(v, false);
    std::stack<int> st;

    for (int node=0; node<v; node++) {
        if (not vis[node])
            dfs(adj_list, vis, st, node);
    }

    std::vector<int> topo;
    while (not st.empty()) {
        topo.emplace_back(st.top());
        st.pop();
    }

    return topo;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();
    const std::vector<int> topo = topological_sort(adj_list);

    std::cout << "\nHere's the topologically sorted order of vertices : ";
    for (const int& ele : topo)
        std::cout << ele << " ";

    return 0;
}

