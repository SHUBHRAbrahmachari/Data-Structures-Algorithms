/*
    Given an array of integers.
    You can either add (+) or (-) sign in front of the element and transform it accordingly.
    You are tasked to find out the maximum possible subsequence sum such that no two consecutive elements have been assigned same sign to them.

    1 <= N <= 10^5
    -10^5 <= A[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>

#define MIN std::numeric_limits<long long>::min()/2

long long solve(const std::vector<int>& arr) {
    const int size = arr.size();

    if (size == 1)
        return std::max(
            arr[0], -arr[0]
        );

    /*
        We will simply maintain 4 running variables which would work for us:

            1> max_including_neg: maximum possible sum upto any index where the current element is included in the subsequence and the sign of the element is (-)
            2> max_including_pos: maximum possible sum upto any index where the current elelemt is included in the subsequence and the sign of the element is (+)
            3> max_excluding_neg: maximum possible sum upto any index where the current element is excluded in the subsequence and the sign associated with the last element is (-)
            4> max_excluding_pos: maximum possible sum upto any index where the current element is excluded in the subsequence and the sign associated with the last element is (+)
    */

    // initiating the base case for index 0
    long long max_including_neg = -arr[0];  // associate a negative sign with the element
    long long max_including_pos = arr[0];   // associate a positive sign with the element
    long long max_excluding_neg = MIN;      // empty subsequence is not desired so we initiate with MIN
    long long max_excluding_pos = MIN;      // empty subsequence is not desired so we initiate with MIN

    for (int i=1; i<size; i++) {
        long long curr_including_neg = max_including_neg;
        long long curr_including_pos = max_including_pos;
        long long curr_excluding_neg = max_excluding_neg;
        long long curr_excluding_pos = max_excluding_pos;

        /*
            Case 1:> 
                We don't want to include this element (arr[i]) in the current subsequence.
                But we want to know the maximum sum a subsequence upto this index & without considering this index,
                such that the sign of last considered element was (-)

                Basically from last index, with or without considering it, what is the best possible sum with last element being (-) sign associated with it?
        */
        max_excluding_neg = std::max(
            curr_including_neg,
            curr_excluding_neg
        );

        /*
            Case 2:?
                We don't want to include this element (arr[i]) in the current subsequence.
                But we want to know the maximum sum of a subsequence upto this index & without considering this index,
                such that the sign of the last considered element was (+)

                Basically from last index, with or without considering it, what is the best possible sum with last element being (+) sign associated with it?
        */
        max_excluding_pos = std::max(
            curr_including_pos,
            curr_excluding_pos
        );

        /*
            Case 3:>
                We want to include this element (arr[i]) in the current subsequence and that too with (-) sign associated with it.
                Therefore we must know what is the best possible sum upto index (i-1) for a subsequnece that either takes or does not take the previous element,
                and it also ends with a (+) sign.

                Or we can also simply start a new subsequence from here!
        */
        max_including_neg = std::max(
            (long long)0,       // to simply start a new subsequence from here
            std::max(
                curr_excluding_pos,
                curr_including_pos
            )
        ) - arr[i];

        /*
            Case 4:>
                We want to include this element (arr[i]) in the current subsequence and that too with (+) sign assocaited with it.
                Therefore we must know what is the best possible sum upto index (i-1) for a subsequence that either takes or does not take the previous element,
                and it also ends with a (-) sign.

                Or we can again also start a completely new subsequence from here!
        */
        max_including_pos = std::max(
            (long long)0,       // to simply start a new subsequence from here      
            std::max(
                curr_including_neg,
                curr_excluding_neg
            )
        ) + arr[i];
    }

    return std::max(
        std::max(
            max_including_neg, max_including_pos
        ),

        std::max(
            max_excluding_neg, max_excluding_pos
        )
    );
}

int main() {
    int size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "\nKeep entering the elements of the array : ";
    for (int i=0; i<size; i++)
        std::cin >> arr[i];

    long long answer = solve(arr);
    std::cout << "\nThe maximum answer would be : " << answer << "\n\n";

    return 0;
}