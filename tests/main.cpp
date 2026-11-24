#include <cstdio>
#include <exception>
#include <filesystem>

#include "TestRunner.h"

int main() {
    try {
        std::filesystem::create_directories("tests/test_data");
        return TestRunner::instance().runAll();
    } catch (const std::exception& error) {
        std::fputs("Unhandled exception in tests: ", stderr);
        std::fputs(error.what(), stderr);
        std::fputc('\n', stderr);
        return 1;
    } catch (...) {
        std::fputs("Unhandled unknown exception in tests\n", stderr);
        return 1;
    }
}
