#pragma once
#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>


class Result {
public:
    virtual ~Result() noexcept = default;

    [[nodiscard]] virtual bool is_pass() const noexcept = 0;
};

template<typename T>
class TestResult final : public Result {
    T m_expected_output;
    T m_actual_output;

public:
    TestResult(T expected_output, T actual_output) : m_expected_output(std::move(expected_output)),
                                                     m_actual_output(std::move(actual_output)) {
    }

    [[nodiscard]] bool is_pass() const noexcept override { return m_expected_output == m_actual_output; }
};

class TestSuiteResult final : public Result {
    std::string m_commit_id;
    std::vector<std::unique_ptr<Result> > m_results;

public:
    TestSuiteResult(std::string commit_id,
                    std::vector<std::unique_ptr<Result> > results) : m_commit_id(std::move(commit_id)),
                                                                     m_results(std::move(results)) {
    }

    [[nodiscard]] bool is_pass() const noexcept override {
        return std::all_of(m_results.begin(), m_results.end(),
                           [](const std::unique_ptr<Result> &result) -> bool { return result->is_pass(); });
    }

    [[nodiscard]] const std::string &commit_id() const noexcept {
        return m_commit_id;
    }
};

[[nodiscard]] std::string bug_bisect(const std::vector<TestSuiteResult> &suite_results);
