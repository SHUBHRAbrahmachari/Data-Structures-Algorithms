/*
    Given an integer array `vouchers` and an integer `target`.
    Return all unique triplets such that their sum is equal to target

    1 <= N <= 3000
    -10^5 <= vouchers[i] <= 10^5
    -10^9 <= target <= 10^9

    Example:

            [-1 0 1 2 -1 -4] target 0

            [-1 -1 2]
            [-1 0 1]
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>

class Triplet {
    private:
        int x;
        int y;
        int z;

    public:
        Triplet(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        int get_x() const {
            return this->x;
        }

        int get_y() const {
            return this->y;
        }

        int get_z() const {
            return this->z;
        }

        bool operator==(const Triplet& other) const {
            return this->x == other.get_x() and this->y == other.get_y() and this->z == other.get_z();
        }

        std::vector<int> to_vector() const {
            std::vector<int> NEW;
            NEW.emplace_back(this->x);
            NEW.emplace_back(this->y);
            NEW.emplace_back(this->z);

            return NEW;
        }
};

namespace std {
    template<>
    class hash<Triplet> {
        public:
            size_t operator()(const Triplet& triplet) const {
                return std::hash<int>()(triplet.get_x())*31*31 ^ std::hash<int>()(triplet.get_y())*31 ^ std::hash<int>()(triplet.get_z());
            }
    };
}

std::vector<std::vector<int>> find_unique_triplets(
    std::vector<int>& array,
    const int target
) {
    const size_t size = array.size();

    if (size < 3)
        return std::vector<std::vector<int>>();

    std::unordered_set<Triplet> triplets;
    std::vector<std::vector<int>> answer_triplets;

    // first sort the array
    std::sort(array.begin(), array.end());

    for (size_t i=0; i<size-2; i++) {
        const int new_target = target - array[i];

        size_t left = i+1;
        size_t right = size-1;

        while (left < right) {
            if (array[left] + array[right] > new_target)
                right--;
            
            else if (array[left] + array[right] < new_target)
                left++;

            else {
                triplets.emplace(array[i], array[left], array[right]);

                // no more unique pairs possible for sure
                if (array[left] == array[right]) 
                    break;

                // avoiding same elements for left
                while (array[left+1] == array[left])
                    left++;

                left += 1;

                // avoiding same elements for right too
                while (array[right-1] == array[right])
                    right--;

                right -= 1;
            }
        }
    }

    for (const Triplet triplet : triplets)
        answer_triplets.emplace_back(triplet.to_vector());

    return answer_triplets;
}

void show_triplet(const std::vector<int>& triplet) {
    std::cout << std::endl;
    for (int ele : triplet)
        std::cout << ele << " ";
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "\nKeep entering the values : ";
    for (size_t i=0; i<size; i++)
        std::cin >> array[i];

    int target;
    std::cout << "\nEnter the target : ";
    std::cin >> target;

    const std::vector<std::vector<int>> triplets = find_unique_triplets(array, target);

    if (triplets.empty()) {
        std::cout << "\nNo triplets found!";
        return 0;
    }

    for (auto triplet : triplets)
        show_triplet(triplet);

    return 0;
}