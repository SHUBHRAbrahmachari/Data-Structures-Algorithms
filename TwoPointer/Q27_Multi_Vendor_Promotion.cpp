/*
    Given an array of nums of n integers and another integer target.
    Return all unique quadruplets (a, b, c, d) such such that a+b+c+d = target and also
    their indices are unique
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>


class Quadruplet {
    private:
        int a;
        int b;
        int c;
        int d;

    public:
        Quadruplet(int a, int b, int c, int d) {
            this->a = a;
            this->b = b;
            this->c = c;
            this->d = d;
        }

        int get_a() const {
            return this->a;
        }

        int get_b() const {
            return this->b;
        }

        int get_c() const {
            return this->c;
        }

        int get_d() const {
            return this->d;
        }

        bool operator==(const Quadruplet& other) const {
            return this->a == other.get_a() and
                   this->b == other.get_b() and
                   this->c == other.get_c() and
                   this->d == other.get_d();
        }

        std::vector<int> to_vector() const {
            std::vector<int> quadruplet;
            quadruplet.emplace_back(this->a);
            quadruplet.emplace_back(this->b);
            quadruplet.emplace_back(this->c);
            quadruplet.emplace_back(this->d);

            return quadruplet;
        }
};

namespace std {
    template<>
    class hash<Quadruplet> {
        public:
            size_t operator()(const Quadruplet& quadruplet) const {
                return std::hash<int>()(quadruplet.get_a())*31*31*31 ^
                       std::hash<int>()(quadruplet.get_b())*31*31 ^
                       std::hash<int>()(quadruplet.get_c())*31 ^
                       std::hash<int>()(quadruplet.get_d());
            }
    };
}

void print_quadruplet(const std::vector<int>& quadruplet) {
    std::cout << std::endl;
    for (int ele : quadruplet)
        std::cout << ele << " ";
    return;
}

std::vector<std::vector<int>> solve(std::vector<int>& array, const int target) {
    const int size = array.size();

    if (size < 4)
        return std::vector<std::vector<int>>();

    std::sort(array.begin(), array.end());

    std::unordered_set<Quadruplet> unique_quadruplets;
    std::vector<std::vector<int>> quadruplets;

    for (int a=0; a<size-3; a++) {
        int new_target = target - array[a];

        for (int b=a+1; b<size-2; b++) {
            int final_target = new_target - array[b];

            int c = b+1;
            int d = size-1;

            while (c < d) {
                // CASE 1: SUM BECOMES GREATER
                if (array[c] + array[d] > final_target)
                    d--;

                // CASE 2: SUM BECOMES SMALLER
                else if (array[c] + array[d] < final_target)
                    c++;

                // CASE 3: SUM BECOMES EQUAL
                else {
                    unique_quadruplets.emplace(array[a], array[b], array[c], array[d]);

                    if (array[c] == array[d])
                        break;

                    else {
                        int val = array[c];
                        while (array[c] == val)
                            c++;

                        val = array[d];
                        while (array[d] == val)
                            d--;
                    }
                }
            }
        }
    }

    for (auto ele : unique_quadruplets)
        quadruplets.emplace_back(ele.to_vector());

    return quadruplets;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> array[i];

    int target;
    std::cout << "\nEnter the target : ";
    std::cin >> target;

    std::vector<std::vector<int>> quadruplets = solve(array, target);
    for (auto ele : quadruplets)
        print_quadruplet(ele);

    return 0;
}