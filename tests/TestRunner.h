#pragma once

#include <cstddef>
#include <exception>
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
            try {
                test.testFunction();
            } catch (const std::exception& exception) {
                ++currentTestFailureCount_;
                std::cout << "  Uncaught exception: " << exception.what() << '\n';
            } catch (...) {
                ++currentTestFailureCount_;
                std::cout << "  Uncaught exception of unknown type\n";
            }
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

// name must be unique across all test files - it becomes a function with
// external linkage, so a collision is a link error, not a local compile error.
#define TEST_CASE(name)                                                     \
    void name();                                                            \
    namespace {                                                             \
    struct name##_registrar {                                               \
        name##_registrar() { TestRunner::instance().addTest(#name, name); } \
    };                                                                      \
    const name##_registrar name##_registrar_instance;                       \
    }                                                                       \
    void name()
