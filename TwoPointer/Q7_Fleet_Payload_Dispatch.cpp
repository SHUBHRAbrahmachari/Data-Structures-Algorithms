/*
    An amazon logistics hub uses heavy-lift drones to dispatch packages.
    You're given an array of weights where weight[i] shows the weight of i-th parcel.

    You're also given an integer limit representing the maximum payload capacity of a drone.
    Each drone can carry any 2 packages simultaneously. Return minimum number of drone flights
    required to deliver all the packages.

        1 <= N <= 10^5
        1 <= weights[i] <= limit <= 10^9
*/

/*
    This is a typical two-pointer approach
*/

#include <iostream>
#include <vector>
#include <algorithm>

long long find_minimum_flights(std::vector<long long>& weights, const long long limit) {
    const size_t size = weights.size();

    // greedy approach ould be to sort the weights first in ascending order
    std::sort(weights.begin(), weights.end());

    long long flight_count = 0;
    size_t start = 0;
    size_t end = size-1;

    while (start <= end) {
        flight_count++;

        // single element left
        if (start == end)
            break;

        else {
            if (weights[start] + weights[end] <= limit)
                start++;

            end--;
        }
    }

    return flight_count;
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of total parcels to be delivered : ";
    std::cin >> size;

    std::vector<long long> weights(size);
    std::cout << "\nKeep entering the weights of the packages : ";
    for (size_t i=0; i<size; i++)
        std::cin >> weights[i];

    long long limit;
    std::cout << "\nEnter the drone's weight carrying limit : ";
    std::cin >> limit;

    const long long answer = find_minimum_flights(weights, limit);
    std::cout << "\nMinimum " << answer << " flights are required!" << std::endl << std::endl;

    return 0;
}