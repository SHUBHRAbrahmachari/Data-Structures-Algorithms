/*
    An array of integers elevations represents the altitiude profile of a drone delivery path.
    find the length of the longest contigous segment of route locations such that
    the absolute difference between any two elevations doesn't exceed limit K

        1 <= N <= 10^5
        1 <= elevations[i] <= 10^9
        0 <= limit <= 10^9
*/

#include <iostream>
#include <vector>
#include <deque>

size_t find_longest_segment_length(const std::vector<long long>& elevations, const long long k) {
    const size_t size = elevations.size();

    // get a deque to track maximum elevation points in a particular segment
    std::deque<size_t> max_elevation_points;

    // similarly get a deque to track minimum elvation points in a particular segment
    std::deque<size_t> min_elevation_points;

    size_t right = 0;
    size_t left = 0;
    size_t max_segment_length = 0;

    while (right < size) {
        // arrange such that maximum elevation point always stays in front
        while (not max_elevation_points.empty() and elevations[right] >= elevations[max_elevation_points.back()])
            max_elevation_points.pop_back();

        // add this elevation point
        max_elevation_points.emplace_back(right);

        // arrange such that the minimum elevation points stays always in front
        while (not min_elevation_points.empty() and elevations[right] <= elevations[min_elevation_points.back()])
            min_elevation_points.pop_back();

        // add this elevation point
        min_elevation_points.emplace_back(right);

        // shrink the window as long as absolute difference condition is breached
        while (elevations[max_elevation_points.front()] - elevations[min_elevation_points.front()] > k) {
            if (max_elevation_points.front() == left)
                max_elevation_points.pop_front();

            if (min_elevation_points.front() == left)
                min_elevation_points.pop_front();

            left++;
        }

        size_t curr_segment_length = right - left + 1;

        max_segment_length = std::max(
            max_segment_length,
            curr_segment_length
        );

        right++;
    }

    return max_segment_length;
}

int main() {
    size_t size;
    std::cout << "\nEnter the number of elevation points you have : ";
    std::cin >> size;

    std::vector<long long> elevations(size);
    std::cout << "\nKeep entering the elevations : ";
    for (int i=0; i<size; i++)
        std::cin >> elevations[i];

    long long k;
    std::cout << "\nEnter the maximum limit : ";
    std::cin >> k;

    const size_t answer = find_longest_segment_length(elevations, k);
    std::cout << "\nThe maximum segment length would be : " << answer << std::endl << std::endl;

    return 0;
}


