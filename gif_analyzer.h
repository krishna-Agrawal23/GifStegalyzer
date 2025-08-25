

#ifndef GIF_ANALYZER_H
#define GIF_ANALYZER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#pragma pack(push, 1)

// GIF File Header (6 bytes)
struct GifHeader {
    char signature[3];
    char version[3];
};

// Logical Screen Descriptor (7 bytes)
struct LogicalScreenDescriptor {
    uint16_t width;
    uint16_t height;
    uint8_t packedFields;
    uint8_t backgroundColorIndex;
    uint8_t pixelAspectRatio;
};

#pragma pack(pop)

class GifAnalyzer {
public:
    // Main analysis function
    void analyze(const std::string& filePath);

private:

    bool hasAppendedData(std::ifstream& file);

  
    void printReport(bool isSuspicious, const std::string& filePath);

    uint8_t readByte(std::ifstream& file);

  
    std::vector<char> readBytes(std::ifstream& file, size_t count);
};

#endif // GIF_ANALYZER_H