#include "AtomicFileWrite.h"

#include <filesystem>
#include <fstream>
#include <system_error>

bool atomicWriteTextFile(const std::string& filePath, const std::string& content) {
    if (filePath.empty()) {
        return false;
    }

    const std::filesystem::path targetPath(filePath);
    std::filesystem::path tempPath = targetPath;
    tempPath += ".tmp";

    {
        std::ofstream tempFile(tempPath, std::ios::trunc);
        if (!tempFile.is_open()) {
            return false;
        }
        tempFile.write(content.data(), static_cast<std::streamsize>(content.size()));
        tempFile.flush();
        const bool writeOk = tempFile.good();
        tempFile.close();
        if (!writeOk || tempFile.fail()) {
            std::error_code removeError;
            std::filesystem::remove(tempPath, removeError);
            return false;
        }
    }

    std::error_code renameError;
    std::filesystem::rename(tempPath, targetPath, renameError);
    if (renameError) {
        std::error_code removeError;
        std::filesystem::remove(tempPath, removeError);
        return false;
    }

    return true;
}
