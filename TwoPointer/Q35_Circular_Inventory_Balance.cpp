/*
    Given an array of positive integers representing item count in a particular inventory.
    The inventory is by nature circular and you can move items from one place to another place.
    You want to arrange the items such that every portion contains same number of items (assume items are always distributable)
    But, the direction in which an item is moved, the direction (left or right) must remain same for other movements as well.
    Every movement has a cost!

    For example, your inventory looks like this : [3 3 6 6 6 6]
    if you want to distribute equally, you need to make it [5 5 5 5 5 5]

    moving from right!

    index 5: we move 1 item to index 0 from index 5: cost = 1 (distance actually)
    index 4: we move 1 item to index 0 again from index 4: cost = 2 (index 0 fulfilled)
    index 3: we move 1 item to index 1 from index 3: cost = 4
    index 2: we move 1 item to index 1 from index 2: cost = 5 (index 1 fulfilled)

    total cost = (1 + 2 + 4 + 5) = 12

    moving from left!

    index 2: we move 1 item to index 1 from index 2: cost 1
    index 3: we move 1 item to index 1 again, from index 3 : cost 2 (index 1 fulfilled)
    index 4: we move 1 item to index 0 from index 4: cost 3
    index 5: we move one item to index 0, from index 5: cost 5 (index 0 fulfilled)

    total cost (1 + 2 + 4 + 5) = 12

    minimum cost = min(12, 12) = 12

    We need to find the minimum cost for this operation (assume distribution is always possible)

                2 <= N <= 10^5
                1 <= A[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>

long long solve_left(const std::vector<long long>& diff) {
    // how many original slots  do we have?
    const int size = diff.size();

    // since slots are circular, we need to append this diffeerence array to itself only
    std::vector<long long> arr = diff;
    for (long long ele : diff)
        arr.emplace_back(ele);

    // we'll start from the last-index
    int index = 2*size - 1;
    int skip_count = 0;

    // step 1> skip those slots which are already item deprived
    while (index >= 0 and arr[index] <= 0) {
        skip_count++;
        index--;
    }

    // step 2> get a stck to collect excess items with their original slot
    std::stack<std::pair<int, long long>> db;
    long long cost = 0;

    // step 3> start distribution
    for (; index >= size - skip_count; index--) {
        // case 1: we have excess elements here
        if (arr[index] > 0) {
            db.emplace(index, arr[index]);
            arr[index] = 0;
        }

        // case 2: neither we have excess elements here, nor we have missing elements here
        else if (arr[index] == 0)
            continue;

        // case 3: we need to dump elements here for sure
        else {
            while (arr[index] != 0) {
                // case 1: top fulfills it and fully fulfils it
                if (db.top().second + arr[index] == 0) {
                    arr[index] += db.top().second;
                    cost += (db.top().first - index);
                    db.pop();
                }

                // case 2: top fulfils it but still has excess items left
                else if (db.top().second + arr[index] > 0) {
                    arr[index] = 0;
                    db.top().second += arr[index];
                    cost += (db.top().first - index);
                }

                // case 3: top fulfils it but partially
                else {
                    arr[index] += db.top().second;
                    cost += (db.top().first - index);
                    db.pop();
                }
            }
        }
    }

    return cost;
}

long long solve_right(const std::vector<long long>& diff) {
    // how many original slots do we have?
    const int size = diff.size();

    // since slots are circular, we need to append this difference array to itself only
    std::vector<long long> arr = diff;

    for (long long ele : diff)
        arr.emplace_back(ele);

    // now we have got the doubled array
    int index = 0;
    int skip_count = 0;
    
    // step1 > skip 0 or negative differences initially move until we do not get the first excess slot, we will fill them later
    while (index < 2*size and arr[index] <= 0) {
        index++;
        skip_count++;
    }

    // step 2> get a stack to collect excess items with their corresponding indices where they were initially present to calculate the cost
    std::stack<std::pair<int, long long>> db;
    long long cost = 0;

    // step 3> start the distribution
    for (; index < size + skip_count; index++) {
        // case 1: we have excess items here, so we simply pick that
        if (arr[index] > 0) {
            db.emplace(index, arr[index]);
            arr[index] = 0;
        }

        // case 2: we have neither excess items nor deprived
        else if (arr[index] == 0)
            continue;


        // case 3: we have to put items here
        else {
            // until we do not fulfil this
            while (arr[index] != 0) {
                // top fulfils it only and fully
                if (db.top().second + arr[index] == 0) {
                    arr[index] += db.top().second;
                    cost += (index - db.top().first);
                    db.pop();
                }

                // top fulfils it but still has excess items left which we will use later
                else if (db.top().second + arr[index] > 0) {
                    db.top().second += arr[index];
                    arr[index] = 0;
                    cost += (index - db.top().first);
                }

                // top does not have enough items to fulfil, so we drop all here and let its previous fulfil it to the rest
                else {
                    arr[index] += db.top().second;
                    cost += (index - db.top().first);
                    db.pop();
                }
            }
        }
    }

    return cost;
}

long long solve(const std::vector<long long>& items) {
    // see how many slots do we have
    const long long size = items.size();

    // see how many slots do we really have
    long long total_count = 0;
    for (long long slot_count : items)
        total_count += slot_count;

    // since items are surely distributable, we will same number of items at every slot. That number is found this way
    const long long target_count = total_count / size;

    // create the difference array, at each slot how many items do we have less or more
    std::vector<long long> diff;

    for (long long slot_count : items)
        diff.emplace_back(slot_count - target_count);

    long long right_movement_cost = solve_right(diff);
    long long left_movement_cost = solve_left(diff);

    std::cout << "\nMoving items to right direction costs " << right_movement_cost << std::endl;
    std::cout << "\nMoving items to left dierction costs " << left_movement_cost << std::endl;

    return std::min(
        right_movement_cost,
        left_movement_cost
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of slots we have : ";
    std::cin >> size;

    std::vector<long long> items(size);
    std::cout << "\nKeep entering the number of items we have in each slot : ";
    for (size_t i=0; i<size; i++)
        std::cin >> items[i];

    const long long answer = solve(items);
    std::cout << "\nMinimum " << answer << " cost it required \n\n";

    return 0;
}

