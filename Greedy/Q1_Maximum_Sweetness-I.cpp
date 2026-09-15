/**
    Problem idea:

    We are given:
      - s[i] : sweetness of the i-th sweet type
      - t[i] : time needed to prepare that sweet
      - c[d] : the time Adam has on day d

    Adam can prepare each sweet type at most once, and on each day he can choose only one sweet
    whose preparation time does not exceed that day's available time.

    We need to maximize the total sweetness collected over all days.

    Constraints:
      1 <= |s| = |t| <= 10^5
      1 <= |c| <= 10^5
      1 <= s[i] <= 10^5
      1 <= c[i], t[i] <= 10^5

    Greedy observation:
      For a particular day, if a sweet can be made within the available time, then among all
      such valid sweets we should pick the one with maximum sweetness. This is exactly what a
      max-heap helps us do efficiently.

    #O(NlogN + MlogM)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/**
    Each sweet is treated as a pair: (sweetness, time required).
    We store both values together so that we can sort by time and later pick
    the best sweetness among all sweets that are currently feasible.
*/
class Sweet {
    private:
        int sweetness;
        int time;

    public:
        Sweet(const int sweetness, const int time) {
            this->sweetness = sweetness;
            this->time = time;
        }

        int get_sweetness() const {
            return this->sweetness;
        }

        int get_time() const {
            return this->time;
        }
};

/**
    The sweets are sorted by preparation time because we want to consider all sweets that can
    be made within the current day's time limit.
*/
class SortingComparator {
    public:
        bool operator()(const Sweet& s1, const Sweet& s2) const {
            return s1.get_time() < s2.get_time();
        }
};

/**
    For the max-heap, we want the sweet with largest sweetness at the top.
    Since std::priority_queue is a max-heap by default, we represent the ordering by placing
    the larger sweetness as the "less-than" value for comparison.
*/
class HeapComparator {
    public:
        bool operator()(const Sweet& s1, const Sweet& s2) const {
            return s1.get_sweetness() < s2.get_sweetness();
        }
};

/**
    The greedy strategy is:
      1. Sort available day-times in increasing order.
      2. For each day, add every sweet whose preparation time is <= today's available time.
      3. Among all currently feasible sweets, choose the one with maximum sweetness.
      4. Repeat this for all days.

    This works because for each day we only need the best sweet available under that day's budget.
    By always taking the highest sweetness among feasible choices, we maximize the total sweetness.
*/
long long solve(const std::vector<int>& s, const std::vector<int>& t, std::vector<int>& c) {
    const size_t sweet_count = s.size();
    const size_t day_count = c.size();

    /**
        Combine sweetness and time into a single object for each sweet.
        This helps us sort sweets by time and later use the max-heap for sweetness.
    */
    std::vector<Sweet> sweets;
    for (size_t i=0; i<sweet_count; i++)
        sweets.emplace_back(s[i], t[i]);

    /**
        Adam can prepare only one sweet per day.
        So we process days in increasing order of time and greedily decide which sweet is best
        for the current day, using a max-heap to keep track of the maximum sweetness available.
    */
    std::sort(c.begin(), c.end());
    std::sort(sweets.begin(), sweets.end(), SortingComparator());

    long long sweetness = 0;

    /**
        sweet_queue stores all sweets that are currently feasible for the current day.
        The heap is ordered by sweetness so that the top element is the sweetest one.
    */
    std::priority_queue<Sweet, std::vector<Sweet>, HeapComparator> sweet_queue;
    size_t index = 0;
    size_t day = 0;

    while (day < day_count) {
        int time = c[day];

        /**
            Add every sweet that can be prepared within the current day's time limit.
            Once added, it becomes available to be selected for this day.
        */
        while (index < sweet_count and sweets[index].get_time() <= time) {
            sweet_queue.emplace(sweets[index]);
            index++;
        }

        if (not sweet_queue.empty()) {
            sweetness += sweet_queue.top().get_sweetness();

            /**
                Each sweet type can be prepared at most once, so after choosing it,
                it is removed from the available pool.
            */
            sweet_queue.pop();
        }

        day++;
    }

    return sweetness;
}

int main() {
    size_t size;
    std::cout << "\nEnter the total number of sweets : ";
    std::cin >> size;

    std::vector<int> s(size);
    std::vector<int> t(size);

    /**
        Read the sweetness and the time required to prepare each sweet type.
    */
    std::cout << "\nKeep entering the sweetness levels and unit of time required to make it : \n\n";
    for (size_t i=0; i<size; i++)
        std::cin >> s[i] >> t[i];

    size_t m;
    std::cout << "\nEnter the total number of days Adam has to make the sweets : ";
    std::cin >> m;

    std::vector<int> c(m);

    /**
        Read the time available on each day.
    */
    std::cout << "\nKeep entering the unit time he has each day to dedicate : ";
    for (size_t i=0; i<m; i++)
        std::cin >> c[i];

    const long long answer = solve(s, t, c);
    std::cout << "\nHe can accumulate atmost " << answer << " amount of sweetness \n\n";

    return 0;
}

