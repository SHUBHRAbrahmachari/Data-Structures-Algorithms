#include <vector>
#include <stdexcept>

class DSU {
    private:
        int v;
        std::vector<int> arr;

    public:
        DSU(int v) {
            this->v = v;
            this->arr.assign(v, 0);

            for (int i=0; i<v; i++)
                this->arr[i] = i;
        }

        // to find the parent of a given node in the DISJOINT SET UNION
        int find_parent(int node) {
            if (node < 0 or node >= this->v)
                throw std::out_of_range("node index out of range");
            
            if (this->arr[node] == node)
                return node;

            return this->arr[node] = find_parent(this->arr[node]);
        }

        // to find if these two nodes come under a UNION or not
        int is_union(int node1, int node2) {
            if (node1 < 0 or node1 >= this->v or node2 < 0 or node2 >= this->v)
                throw std::out_of_range("node index outof range");

            return find_parent(node1) == find_parent(node2);
        }

        // to bring two nodes under a union
        void make_union(int node1, int node2) {
            if (node1 < 0 or node1 >= this->v or node2 < 0 or node2 >= this->v)
                throw std::out_of_range("node index outof range");

            int parent1 = find_parent(node1);
            int parent2 = find_parent(node2);

            if (parent1 <= parent2)
                this->arr[parent2] = parent1;
            else
                this->arr[parent1] = parent2;
            
            return;
        }
};