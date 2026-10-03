#include <vector>
#include <stdexcept>

/*
    We use union by size instead of union by rank.
    
    Both strategies keep the DSU trees shallow, especially when combined
    with path compression. However, union by size additionally maintains
    the number of nodes in each component, which can be used to efficiently
    answer component-size related queries.
*/
class DisjointSet {
    private:
        int size;
        std::vector<int> sizes;
        std::vector<int> parents;
        
    public:
        /*
            The constructor expectes the number of nodes (v) you will be using in you graph.
            In case you are using 1-based numbering provide size+1 to adjust node number v.
        */
        DisjointSet(int v) {
            this->size = v;
            this->sizes.assign(v, 1);
            this->parents.assign(v, 0);

            // initially every node is the parent to itself
            for (int i=0; i<v; i++)
                this->parents[i] = i;
        }

        /*
            count_components() method figures out how many components are actually there!
            How do we calculate that! Simply the number number nodes who are parents to themselves.
        */
        int count_components() {
            int comps = 0;
            for (int node=0; node<this->size; node++) {
                if (node == this->parents[node])
                    comps++;
            }

            return comps;
        }

        /*
            Method find_parent() helps you to find the ultimate parent of any given node in the graph at a point.
            If node index is negative or beyond maximum node number, it throws OUT_OF_RANGE error.
        */
        int find_parent(int node) {
            if (node < 0 or node >= this->size)
                throw std::out_of_range("index out of range");

            // the node is parent to itself, that means we have reached the ultimate parent
            if (node == this->parents[node])
                return node;

            // simple path compression while fetching the ultimate parent
            return this->parents[node] = find_parent(this->parents[node]);
        }

        /*
            Method is_connected() checks whether two given nodes fall under a common component or not.
            If either of the node's index is negative or beyond maximum node number, it throws OUT_OF_RANGE error.
        */
        bool is_connected(int node1, int node2) {
            if (node1 < 0 or node2 < 0 or node1 >= this->size or node2 >= this->size)
                throw std::out_of_range("node index out of range");

            if (node1 == node2)
                return true;
                
            // If they share the same ultimate parent, they surely come under the same component
            return find_parent(node1) == find_parent(node2);
        }

        /*
            Method make_union() merges two components having these two nodes if not already under a same component.
            If either of the node's index is negative or beyond maximum node number, it throws OUT_OF_RANGE error.
        */
        void make_union(int node1, int node2) {
            if (node1 < 0 or node2 < 0 or node1 >= this->size or node2 >= this->size)
                throw std::out_of_range("node index out of range");

            int parent1 = find_parent(node1);
            int parent2 = find_parent(node2);

            // if parents are same that means they are already under the same component
            if (parent1 == parent2)
                return;

            /*
                But in case the ultimate parents are not same,
                We are willing to connect the smaller component to the larger component.
                The intuition being that we want our tree to have minimum length after merge.
            */
            if (this->sizes[parent1] >= this->sizes[parent2]) {
                // task 1> make parent1 as the ultimate parent of parent2 as well
                this->parents[parent2] = parent1;

                // task 2> increase the size of parent1
                this->sizes[parent1] += this->sizes[parent2];
            }

            else {
                // task 1> make parent2 as the ultimate parent of parent1 as well
                this->parents[parent1] = parent2;

                // task 2> increase the size of parent2
                this->sizes[parent2] += this->sizes[parent1];
            }
        }
};