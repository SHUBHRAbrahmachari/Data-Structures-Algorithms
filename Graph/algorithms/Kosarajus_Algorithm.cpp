/*
    When we talk about "components" in a graph, we generally talk about Undirected Graphs.
    But when we are talking about a Directed graph, you cannot simply say "How many components are there?".

    It would be a very ambiguous question to ask. The reason being in a directed graph, you cannot guarantee that every pair of nodes is reachable from each other.
    Because edges are directed. for directed graphs we have two dedicated terms

    1> Strongly Connected Components (SCCs): A subset of vertices where each pair is reachable from one to another with their corresponding edges.
    2> Weakly Connected Components (WCCs): A maximal subgraph where all vertices are connected if you ignore edge directions (convert all directed edges into undirected ones)

    So you cannot simply ask "how many components are there?" Rather a much more sensible question would be "How many SCCs are there in the graph?"
    This would be the closest analogy against a component in an undirected graph in terms of reachability between pairs.

    To find out Strongly Connected Components (SCCs) in a graph we have a dedicated algorithm known as Kosaraju's Algorithm (Found by S. Rao Kosaraju)

    Intuition:

        Suppose {A, B, C} is a SCC with edges {A->B, B->C and C->A}. Every vertext is reachable to every other vertex. Cool!
        Now suppose you reverse all the edges in the graph! {B->A, C->B & A->C}
        Is every possible pair of vertices still reachable to each other? ABSOLUTELY YES.
        SCC does not bother about reversal of edges. Even if you reverse the edges, a SCC would remain a SCC. Finest observation!

        Now how do we plan to use this? Kosaraju was very clever with it!

        Step 1> Run a DFS and keep pushing the nodes into a stack as soon as the DFS finishes.
                This way we are able to sort the nodes in the order of their finishing time. The node that finishes last remains at top.
                Even if their are disconnected components, it does not matter.

        Step 2> Reverse all the edges. Transpose the graph.
        Step 3> Run a DFS by picking the top node of the stack. See how many nodes it can track down in a single go! that subset becomes your SCC.
                BECAUSE EVEN AFTER REVERSING THE EDGES, IF THE SUBSET IS STILL REACHABLE, THAT IS GUARANTEED TO BE A SCC.

    We will implement the same thing!
*/

#include <iostream>
#include <vector>
#include <stack>
#include "../graph.hpp"

// to stack up the nodes
void dfs1(
    const int node,
    const std::vector<std::vector<Edge>>& adj_list,
    std::stack<int>& st,
    std::vector<bool>& vis  
) {
    if (vis[node])
        return;

    // immediately mark the node as visited
    vis[node] = true;

    // traverse over all the adjacent edges
    for (const auto& edge : adj_list[node]) {
        int target = edge.get_destination();

        // go for further DFS if and only if we have not already visited this node
        if (not vis[target])
            dfs1(target, adj_list, st, vis);
    }

    // once DFS ends, push the node to the stack
    st.emplace(node);
}

// to find out the strongly connected component subset after graph transposition
void dfs2(
    const int node,
    const std::vector<std::vector<Edge>>& adj_rev,
    std::vector<bool>& vis,
    std::vector<int>& ans
) {
    if (vis[node])
        return;

    // immediately mark the node as visited
    vis[node] = true;
    ans.emplace_back(node);

    // traverse over all the adjacent edges
    for (const auto& edge : adj_rev[node]) {
        int target = edge.get_destination();

        // go for further DFS if and only if we have not already visited this node
        if (not vis[target])
            dfs2(target, adj_rev, vis, ans);
    }
}

// O(V+E)
std::vector<std::vector<int>> find_strongly_connected_components(const std::vector<std::vector<Edge>>& adj_list) {
    // see how many nodes you have in your graph. you need this for transposing your graph
    int v = adj_list.size();

    // get a stack to store the nodes
    std::stack<int> st;

    // get a visited array
    std::vector<bool> vis(v, false);

    /*
        One thing to be very clear! This is exactly TOPOLOGICAL SORT what we know.
        But the question is why do we need to collect the TOPOLOGICAL SORT beforehand?

        well there is a very good reason for that! Let me explain!
        The problem is "DFS leakage"!

        Suppose you've two strongly connected components SCC! and SCC2,
        with a single directed edge from SCC1 -> SCC2

        If you start a standard DFS at any node of SCC, the DFS is bound to
        traverse into SCC2. Because standard DFS visits everyting withing reach.
        So it bundles SCC1 and SCC2 together. WRONGLY TREATING THEM AS ONE SINGLE COMPONENT.

        Now why finish time (topological sort) matters?

        When running DFS on the original graph, nodes in SCC1 will finish LAST for sure.

        > DFS enters SCC1
        > DFS follows th edge into SCC2
        > DFS Explores SCC2 completely. SCC2 finishes first and gets plushed into stack.
        > DFS backtracks to SCC1. Only now do SCC1 nodes finish and get placed on top.

        THE TOP OF STACK is  guaranteed to contain a node from SCC1.

        Now comes the edge reversal (graph transposition) trick.
        Any SCC is not botherred by edge reversals BUT now if you start from SCC1,
        YOU WON'T BE ABLE TO GET INTO SCC2 FOR SURE! SO SURELY YOU WILL BE ABLE TO DETECT YOUR SCCs DISTINCTLY!

        THIS IS THE IDEA.

    */
    for (int node=0; node<v; node++) {
        if (not vis[node])
            dfs1(node, adj_list, st, vis);
    }

    /*
        Now we have got the nodes in our stack.
        Now first thing we need to do is that we have to transpose our graph (reverse all the edges)
    */
    std::vector<std::vector<Edge>> adj_rev(v, std::vector<Edge>());

    for (int node=0; node<v; node++) {
        // so that we can re-use the same visited array only this much
        vis[node] = false;

        for (const auto& edge : adj_list[node]) {
            int d = edge.get_destination();
            adj_rev[d].emplace_back(node);
        }
    }

    std::vector<std::vector<int>> scc;

    while (not st.empty()) {
        int node = st.top();
        st.pop();

        if (not vis[node]) {
            std::vector<int> res;
            dfs2(node, adj_rev, vis, res);

            scc.emplace_back(res);
        }
    }

    return scc;
}

int main() {
    const std::vector<std::vector<Edge>> adj_list = unweighted_graph_init();
    const auto scc = find_strongly_connected_components(adj_list);

    std::cout << "\nHere are the strongly connected components : \n\n";
    for (const auto& component : scc) {
        for (const int& node : component)
            std::cout << node << " ";
        std::cout << "\n";
    }

    std::cout << "\n\n";
    return 0;
}