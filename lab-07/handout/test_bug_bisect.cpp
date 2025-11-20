#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "bug_bisect.h"
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>
#include <memory>

std::string to_hex(const int num) {
    std::stringstream ss;
    ss << "0x" << std::uppercase << std::hex << num;
    return ss.str();
}

TestSuiteResult make_passing_suite(const int id, const int n_tests = 10) {
    std::vector<std::unique_ptr<Result> > results;
    results.reserve(n_tests);
    for (int i = 0; i < n_tests; ++i)
        results.push_back(std::make_unique<TestResult<int> >(i, i));
    return {to_hex(id), std::move(results)};
}

TestSuiteResult make_failing_suite(const int id, const int n_tests = 10) {
    std::vector<std::unique_ptr<Result> > results;
    results.reserve(n_tests);
    for (int i = 0; i < n_tests; ++i)
        results.push_back(std::make_unique<TestResult<int> >(i, i + 1));
    return {to_hex(id), std::move(results)};
}

TEST_CASE("bug_bisect - first suite fails") {
    std::vector<TestSuiteResult> suites;
    suites.push_back(make_failing_suite(0));
    suites.push_back(make_failing_suite(1));
    suites.push_back(make_failing_suite(2));
    CHECK(bug_bisect(suites) == to_hex(0));
}

TEST_CASE("bug_bisect - last suite fails") {
    std::vector<TestSuiteResult> suites;
    for (int i = 0; i < 5; ++i)
        suites.push_back(make_passing_suite(i));
    suites.push_back(make_failing_suite(5));
    CHECK(bug_bisect(suites) == to_hex(5));
}

TEST_CASE("bug_bisect - middle suite fails") {
    std::vector<TestSuiteResult> suites;
    for (int i = 0; i < 3; ++i)
        suites.push_back(make_passing_suite(i));
    suites.push_back(make_failing_suite(3));
    for (int i = 4; i < 6; ++i)
        suites.push_back(make_failing_suite(i));
    CHECK(bug_bisect(suites) == to_hex(3));
}

TEST_CASE("bug_bisect - single failing suite") {
    std::vector<TestSuiteResult> suites;
    suites.push_back(make_failing_suite(0));
    CHECK(bug_bisect(suites) == to_hex(0));
}

TEST_CASE("bug_bisect - large dataset") {
    constexpr int total_commits = 10000;
    constexpr int fail_index = 6789;
    std::vector<TestSuiteResult> suites;
    suites.reserve(total_commits);
    for (int i = 0; i < total_commits; ++i) {
        if (i < fail_index)
            suites.push_back(make_passing_suite(i));
        else
            suites.push_back(make_failing_suite(i));
    }
    CHECK(bug_bisect(suites) == to_hex(fail_index));
}

TEST_CASE("bug_bisect - deterministic random fail positions") {
    constexpr int total_commits = 1000000;
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, total_commits - 1);
    for (int run = 0; run < 1000; ++run) {
        int fail_index = dist(rng);
        std::vector<TestSuiteResult> suites;
        suites.reserve(total_commits);
        for (int i = 0; i < total_commits; ++i) {
            if (i < fail_index)
                suites.push_back(make_passing_suite(i));
            else
                suites.push_back(make_failing_suite(i));
        }
        CHECK(bug_bisect(suites) == to_hex(fail_index));
    }
}
