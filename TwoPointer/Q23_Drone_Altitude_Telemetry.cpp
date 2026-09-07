/*
    Given an integer array `arr` of telemetry readings.
    Return the length of the longest mountain subarray of length atleast 3 such that

    A[0] < A[1] < A[2] < ... < A[i]

                    AND

    A[i] > A[i+1] > A[i+1] > .....

    3 <= N <= 10^5
    0 <= arr[i] <= 10^9

    Example: [2 1 4 7 3 2 5]
        output : 5 [1 4 7 3 2]

*/

#include <iostream>
#include <vector>

int solve(const std::vector<int>& elevations) {
    const int size = elevations.size();

    int left = 0;
    int right = 0;

    // trajectory = true : we are looking to ascend right now
    // trajectory = false : we are looking to descend right now, we only update our length when we're descending
    bool trajectory = true;
    bool have_left_element = false;

    int max_length = 0;

    while (true) {

        // keep updating our max_length while we're descending
        if (have_left_element and not trajectory)
            max_length = std::max(
                max_length,
                right - left + 1
            );

        // we're already standing at last observable index
        if (right == size-1)
            break;

        // we don't update our max_length but see how long we can ascend
        if (trajectory) {
            // case 1: yes we can definitely rise further
            if (elevations[right+1] > elevations[right]) {
                right++;
                have_left_element = true;
            }

            // case 2: ok we see that next elevation being the same, so upto this stretch it can never be a mountain, we need to start again
            else if (elevations[right] == elevations[right+1]) {
                right += 1;
                left = right;
                have_left_element = false;
            }

            // finally change in trajectory
            else {
                right += 1;

                // set trajectory as false => descending now
                trajectory = false;
            }
        }

        // we're descending now
        else {
            // case 1: we can still descend further
            if (elevations[right+1] < elevations[right])
                right++;

            // case 2: we see next elevation is same, so again we need to start
            else if (elevations[right+1] == elevations[right]) {
                right += 1;
                left = right;
                trajectory = true;
                have_left_element = false;
            }

            // case 3: we see next element is greter, so most probably from this point new hill starts
            else {
                left = right;
                trajectory = true;
                have_left_element = false;
            }
        }
    }

    return max_length;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> elevations(size);
    std::cout << "\nEnter the elevations : ";
    for (size_t i=0; i<size; i++)
        std::cin >> elevations[i];

    const int max_mountain_length = solve(elevations);
    std::cout << "\nThe maximum mountain length would be : " << max_mountain_length << std::endl << std::endl;

    return 0;
}