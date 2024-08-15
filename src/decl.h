// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

#include <cstdint>
#include <format>
#include <filesystem>
#include <fstream>
#include <vector>
#include <print>

using u8 = std::uint8_t;
using i32 = std::int32_t;
using u64 = std::uint64_t;

template<>
struct std::formatter<std::filesystem::path, char> {
    constexpr auto parse(const std::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const std::filesystem::path& path, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", path.string());
    }
};
template<>
struct std::formatter<std::stringstream, char> {
    constexpr auto parse(const std::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const std::stringstream& stream, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", stream.str());
    }
};


template<typename... Args>
void quit(const std::format_string<Args...>& format, Args&&... args) {
    std::print(format, std::forward<Args>(args)...);
    std::print("\n");
    std::terminate();
}

void searchForDupInsideOf(const std::filesystem::path& path);
void validateRegular(const std::filesystem::directory_entry& entry);

void readInto(std::vector<u8>& output, std::ifstream& input);
void addIntoFilter(const std::vector<u8>& hash, const std::filesystem::path& path);
void reportDuplicates();

