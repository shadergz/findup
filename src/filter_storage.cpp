#include <unordered_map>
#include <cstring>
#include <mutex>

#include <chrono>
#include <print>

#include <decl.h>
struct Hash {
    explicit Hash(const std::vector<u8>& input) : data(input) {}
    auto operator == (const Hash& cmp) const {
        return std::ranges::equal(data, cmp.data);
    }

    std::vector<u8> data;
};
struct HashAsKey {
    std::size_t operator()(const Hash& key) const {
        std::array<u64, 4> check{};
        std::memcpy(&check[0], &key.data[0], sizeof(check));

        return
            std::hash<u64>()(check[0]) ^
            std::hash<u64>()(check[1]) ^
            std::hash<u64>()(check[2]) ^
            std::hash<u64>()(check[3]);
    }
};

struct DuplicateList {
    DuplicateList() = default;
    explicit DuplicateList(const std::filesystem::path& first) :
        origin(first) {}
    std::filesystem::path origin;
    std::vector<std::filesystem::path> same;
};

std::unordered_map<Hash, DuplicateList, HashAsKey> storage;
std::mutex dupLock;

void addIntoFilter(const std::vector<u8>& hash, const std::filesystem::path& path) {
    const Hash block{hash};
    std::scoped_lock lock(dupLock);

    if (storage.contains(block)) {
        storage[block].same.push_back(path);
    } else {
        storage[block] = DuplicateList{path};
    }
}

std::string arrayToString(const std::vector<u8>& array) {
    std::stringstream ss;
    for (const auto byte : array) {
        ss << std::hex << (byte >> 4);
        ss << std::hex << (byte & 0xf);
    }
    return ss.str();
}

void reportDuplicates() {
    std::scoped_lock lock(dupLock);
    u64 entry{};
    std::stringstream ss;

    // ReSharper disable once CppUseElementsView
    for (const auto& [first, duplicated] : storage) {
        const auto& list{duplicated.same};
        const auto& origin{duplicated.origin};

        if (list.size() && !is_empty(list.front())) {
            ss << std::format("{} - Found duplicates from: {} ({})\n", entry++, origin, arrayToString(first.data));
        }

        for (const auto& all : list) {
            auto created{last_write_time(all)};
            ss << std::format("\t - {} = {}\n", all, created);
        }
    }
    std::print("{}\n", ss);
}