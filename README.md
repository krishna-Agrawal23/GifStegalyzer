## GIFStegalyzer 
A lightweight and efficient C++ tool for detecting potential malware and hidden data within GIF images. 

This project demonstrates low-level file format analysis, a crucial skill in cybersecurity and reverse engineering.

## 💡 Project Motivation 
Steganography is a technique used to conceal a file, message, or image within another file. Malicious actors can hide malware executables or scripts inside seemingly harmless image files like GIFs.

GIFStegalyzer addresses this threat by performing a series of checks on a GIF's binary structure to identify anomalies that suggest a hidden payload.

### This tool is an excellent portfolio piece, showcasing skills in:
- C++ programming fundamentals
- Binary file I/O and manipulation
- Understanding of file formats (GIF89a)
- Cybersecurity and threat detection principles
- Command-line application development

## 🔬 How It Works
GIFStegalyzer performs a primary check for appended data, a common and simple steganographic technique.

A valid GIF file has a specific structure that must end with a single trailer byte (0x3B). Any data found after this byte is considered suspicious and is flagged for further inspection.

The tool's analysis is non-destructive and safe. It does not execute or remove the file; it only reads its binary content and reports its findings.
## 🚀 Getting Started
### Prerequisites
You will need a C++11 compliant compiler (e.g., g++, Clang) and CMake to build the project.

- g++: <mark>sudo apt-get install g++</mark>
- CMake: <mark>sudo apt-get install cmake</mark>
### Build and Run
Clone the repository and build the project from your terminal.
### Clone the repository           
    git clone https://github.com/krishna-Agrawal23/GIFStegalyzer.git
    cd GIFStegalyzer
### Compile the code
    g++ main.cpp gif_analyzer.cpp -o gifstegalyzer -std=c++11
## Usage
Run the compiled executable from your terminal, providing the path to the GIF file you wish to analyze.
### Analyze a sample GIF
    ./gifstegalyzer sample.gif
## Example Output
A safe file will produce the following output:

    Starting analysis of: safe.gif
    File size: 1024 bytes
    No suspicious data detected after the GIF trailer.
           
    --- Analysis Report ---
    File: safe.gif
    Verdict: ✅ **SAFE** ✅ - File appears to be a standard GIF.
    ----------------------
A suspicious file (with appended data) will produce this output:
          
     Starting analysis of: suspicious.gif
     File size: 1100 bytes
     Warning: The last byte is not the official GIF trailer (0x3B).
     Detected 76 suspicious bytes after the GIF trailer.
           
     --- Analysis Report ---
     File: suspicious.gif
     Verdict: 🚨 **SUSPICIOUS** 🚨 - Potential malware or data hidden.
     -----------------------
     
## 📚 Technical Details
The project is structured into three main files:
- <mark>main.cpp:</mark> The entry point of the program.
- <mark>gif_analyzer.h:</mark> Defines the GifAnalyzer class and GIF file structure.
- <mark>gif_analyzer.cpp:</mark> Contains the core logic for parsing the GIF binary data and detecting anomalies.

The <mark>GifAnalyzer</mark> class reads the file in binary mode and performs the following checks:
- File Signature: Verifies the file starts with <amrk>GIF87a</mark> or <mark>GIF89a.</mark>
- Trailer Check: Seeks to the end of the file to ensure the last byte is the GIF trailer (<mark>0x3B</mark>).
- Appended Data: Compares the file size with the position of the trailer to determine if any extra bytes have been appended.

## 🤝 Contributions
Feel free to fork the repository and contribute! Ideas for future improvements include:
- A more comprehensive file parser to analyze other GIF blocks.
- Statistical analysis of pixel data to detect Least Significant Bit (LSB) steganography.
- Integration with a signature database (like YARA rules) to scan for known malware patterns.
- 
## 📄 License
This project is licensed under the MIT License.

#
