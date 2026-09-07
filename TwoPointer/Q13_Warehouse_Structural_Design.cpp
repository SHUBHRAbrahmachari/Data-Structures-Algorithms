/*
    An array of heights containing integers represents the height profiles of rectangular
    barriers of width 1 placed in a storage facility. Calculate the total volume of water trapped in between these bars after a rainfall.

    1 <= N <= 10^5
    0 <= heights[i] <= 10^5
*/

/*
    As long as bar heights ecrease, no water can be trapped right?
    thisnk of it like a stair-case, we re trying to fetch just greater height bar,
    once we got that, we see how many other bars can it satisfy
*/

#include <iostream>
#include <vector>
#include <stack>


int find_trapped_rainwater_volume(const std::vector<int>& heights) {
    const size_t size = heights.size();
    
    // get a stack
    std::stack<int> st;

    int total_volume = 0;

    for (size_t index=0; index<size; index++) {
        while (not st.empty() and heights[index] > heights[st.top()]) {
            const int mid = st.top();
            st.pop();

            // left bar does not exist
            if (st.empty())
                break;

            // the left bar, if height is same calculated value would automatically get neutralized
            // do not just simply remove, since it is to be evaluated as mid index as well right?
            const int left = st.top();

            const int height = std::min(heights[left], heights[index]) - heights[mid];
            const int width = index - left - 1;

            total_volume += height*width;
        }

        // push this again to look for next possiibilities
        st.push(index);
    }

    return total_volume;   
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of bars : ";
    std::cin >> size;

    std::vector<int> heights(size);
    std::cout << "\nKeep entering the heights : ";
    for (size_t i=0; i<size; i++)
        std::cin >> heights[i];


    const int answer = find_trapped_rainwater_volume(heights);
    std::cout << "\nThe trapped volume is " << answer << " units(s) \n\n";

    return 0;
}