#pragma once

#include <cstdint>
#include <string_view>

constexpr std::uint64_t fnv1a64(std::string_view text) noexcept {
    constexpr std::uint64_t offsetBasis = 14695981039346656037ULL;
    constexpr std::uint64_t prime = 1099511628211ULL;

    std::uint64_t hash = offsetBasis;
    for (const unsigned char character : text) {
        hash ^= character;
        hash *= prime;
    }
    return hash;
}
