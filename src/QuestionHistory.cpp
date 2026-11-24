#include "QuestionHistory.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <system_error>
#include <utility>

#include "AtomicFileWrite.h"
#include "ParseUtil.h"

bool QuestionHistory::hasSeenExact(std::uint64_t exactHash) const {
    return seenExactHashes_.contains(exactHash);
}

bool QuestionHistory::hasSeenSemantic(std::uint64_t semanticHash) const {
    return seenSemanticHashes_.contains(semanticHash);
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
        std::istringstream lineStream(line);
        std::string recordType;
        if (!(lineStream >> recordType)) {
            continue;
        }

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

bool QuestionHistory::saveToFile(const std::string& filePath) const {
    std::ostringstream buffer;
    for (const std::uint64_t hash : seenExactHashes_) {
        buffer << "exact " << hash << '\n';
    }
    for (const std::uint64_t hash : seenSemanticHashes_) {
        buffer << "semantic " << hash << '\n';
    }
    return atomicWriteTextFile(filePath, buffer.str());
}
