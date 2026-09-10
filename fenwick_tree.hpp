#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

template <typename T>
class FenwickTreeSum {
    private:
        size_t size;
        std::vector<T> tree;
        std::vector<T> arr;

    public:
        FenwickTreeSum(const size_t size) {
            this->size = size;
            this->arr.assign(this->size, 0);
            this->tree.assign(this->size+1, 0);
        }

        FenwickTreeSum(const std::vector<T>& arr) {
            this->size = arr.size();
            this->arr.assign(this->size, 0);
            this->tree.assign(this->size+1, 0);

            for (size_t i=0; i<this->size; i++)
                this->update(i, arr[i]);
        }

        void update(const size_t index, const T new_value) {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            const T diff = new_value - this->arr[index];
            this->arr[index] = new_value;
            size_t eff_index = index+1;

            while (eff_index <= this->size) {
                this->tree[eff_index] += diff;
                eff_index += (eff_index & -eff_index);
            }
        }

        // sum of elements upto index `index` from index 0
        T query(const size_t index) {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            size_t eff_index = index+1;
            T sum = 0;

            while (eff_index > 0) {
                sum += this->tree[eff_index];
                eff_index -= (eff_index & -eff_index);
            }

            return sum;
        }
};
