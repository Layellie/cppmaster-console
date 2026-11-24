#include <cstdio>
#include <exception>

#include "Application.h"

// Everything the app does that can realistically throw (filesystem access,
// allocation) happens inside Application. Catching here turns what would
// otherwise be a raw std::terminate crash — with no actionable message,
// and often gone before the user can read it — into a clear error plus a
// non-zero exit code. Using std::fputs in the catch handlers keeps main()
// genuinely noexcept (std::cerr can theoretically throw).
int main() {
    try {
        Application app;
        app.run();
        return 0;
    } catch (const std::exception& error) {
        std::fputs("\nBeklenmeyen bir hata olustu: ", stderr);
        std::fputs(error.what(), stderr);
        std::fputs(
            "\nLutfen bu hatayi bildirin: "
            "https://github.com/Layellie/cppmaster-console/issues\n",
            stderr);
        return 1;
    } catch (...) {
        std::fputs(
            "\nBeklenmeyen ve tanimlanamayan bir hata olustu.\n"
            "Lutfen bu hatayi bildirin: "
            "https://github.com/Layellie/cppmaster-console/issues\n",
            stderr);
        return 1;
    }
}
