#include "QuestionHistory.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace {

bool tryParseUint64(const std::string& text, std::uint64_t& outValue) {
    if (text.empty()) {
        return false;
    }
    try {
        std::size_t consumedChars = 0;
        const unsigned long long value = std::stoull(text, &consumedChars);
        if (consumedChars != text.size()) {
            return false;
        }
        outValue = static_cast<std::uint64_t>(value);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

}  // namespace

bool QuestionHistory::hasSeenExact(std::uint64_t exactHash) const {
    return seenExactHashes_.find(exactHash) != seenExactHashes_.end();
}

bool QuestionHistory::hasSeenSemantic(std::uint64_t semanticHash) const {
    return seenSemanticHashes_.find(semanticHash) != seenSemanticHashes_.end();
}

void QuestionHistory::record(const GeneratedQuestion& generated) {
    seenExactHashes_.insert(generated.exactHash);
    seenSemanticHashes_.insert(generated.semanticHash);
}

bool QuestionHistory::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_set<std::uint64_t> parsedExact;
    std::unordered_set<std::uint64_t> parsedSemantic;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        std::string valueText;
        lineStream >> valueText;
        std::uint64_t value = 0;

        if (recordType == "exact") {
            if (!tryParseUint64(valueText, value)) {
                corrupted = true;
                break;
            }
            parsedExact.insert(value);
        } else if (recordType == "semantic") {
            if (!tryParseUint64(valueText, value)) {
                corrupted = true;
                break;
            }
            parsedSemantic.insert(value);
        } else {
            corrupted = true;
            break;
        }
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        seenExactHashes_.clear();
        seenSemanticHashes_.clear();
        return true;
    }

    seenExactHashes_ = std::move(parsedExact);
    seenSemanticHashes_ = std::move(parsedSemantic);
    return false;
}

void QuestionHistory::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    for (const std::uint64_t hash : seenExactHashes_) {
        file << "exact " << hash << '\n';
    }
    for (const std::uint64_t hash : seenSemanticHashes_) {
        file << "semantic " << hash << '\n';
    }
}
