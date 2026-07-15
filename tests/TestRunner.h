#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class TestRunner {
public:
    static TestRunner& instance() {
        static TestRunner runner;
        return runner;
    }

    void addTest(std::string name, std::function<void()> testFunction) {
        tests_.push_back({std::move(name), std::move(testFunction)});
    }

    int runAll() {
        int failedTests = 0;
        for (const auto& test : tests_) {
            currentTestFailureCount_ = 0;
            test.testFunction();
            if (currentTestFailureCount_ == 0) {
                std::cout << "[PASS] " << test.name << '\n';
            } else {
                std::cout << "[FAIL] " << test.name << " (" << currentTestFailureCount_
                           << " check(s) failed)\n";
                ++failedTests;
            }
        }
        const std::size_t passedTests = tests_.size() - static_cast<std::size_t>(failedTests);
        std::cout << '\n' << passedTests << "/" << tests_.size() << " test(s) passed.\n";
        return failedTests == 0 ? 0 : 1;
    }

    void reportFailure(const std::string& expression, const std::string& file, int line) {
        ++currentTestFailureCount_;
        std::cout << "  CHECK failed: " << expression << " at " << file << ":" << line << '\n';
    }

private:
    struct TestCase {
        std::string name;
        std::function<void()> testFunction;
    };

    std::vector<TestCase> tests_;
    int currentTestFailureCount_ = 0;
};

#define CHECK(condition)                                                       \
    do {                                                                       \
        if (!(condition)) {                                                    \
            TestRunner::instance().reportFailure(#condition, __FILE__, __LINE__); \
        }                                                                       \
    } while (false)

#define TEST_CASE(name)                                                     \
    void name();                                                            \
    namespace {                                                             \
    struct name##_registrar {                                               \
        name##_registrar() { TestRunner::instance().addTest(#name, name); } \
    };                                                                      \
    const name##_registrar name##_registrar_instance;                       \
    }                                                                       \
    void name()
