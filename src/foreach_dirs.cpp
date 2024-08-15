#include <decl.h>

void searchForDupInsideOf(const std::filesystem::path& path) {
    const std::filesystem::directory_iterator dir(path);
    const std::filesystem::directory_iterator end;
    if (dir == end) {
        return;
    }

    for (const auto& entry : dir) {
        if (entry.is_directory()) {
            searchForDupInsideOf(entry.path());
            continue;
        }
        if (entry.is_regular_file()) {
            validateRegular(entry);
        }
    }
}
