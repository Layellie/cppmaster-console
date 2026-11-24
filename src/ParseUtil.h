#pragma once

#include <charconv>
#include <cstdint>
#include <string_view>
#include <system_error>

template <typename Integer>
[[nodiscard]] inline bool tryParseInteger(std::string_view text, Integer& outValue) noexcept {
    if (text.empty()) {
        return false;
    }
    Integer value = 0;
    const auto* const begin = text.data();
    const auto* const end = begin + text.size();
    const auto result = std::from_chars(begin, end, value);
    if (result.ec != std::errc{} || result.ptr != end) {
        return false;
    }
    outValue = value;
    return true;
}

[[nodiscard]] inline bool tryParseInt(std::string_view text, int& outValue) noexcept {
    return tryParseInteger<int>(text, outValue);
}

[[nodiscard]] inline bool tryParseInt64(std::string_view text, std::int64_t& outValue) noexcept {
    return tryParseInteger<std::int64_t>(text, outValue);
}

[[nodiscard]] inline bool tryParseUint64(std::string_view text, std::uint64_t& outValue) noexcept {
    return tryParseInteger<std::uint64_t>(text, outValue);
}
