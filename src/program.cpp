#include <decl.h>
#include <mutex>
#include <thread>

i32 main(const i32 argc, char** argv) {
    if (argc < 2) {
        quit("Invalid number of parameters passed");
    }
    std::vector<std::thread> segments;
    std::mutex guard{};

    for (const auto arg : std::span(&argv[1], argc - 1)) {
        std::scoped_lock scope{guard};
        segments.emplace_back([&]{
            std::filesystem::path argument{arg};

            if (!exists(argument) ||
                !is_directory(argument)) {

                quit("Directory not found");
            }
            argument = canonical(argument);
            searchForDupInsideOf(argument);
        });
    }
    for (auto& thread : segments) {
        thread.join();
    }
    reportDuplicates();

    return {};
}
