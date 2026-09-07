#include <vector>
#include <limits>
#include <stdexcept>

template<typename T>
class SegmentTree {
    protected:
        size_t size;
        std::vector<T> tree;

    public:

        SegmentTree(const size_t size) {
            this->size = size;
            this->tree.assign(this->size*4, 0);
        }

        SegmentTree(const std::vector<T>& array) {
            this->size = array.size();
            this->tree.assign(this->size*4, 0);
        }

        virtual void update(const size_t index, const T value) = 0;
        virtual void delta(const size_t index, const T delta_value) = 0;
        virtual T query(const size_t left_index, const size_t right_index) = 0;
};

template<typename T>
class SegmentTreeSum : public SegmentTree<T> {
    private:

        void build_(const std::vector<T>& array, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = array[left];
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            this->build_(array, left, mid, left_child);
            this->build_(array, mid+1, right, right_child);

            this->tree[v] = this->tree[left_child] + this->tree[right_child];
            return;
        }

        void update_(const size_t index, const T new_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = new_value;
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            if (index <= mid)
                this->update_(index, new_value, left, mid, left_child);

            else
                this->update_(index, new_value, mid+1, right, right_child);

            this->tree[v] = this->tree[left_child] + this->tree[right_child];
            return;
        }

        void delta_(const size_t index, const T delta_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] += delta_value;
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            if (index <= mid)
                this->delta_(index, delta_value, left, mid, left_child);

            else
                this->delta_(index, delta_value, mid+1, right, right_child);

            this->tree[v] = this->tree[left_child] + this->tree[right_child];
            return;
        }

        T query_(const size_t lt, const size_t rt, const size_t left, const size_t right, const size_t v=1) {
            // case 1> complete overlap
            if (left >= lt and right <= rt)
                return this->tree[v];

            // case 2> complete miss
            if (left > rt or right < lt)
                return 0;

            const size_t mid = (left+right)/2;
            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            const T left_result = query_(lt, rt, left, mid, left_child);
            const T right_result = query_(lt, rt, mid+1, right, right_child);

            return left_result + right_result;
        }

    public:

        SegmentTreeSum(const size_t size) : SegmentTree<T>(size) {}

        SegmentTreeSum(const std::vector<T>& array) : SegmentTree<T>(array) {
            this->build_(array, 0, this->size-1);
        }

        void update(const size_t index, const T new_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->update_(index, new_value, 0, this->size-1);
        }

        void delta(const size_t index, const T delta_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->delta_(index, delta_value, 0, this->size-1);
        }

        T query(const size_t left_index, const size_t right_index) {
            if (left_index >= this->size or right_index >= this->size)
                throw std::out_of_range("index out of range");

            return this->query_(left_index, right_index, 0, this->size-1);
        }
};

template<typename T>
class SegmentTreeMax : public SegmentTree<T> {
    private:

        void build_(const std::vector<T>& array, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = array[left];
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            this->build_(array, left, mid, left_child);
            this->build_(array, mid+1, right, right_child);

            this->tree[v] = std::max(
                this->tree[left_child],
                this->tree[right_child]
            );

            return;
        }

        void update_(const size_t index, const T new_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = new_value;
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            if (index <= mid)
                this->update_(index, new_value, left, mid, left_child);

            else
                this->update_(index, new_value, mid+1, right, right_child);

            this->tree[v] = std::max(
                this->tree[left_child],
                this->tree[right_child]
            );

            return;
        }

        void delta_(const size_t index, const T delta_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] += delta_value;
                return;
            }

            const size_t mid = (left+right)/2;

            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            if (index <= mid)
                this->delta_(index, delta_value, left, mid, left_child);

            else
                this->delta_(index, delta_value, mid+1, right, right_child);

            this->tree[v] = std::max(
                this->tree[left_child],
                this->tree[right_child]
            );

            return;
        }

        T query_(const size_t lt, const size_t rt, const size_t left, const size_t right, const size_t v=1) {
            // case 1> complete overlap
            if (left >= lt and right <= rt)
                return this->tree[v];

            // case 2> complete miss
            if (left > rt or right < lt)
                return std::numeric_limits<T>::min();

            const size_t mid = (left+right)/2;
            const size_t left_child = 2*v;
            const size_t right_child = left_child + 1;

            const T left_result = query_(lt, rt, left, mid, left_child);
            const T right_result = query_(lt, rt, mid+1, right, right_child);

            return std::max(
                left_result,
                right_result
            );
        }

    public:

        SegmentTreeMax(const size_t size) : SegmentTree<T>(size) {}

        SegmentTreeMax(const std::vector<T>& array) : SegmentTree<T>(array) {
            this->build_(array, 0, this->size-1);
        }

        void update(const size_t index, const T new_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->update_(index, new_value, 0, this->size-1);
        }

        void delta(const size_t index, const T delta_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->delta_(index, delta_value, 0, this->size-1);
        }

        T query(const size_t left_index, const size_t right_index) {
            if (left_index >= this->size or right_index >= this->size)
                throw std::out_of_range("index out of range");

            return this->query_(left_index, right_index, 0, this->size-1);
        }
};

template<typename T>
class SegmentTreeMin : public SegmentTree<T> {
    private:

        void build_(const std::vector<T>& array, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = array[left];
                return;
            }

            const size_t mid = (left+right)/2;
            const size_t left_child = 2*v;
            const size_t right_child = left_child+1;

            this->build_(array, left, mid, left_child);
            this->build_(array, mid+1, right, right_child);

            this->tree[v] = std::min(
                this->tree[left_child],
                this->tree[right_child]
            );
        }

        void update_(const size_t index, const T new_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] = new_value;
                return;
            }

            const size_t mid = (left+right)/2;
            const size_t left_child = 2*v;
            const size_t right_child = left_child+1;

            if (index <= mid)
                this->update_(index, new_value, left, mid, left_child);

            else
                this->update_(index, new_value, mid+1, right, right_child);

            this->tree[v] = std::min(
                this->tree[left_child],
                this->tree[right_child]
            );
        }

        void delta_(const size_t index, const T delta_value, const size_t left, const size_t right, const size_t v=1) {
            if (left == right) {
                this->tree[v] += delta_value;
                return;
            }

            const size_t mid = (left+right)/2;
            const size_t left_child = 2*v;
            const size_t right_child = left_child+1;

            if (index <= mid)
                this->delta_(index, delta_value, left, mid, left_child);

            else
                this->delta_(index, delta_value, mid+1, right, right_child);

            this->tree[v] = std::min(
                this->tree[left_child],
                this->tree[right_child]
            );
        }

        T query_(const size_t left, const size_t right, const size_t lt, const size_t rt, const size_t v=1) {
            if (lt >= left and rt <= right)
                return this->tree[v];

            else if (lt > right or rt < left)
                return std::numeric_limits<T>::max();

            else {
                const size_t mid = (lt+rt)/2;

                const size_t left_child = 2*v;
                const size_t right_child = left_child+1;

                const T left_result = this->query_(left, right, lt, mid, left_child);
                const T right_result = this->query_(left, right, mid+1, rt, right_child);

                return std::min(
                    left_result,
                    right_result
                );
            }
        }

    public:

        SegmentTreeMin(const size_t size) : SegmentTree<T>(size) {}

        SegmentTreeMin(const std::vector<T>& array) : SegmentTree<T>(array) {
            this->build_(array, 0, this->size-1);
        }

        void update(const size_t index, const T new_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->update_(index, new_value, 0, this->size-1);
        }

        void delta(const size_t index, const T delta_value) override {
            if (index >= this->size)
                throw std::out_of_range("index out of range");

            this->delta_(index, delta_value, 0, this->size-1);
        }

        T query(const size_t left, const size_t right) override {
            if (right >= this->size or left > right)
                throw std::out_of_range("index out of range");

            return this->query_(left, right, 0, this->size-1);
        }
};