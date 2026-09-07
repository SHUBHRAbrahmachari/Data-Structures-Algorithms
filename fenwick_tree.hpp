#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class FenwickTree {
    protected:
        size_t size;
        std::vector<T> tree;

    public:

        FenwickTree(const size_t size) {
            this->size = size;
            this->tree.assign(this->size+1, 0);
        }

        FenwickTree(const std::vector<T>& array) {
            this->size = array.size();
            this->tree.assign(this->size+1, 0);
        }

        virtual void update(const size_t index, const T delta) = 0;
        virtual T query(const size_t index) = 0;
};

template<typename T>
class FenwickTreeSum : public FenwickTree<T> {
    public:

        FenwickTreeSum(const size_t size) : FenwickTree<T>(size) {}

        FenwickTreeSum(const std::vector<T>& array) : FenwickTree<T>(array) {
            for (size_t i=0; i<this->size; i++)
                update(i, array[i]);
        }

        void update(const size_t index, const T delta) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            size_t eff_index = index+1;
            while (eff_index <= this->size) {
                this->tree[eff_index] += delta;
                eff_index += (eff_index & -eff_index);
            }
        }

        T query(const size_t index) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            T sum = 0;
            size_t eff_index = index+1;
            while (eff_index > 0) {
                sum += this->tree[eff_index];
                eff_index -= (eff_index & -eff_index);
            }

            return sum;
        }
};
