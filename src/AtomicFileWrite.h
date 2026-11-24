#pragma once

#include <string>

// Writes `content` to a sibling temporary file, flushes it, and atomically
// renames it into place so a crash or disk-full error mid-write never leaves
// `filePath` truncated or half-written. Returns false (leaving any existing
// file at `filePath` untouched) if writing or renaming fails.
bool atomicWriteTextFile(const std::string& filePath, const std::string& content);
