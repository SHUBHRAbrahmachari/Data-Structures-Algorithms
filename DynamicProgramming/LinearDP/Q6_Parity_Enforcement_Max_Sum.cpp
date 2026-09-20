/*
    Given an array of positive integers.
    You can alter any element in this array by 0 such that ->

    NO TWO ADJACENT ELEMENTS (non-zero) HAS THE SAME PARITY.
    i.e. NO TWO ADJECENT ELEMENTS SHOULD BE SIMULTANEOUSLY ODD/EVEN
    One of them has to be odd, other one has to be even

    Maximize the total sum of the array after all those operations

    1 <= N <= 10^5
    1 <= A[i] <= 10^9
*/

#include <iostream>
#include <vector>

long long solve(const std::vector<int>& arr) {
    const size_t size = arr.size();
    /*
        We'll have two running variables
    */

    if (size == 1)
        return arr[0];

    long long max_sum_without_alteration = arr[0];
    long long max_sum_with_alteration = 0;

    for (size_t i=1; i<size; i++) {
        long long curr_sum_without_alteration = max_sum_without_alteration;
        long long curr_sum_with_alteration = max_sum_with_alteration;

        int prev_parity = arr[i-1] % 2;
        int curr_parity = arr[i] % 2;
        
        /*
            since parites does not match, we can consider both
                1> best sum upto index i-1 where element at index i-1 was not altered
                2> best sum upto index i-1 where element at index i-1 was altered
        */
        if (curr_parity != prev_parity) {
            /*
                Since parities does not match.
                Whether you should consider this element or not does not depend on whether last element was taken or not.
                You are free to choose any combination
            */
            max_sum_without_alteration = std::max(
                curr_sum_with_alteration,
                curr_sum_without_alteration
            ) + arr[i]; // because we're considering to add this element

            // since i am not considering this element, so i need to consider the maximum of previous
            max_sum_with_alteration = std::max(
                curr_sum_with_alteration,
                curr_sum_without_alteration
            ); // because we're considering not to add this element
        }

        // since parities match, we need to alter either this element, or the previous element
        else {
            /*
                case 1:
                    If i'm willing to toggle this element.
                    It doesn't matter whether previous element was toggled or not.
                    So i simply take maximum of them
            */
            max_sum_with_alteration = std::max(
                curr_sum_without_alteration,
                curr_sum_with_alteration
            );

            /*
                case 2:
                    If i am not willing to toggle this element.
                    I must ensure that the previous element was toggled.
                    So i consider only pevious element toggled state
            */
            max_sum_without_alteration = curr_sum_with_alteration + arr[i];
        }
    }

    return std::max(
        max_sum_without_alteration,
        max_sum_with_alteration
    );
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nEnter the elements of the array : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    const long long answer = solve(arr);
    std::cout << "\nThe maximum answer would be : " << answer << "\n\n";

    return 0;
}