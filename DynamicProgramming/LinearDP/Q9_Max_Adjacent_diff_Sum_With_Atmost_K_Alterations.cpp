/*
    Given an array of integers.
    We are also given another integer K.

    We can set any element to 0 atmost K times. Any element of this array.
    We need to find maximum possible sum of absolute differences of the adjacent elements of this array.

    1 <= K <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

/*
    We wouldn't go with our typical memoizzation.
    The code will become extremely messy.

    Let's move with tabulation.
*/

long long solve(const std::vector<int>& arr, const int k) {
    const size_t size = arr.size();

    if (size == 1)
        return 0;

    /*
        Let us create our DP memory: DEFINITION IS EXTREMELY IMPORTANT TO UNDERSTAND

        memory[i][t][s]: 
            Maximum possible adjacent difference sum upto index i
            With EXACTLY total t alterations used up to index i,
            With state of A[i] being s (either altered or not) 
    */
    std::vector<std::vector<std::vector<long long>>> memory(
        size,
        std::vector<std::vector<long long>>(
            k+1,
            std::vector<long long>(2)
        )
    );

    /*
        Now we come to the transitions:

        scenario 1> We do not spend flip at index i

            if A[i-1] was not toggled, sum = |A[i]-A[i-1]|
            if A[i-1] was toggled, sum = |A[i]-0|
            
            but how do you calculate it? very easy!

            memory[i][t][0] = max(
                memory[i-1][t][0] + |A[i]-A[i-1]|,
                memory[i-1][t][1] + |A[i]|
            )

            why t? not t-1? because we have not spent any toggle here na!

        scenario 2> We spend a flip at index i

            if A[i-1] was toggles, sum = 0
            if A[i-1] was not toggles, sum = |A[i-1]|

            but how do you calculate the total sum, again very easy!

            memory[i][t][1] = max(
                memory[i-1][t-1][0] + |A[i-1]|,
                memory[i-1][t-1][1]
            )

            why t-1? not t? because we have already spending a toggle in this index na? so we must look for t-1 earlier toggles
    */
    
    /*
        Good to go! Now let us start the actual code
    */

    for (int i=1; i<size; i++) {
        for (int t=k; t>=0; t--) {
            // for every element we will go for all toggle levels

            if (t > 0) {
                // scenario 1> we decide not to flip this element and let it be as it is
                memory[i][t][0] = std::max(
                    memory[i-1][t][0] + std::abs(arr[i]-arr[i-1]),
                    memory[i-1][t][1] + std::abs(arr[i])
                );

                // scenario 2? we decide to flip this element
                memory[i][t][1] = std::max(
                    memory[i-1][t-1][0] + std::abs(arr[i-1]),
                    memory[i-1][t-1][1]
                );
            }

            // for t == 0 we can't access t-1 right? we need to handle it separately
            else
                memory[i][0][0] = memory[i-1][0][0] + std::abs(arr[i]-arr[i-1]);
        }
    }

    // since we were asked to generate the answer for ATMOST K transactions, we need to find the maximum for every level
    long long answer = MIN;

    for (size_t t=0; t<=k; t++) {
        answer = std::max(
            answer,
            std::max(
                memory[size-1][t][0],
                memory[size-1][t][1]
            )
        );
    }

    return answer;
}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements one by one : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    int k;
    std::cout << "\nEnter the maximum possible flips : ";
    std::cin >> k;

    const long long answer = solve(arr, k);
    std::cout << "\nThe maximum possible sum of adjacent elements will be : " << answer << "\n\n";

    return 0;
}