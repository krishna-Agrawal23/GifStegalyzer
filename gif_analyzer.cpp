#include "gif_analyzer.h"

void GifAnalyzer::analyze(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    // Gets the total file size
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::cout << "Starting analysis of: " << filePath << std::endl;
    std::cout << "File size: " << fileSize << " bytes" << std::endl;

    // A valid GIF must be at least 15 bytes (Header + Logical Screen Descriptor + Trailer)
    if (fileSize < 15) {
        std::cerr << "File is too small to be a valid GIF." << std::endl;
        printReport(true, filePath);
        return;
    }

    // Read the GIF header and Logical Screen Descriptor
    GifHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Validate the GIF signature
    if (std::string(header.signature, 3) != "GIF") {
        std::cerr << "File signature is not 'GIF'. This is not a valid GIF file." << std::endl;
        printReport(true, filePath);
        return;
    }

    // Move to the end of the file to check for the trailer
    file.seekg(-1, std::ios::end);
    uint8_t trailerByte = readByte(file);

    // The official GIF trailer is a single semicolon (0x3B)
    if (trailerByte != 0x3B) {
        std::cerr << "Warning: The last byte is not the official GIF trailer (0x3B)." << std::endl;
        printReport(true, filePath);
        return;
    }

    // Move back to the trailer position to check for appended data
    file.seekg(-1, std::ios::end);
    std::streampos trailerPosition = file.tellg();

    // Check for any extra bytes after the trailer
    file.seekg(0, std::ios::end);
    std::streampos endPosition = file.tellg();

    // The fix: Cast the integer '1' to std::streamoff
    if (endPosition > trailerPosition + static_cast<std::streamoff>(1)) {
        std::cout << "Detected " << (endPosition - (trailerPosition + static_cast<std::streamoff>(1))) << " suspicious bytes after the GIF trailer." << std::endl;
        printReport(true, filePath);
    } else {
        std::cout << "No suspicious data detected after the GIF trailer." << std::endl;
        printReport(false, filePath);
    }
}

// ... (rest of the file remains the same)

bool GifAnalyzer::hasAppendedData(std::ifstream& file) {
    std::streampos currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(currentPos);
    
    // Finds the last byte and check if there's anything after it.
    file.seekg(-1, std::ios::end);
    uint8_t lastByte = readByte(file);
    
    // Resets the stream position for the next checks
    file.seekg(0, std::ios::beg);

    if (lastByte == 0x3B) { // Trailer is 0x3B
        std::streampos trailerPos = file.tellg();
        file.seekg(0, std::ios::end);
        std::streampos endPos = file.tellg();
        return (endPos - trailerPos) > static_cast<std::streamoff>(1);
    }
    return false;
}

uint8_t GifAnalyzer::readByte(std::ifstream& file) {
    uint8_t byte;
    file.read(reinterpret_cast<char*>(&byte), 1);
    return byte;
}

std::vector<char> GifAnalyzer::readBytes(std::ifstream& file, size_t count) {
    std::vector<char> buffer(count);
    file.read(buffer.data(), count);
    return buffer;
}

void GifAnalyzer::printReport(bool isSuspicious, const std::string& filePath) {
    std::cout << "\n--- Analysis Report ---" << std::endl;
    std::cout << "File: " << filePath << std::endl;
    std::cout << "Verdict: ";
    if (isSuspicious) {
        std::cout << "🚨 **SUSPICIOUS** 🚨 - Potential malware or data hidden." << std::endl;
    } else {
        std::cout << "✅ **SAFE** ✅ - File appears to be a standard GIF." << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;
}