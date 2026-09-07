/*
    You're visiting a farm that has a single row of fruit trees arranged from left to right.
    Represented by an integer array fruits, where fruits[i] is the type of fruit i-th tree produces.

    You have two baskets, each basket can hold a single type of fruit.
    There is no limit on the amount of fruit each basket can hold. You can start at any tree, but once you start, you must pick exactly one fruit from every tree including where you start.
    Picking stops when you reach a tree that cannot be fit in either of your baskets.

    Return the maximum number of fruits you can collect.

    1 <= fruits.length <= 10^5
    0 <= fruits[i] <= fruits.length

    Examples:
        Input: fruits = [1, 2, 1] -> Output: 3 (Pick from all 3 trees: [1, 2, 1])
        Input: fruits = [0, 1, 2, 2] -> Output: 3 (Pick from trees [1, 2, 2])
        Input: fruits = [1, 2, 3, 2, 2] -> Output: 4 (Pick from trees [2, 3, 2, 2])
*/
/*
    This is simply longest subarray length with atmost 2 unique elements problem in disguise!
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// O(N)
int find_max_fruits(const std::vector<int>& fruits) {
    const int size = fruits.size();

    // to keep track of last appearance index of both of the fruits
    std::unordered_map<int, int> last_appearance_indices;

    int maximum_fruits = 0;

    int left = 0;
    int right = 0;

    while (right < size) {
        const int fruit = fruits[right];

        auto itr = last_appearance_indices.find(fruit);

        // this fruit already exists in either of the buckets
        if (itr != last_appearance_indices.end()) {
            // update its last appearance
            itr->second = right;
        }

        // this fruit does not exist in either of the buckets, i.e. we got a new type of fruit
        else {
            // we can easily collect this fruit
            if (last_appearance_indices.size() < 2) {
                // add this fruit to the either of the buckets which would be free
                last_appearance_indices.emplace(fruit, right);
            }

            else {
                // see which type of fruit's last appearnce has the smallest index, remove that one
                int last_appearance_index = size;
                std::unordered_map<int, int>::iterator fruit_itr;

                // looks like a loop but is actually O(1)
                for (auto itr=last_appearance_indices.begin(); itr != last_appearance_indices.end(); std::advance(itr, 1)) {
                    if (itr->second < last_appearance_index) {
                        last_appearance_index = itr->second;
                        fruit_itr = itr;
                    }
                }

                // pull left beyond that index
                left = last_appearance_index + 1;

                // delete that type of fruit
                last_appearance_indices.erase(fruit_itr);

                // add the new type of fruit to the freed bucket
                last_appearance_indices.emplace(fruit, right);
            }
        }

        // see if we've got more number of fruits
        const int current_fruits = right - left + 1;

        maximum_fruits = std::max(
            maximum_fruits,
            current_fruits
        );

        right++;
    }

    return maximum_fruits;
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> fruits(size, 0);
    std::cout << "\nKeep entering the fruits : ";
    for (int i=0; i<size; i++)
        std::cin >> fruits[i];

    const int answer = find_max_fruits(fruits);
    std::cout << "\nMaximum " << answer << " fruit(s) can be collected" << std::endl << std::endl;

    return 0;
}