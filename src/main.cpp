#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <sstream>

void hexDump(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "error: unable to open file " << filename << std::endl;
        return;
    }

    std::ofstream dumpFile(filename + ".hex.dump");
    if (!dumpFile) {
        std::cerr << "error: unable to create dump file" << std::endl;
        return;
    }

    std::stringstream output;
    output << "hex dump - " << filename << ":\n\n";
    output << "offset    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F    ASCII\n";
    output << "--------  -----------------------------------------------    ----------------\n";

    char buffer[16];
    long long offset = 0;

    while (file.read(buffer, sizeof(buffer))) {
        output << std::setw(8) << std::setfill('0') << std::hex << offset << "  ";

        for (int i = 0; i < 16; ++i) {
            output << std::setw(2) << std::setfill('0') << std::hex << (unsigned char)buffer[i] << " ";
        }

        output << "   ";

        for (int i = 0; i < 16; ++i) {
            output << (std::isprint(buffer[i]) ? buffer[i] : '.');
        }

        output << std::endl;
        offset += 16;
    }

    std::streamsize remaining = file.gcount();
    if (remaining > 0) {
        output << std::setw(8) << std::setfill('0') << std::hex << offset << "  ";

        for (int i = 0; i < 16; ++i) {
            if (i < remaining) {
                output << std::setw(2) << std::setfill('0') << std::hex << (unsigned char)buffer[i] << " ";
            } else {
                output << "   ";
            }
        }

        output << "   ";

        for (int i = 0; i < remaining; ++i) {
            output << (std::isprint(buffer[i]) ? buffer[i] : '.');
        }

        output << std::endl;
    }

    std::cout << output.str();
    dumpFile << output.str();
    std::cout << "hex dump saved to " << filename << ".hex.dump" << std::endl;
}

void memDump(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "error: Unable to open file " << filename << std::endl;
        return;
    }

    std::ofstream dumpFile(filename + ".mem.dump");
    if (!dumpFile) {
        std::cerr << "error: unable to create dump file" << std::endl;
        return;
    }

    std::stringstream output;
    output << "memory dump of " << filename << ":\n\n";
    output << "address        value\n";
    output << "--------       -----\n";

    char buffer[4];
    long long address = 0;

    while (file.read(buffer, sizeof(buffer))) {
        output << std::setw(8) << std::setfill('0') << std::hex << address << "       ";

        for (int i = 3; i >= 0; --i) {
            output << std::setw(2) << std::setfill('0') << std::hex << (unsigned char)buffer[i];
        }

        output << std::endl;
        address += 4;
    }

    std::cout << output.str();
    dumpFile << output.str();
    std::cout << "memory dump saved to " << filename << ".mem.dump" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " <filename> <--hex|--mem>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string option = argv[2];

    if (option == "--hex") {
        hexDump(filename);
    } else if (option == "--mem") {
        memDump(filename);
    } else {
        std::cerr << "error: unknown argument" << std::endl;
        return 1;
    }

    return 0;
}