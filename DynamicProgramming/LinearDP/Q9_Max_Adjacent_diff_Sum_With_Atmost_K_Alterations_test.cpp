#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#define main q9_original_main
#include "Q9_Max_Adjacent_diff_Sum_With_Atmost_K_Alterations.cpp"
#undef main

namespace {

using Clock = std::chrono::steady_clock;
const long long NEGATIVE_INFINITY = std::numeric_limits<long long>::min() / 4;

long long score(const std::vector<int>& values, unsigned int mask) {
    long long total = 0;
    int previous = (mask & 1U) == 0 ? values[0] : 0;

    for (size_t index = 1; index < values.size(); ++index) {
        const int current = (mask & (1U << index)) == 0 ? values[index] : 0;
        total += std::llabs(static_cast<long long>(current) - previous);
        previous = current;
    }

    return total;
}

// Exhaustive oracle for small arrays. It checks every valid set of altered indices.
long long brute_force(const std::vector<int>& values, int k) {
    long long answer = 0;
    const unsigned int mask_count = 1U << values.size();

    for (unsigned int mask = 0; mask < mask_count; ++mask) {
        if (__builtin_popcount(mask) <= static_cast<unsigned int>(k))
            answer = std::max(answer, score(values, mask));
    }

    return answer;
}

// Independent O(NK) oracle for large arrays. Unreachable states use a sentinel.
long long linear_reference(const std::vector<int>& values, int k) {
    if (values.size() <= 1)
        return 0;

    std::vector<std::vector<long long>> previous(
        k + 1, std::vector<long long>(2, NEGATIVE_INFINITY));
    previous[0][0] = 0;
    if (k >= 1)
        previous[1][1] = 0;

    for (size_t index = 1; index < values.size(); ++index) {
        std::vector<std::vector<long long>> current(
            k + 1, std::vector<long long>(2, NEGATIVE_INFINITY));

        for (int alterations = 0; alterations <= k; ++alterations) {
            if (previous[alterations][0] != NEGATIVE_INFINITY) {
                current[alterations][0] = std::max(
                    current[alterations][0],
                    previous[alterations][0] + std::llabs(
                        static_cast<long long>(values[index]) - values[index - 1]));
            }
            if (previous[alterations][1] != NEGATIVE_INFINITY) {
                current[alterations][0] = std::max(
                    current[alterations][0] + 0,
                    previous[alterations][1] + std::llabs(
                        static_cast<long long>(values[index])));
            }
            if (alterations == 0)
                continue;

            if (previous[alterations - 1][0] != NEGATIVE_INFINITY) {
                current[alterations][1] = std::max(
                    current[alterations][1],
                    previous[alterations - 1][0] + std::llabs(
                        static_cast<long long>(values[index - 1])));
            }
            if (previous[alterations - 1][1] != NEGATIVE_INFINITY) {
                current[alterations][1] = std::max(
                    current[alterations][1], previous[alterations - 1][1]);
            }
        }

        previous.swap(current);
    }

    long long answer = 0;
    for (int alterations = 0; alterations <= k; ++alterations) {
        answer = std::max(answer, previous[alterations][0]);
        answer = std::max(answer, previous[alterations][1]);
    }
    return answer;
}

struct TestCase {
    std::string name;
    std::vector<int> values;
    int k;
    bool exhaustive;
};

std::string input_description(const TestCase& test) {
    if (test.values.size() > 15)
        return "<deterministic generated input>";

    std::string description = "[";
    for (size_t index = 0; index < test.values.size(); ++index) {
        if (index != 0)
            description += ", ";
        description += std::to_string(test.values[index]);
    }
    return description + "]";
}

void add_random_cases(std::vector<TestCase>& tests) {
    std::mt19937 generator(20260921U);
    const std::vector<int> sizes = {2, 3, 4, 5, 7, 10, 15, 20};

    for (int size : sizes) {
        for (int case_number = 0; case_number < 100; ++case_number) {
            std::vector<int> values(size);
            for (int& value : values)
                value = static_cast<int>(generator() % 41) - 20;
            tests.push_back({"random-" + std::to_string(size) + "-" +
                                 std::to_string(case_number),
                             values, case_number % size + 1, true});
        }
    }

    const std::vector<int> boundary_values = {
        -100000, -99999, -1, 0, 1, 99999, 100000};
    for (int case_number = 0; case_number < 200; ++case_number) {
        const int size = 2 + static_cast<int>(generator() % 19);
        std::vector<int> values(size);
        for (int& value : values)
            value = boundary_values[generator() % boundary_values.size()];
        tests.push_back({"boundary-random-" + std::to_string(case_number),
                         values, case_number % size + 1, true});
    }
}

struct ExhaustiveResult {
    size_t cases = 0;
    size_t passed = 0;
    long long elapsed_microseconds = 0;
};

void enumerate_arrays(const std::vector<int>& domain, size_t target_size,
                      size_t index, std::vector<int>& values, int k,
                      ExhaustiveResult& result) {
    if (index == target_size) {
        ++result.cases;
        const long long expected = brute_force(values, k);
        const long long output = solve(values, k);
        result.passed += output == expected ? 1 : 0;
        return;
    }

    for (int value : domain) {
        values[index] = value;
        enumerate_arrays(domain, target_size, index + 1, values, k, result);
    }
}

ExhaustiveResult run_exhaustive_domain(const std::vector<int>& domain,
                                       size_t maximum_size) {
    ExhaustiveResult result;
    const auto start = Clock::now();

    for (size_t size = 1; size <= maximum_size; ++size) {
        std::vector<int> values(size);
        for (int k = 1; k <= static_cast<int>(size); ++k)
            enumerate_arrays(domain, size, 0, values, k, result);
    }

    result.elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                                      Clock::now() - start)
                                      .count();
    return result;
}

void add_large_cases(std::vector<TestCase>& tests) {
    std::vector<int> linear_100k(100000);
    for (size_t index = 0; index < linear_100k.size(); ++index)
        linear_100k[index] = static_cast<int>((index * 7919) % 200001) - 100000;
    tests.push_back({"large-n100000-k1", linear_100k, 1, false});

    std::vector<int> linear_100k_k2(100000);
    for (size_t index = 0; index < linear_100k_k2.size(); ++index)
        linear_100k_k2[index] = (index % 11 == 0) ? 100000 :
                                 ((index % 7 == 0) ? -100000 : static_cast<int>(index % 101) - 50);
    tests.push_back({"large-n100000-k2", linear_100k_k2, 2, false});

    std::vector<int> medium(2500);
    for (size_t index = 0; index < medium.size(); ++index)
        medium[index] = (index % 3 == 0) ? 100000 : (index % 3 == 1 ? -100000 : 0);
    tests.push_back({"medium-n2500-k2500", medium, 2500, false});

    std::vector<int> medium_k1000(5000);
    for (size_t index = 0; index < medium_k1000.size(); ++index)
        medium_k1000[index] = (index % 5 == 0) ? 100000 :
                              (index % 5 == 1 ? -100000 : static_cast<int>(index % 200) - 100);
    tests.push_back({"medium-n5000-k1000", medium_k1000, 1000, false});
}

}  // namespace

int main() {
    std::vector<TestCase> tests = {
        {"single-element", {42}, 1, true},
        {"two-elements-positive", {5, 10}, 1, true},
        {"two-elements-negative", {-10, -3}, 1, true},
        {"all-zero", {0, 0, 0, 0, 0}, 3, true},
        {"alternating-extremes", {100000, -100000, 100000, -100000}, 2, true},
        {"negative-and-zero", {-9, 0, -4, 0, -12}, 2, true},
        {"best-flip-is-interior", {10, 1, 10}, 1, true},
        {"all-flips-allowed", {8, -6, 4, -2, 0}, 5, true},
        {"unreachable-state-trap", {1, 100, 2, 99, 3}, 1, true},
        {"repeated-values", {7, 7, 7, 7, 7, 7}, 2, true},
    };
    add_random_cases(tests);
    add_large_cases(tests);

    const ExhaustiveResult exhaustive = run_exhaustive_domain({-2, -1, 0, 1, 2}, 7);
    const ExhaustiveResult ternary_exhaustive = run_exhaustive_domain({-1, 0, 1}, 9);

    std::cout << "Exhaustive domain {-2,-1,0,1,2}, N<=7: "
              << exhaustive.passed << '/' << exhaustive.cases << " passed in "
              << exhaustive.elapsed_microseconds << " us\n";
    std::cout << "Exhaustive domain {-1,0,1}, N<=9: "
              << ternary_exhaustive.passed << '/' << ternary_exhaustive.cases
              << " passed in " << ternary_exhaustive.elapsed_microseconds << " us\n\n";

    std::cout << std::left << std::setw(29) << "case"
              << std::setw(38) << "input"
              << std::right << std::setw(7) << "N"
              << std::setw(7) << "K"
              << std::setw(18) << "output"
              << std::setw(18) << "expected"
              << std::setw(10) << "correct"
              << std::setw(14) << "time (us)" << '\n';
    std::cout << std::string(141, '-') << '\n';

    size_t passed = 0;
    long long total_microseconds = 0;

    for (const TestCase& test : tests) {
        const long long expected = test.exhaustive
                                       ? brute_force(test.values, test.k)
                                       : linear_reference(test.values, test.k);
        const auto start = Clock::now();
        const long long output = solve(test.values, test.k);
        const auto finish = Clock::now();
        const long long elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
                                       finish - start)
                                       .count();
        const bool correct = output == expected;
        passed += correct ? 1 : 0;
        total_microseconds += elapsed;

        std::cout << std::left << std::setw(29) << test.name
                  << std::setw(38) << input_description(test)
                  << std::right << std::setw(7) << test.values.size()
                  << std::setw(7) << test.k
                  << std::setw(18) << output
                  << std::setw(18) << expected
                  << std::setw(10) << (correct ? "PASS" : "FAIL")
                  << std::setw(14) << elapsed << '\n';
    }

    const size_t exhaustive_cases = exhaustive.cases + ternary_exhaustive.cases;
    const size_t exhaustive_passed = exhaustive.passed + ternary_exhaustive.passed;
    const size_t total_cases = tests.size() + exhaustive_cases;
    const size_t total_passed = passed + exhaustive_passed;
    std::cout << '\n' << "Listed cases: " << passed << '/' << tests.size() << '\n';
    std::cout << "All cases: " << total_passed << '/' << total_cases << '\n';
    std::cout << "Total solve time: " << total_microseconds << " us\n";
    return total_passed == total_cases ? 0 : 1;
}