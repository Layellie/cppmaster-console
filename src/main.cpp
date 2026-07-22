#include <exception>
#include <iostream>

#include "Application.h"

// Everything the app does that can realistically throw (filesystem access,
// allocation) happens inside Application. Catching here turns what would
// otherwise be a raw std::terminate crash — with no actionable message,
// and often gone before the user can read it — into a clear error plus a
// non-zero exit code.
int main() {
    try {
        Application app;
        app.run();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "\nBeklenmeyen bir hata olustu: " << error.what() << '\n'
                  << "Lutfen bu hatayi bildirin: "
                     "https://github.com/Layellie/cppmaster-console/issues\n";
        return 1;
    } catch (...) {
        std::cerr << "\nBeklenmeyen ve tanimlanamayan bir hata olustu.\n"
                  << "Lutfen bu hatayi bildirin: "
                     "https://github.com/Layellie/cppmaster-console/issues\n";
        return 1;
    }
}
