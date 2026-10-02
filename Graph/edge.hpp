class Edge {
    private:
        int destination;
        int weight;

    public:
        Edge(const int destination, const int weight=0) {
            this->destination = destination;
            this->weight = weight;
        }

        int get_destination() const {
            return this->destination;
        }

        int get_weight() const {
            return this->weight;
        }

        void set_destination(const int destination) {
            this->destination = destination;
        }

        void set_weight(const int weight) {
            this->weight = weight;
        }
};