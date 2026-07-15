#include <filesystem>

#include "TestRunner.h"

int main() {
    std::filesystem::create_directories("tests/test_data");
    return TestRunner::instance().runAll();
}
