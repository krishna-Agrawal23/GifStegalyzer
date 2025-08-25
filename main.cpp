#include "gif_analyzer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path_to_gif_file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    GifAnalyzer analyzer;
    analyzer.analyze(filePath);

    return 0;
}