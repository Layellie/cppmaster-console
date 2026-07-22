#pragma once

#include <cstdint>
#include <string_view>

constexpr std::uint64_t fnv1a64(std::string_view text) noexcept {
    constexpr std::uint64_t offsetBasis = 14695981039346656037ULL;
    constexpr std::uint64_t prime = 1099511628211ULL;

    std::uint64_t hash = offsetBasis;
    for (const char character : text) {
        // FNV-1a is defined over bytes, so the sign of char is irrelevant
        // here — but the conversion is made explicit rather than left
        // implicit, both to say so and because char's signedness is
        // implementation-defined.
        hash ^= static_cast<unsigned char>(character);
        hash *= prime;
    }
    return hash;
}
