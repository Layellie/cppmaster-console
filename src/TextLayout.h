#pragma once

#include <cstddef>
#include <string>

// How many terminal columns `text` occupies.
//
// std::string::size() counts bytes, and this interface is Turkish: "Konuları
// Öğren" is 14 characters but 17 bytes, because ı, Ö and ğ each take two in
// UTF-8. Padding by byte count would push every column containing a Turkish
// character out of alignment — and every menu label here has one.
//
// Counting UTF-8 code points (every byte that is not a 10xxxxxx continuation
// byte) is correct for this alphabet. It would not be correct for East Asian
// wide characters or combining marks, which this app has no reason to show.
[[nodiscard]] inline std::size_t displayWidth(const std::string& text) {
    std::size_t width = 0;
    for (const char rawByte : text) {
        // Explicit: char is signed here, and letting the range-for do the
        // conversion implicitly trips -Wconversion on Clang.
        const auto byte = static_cast<unsigned char>(rawByte);
        if ((byte & 0xC0U) != 0x80U) {
            ++width;
        }
    }
    return width;
}

// Pads with spaces on the right until `text` occupies `width` columns.
// Returns it unchanged when it is already at least that wide, so a long
// label pushes its column instead of being truncated.
[[nodiscard]] inline std::string padToWidth(const std::string& text, std::size_t width) {
    const std::size_t current = displayWidth(text);
    if (current >= width) {
        return text;
    }
    return text + std::string(width - current, ' ');
}
