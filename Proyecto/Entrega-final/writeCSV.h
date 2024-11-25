#include "address.h"
#include "header.h"

void writeCSV(const std::string& filename, addressMap<std::string>& map, std::vector<std::string>& header)
{
    if (filename == "") {
        std::cerr << "No filename specified, cannot write" << std::endl;
        return;
    }

    std::ofstream file(filename + ".csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < header.size(); i++) {
        file << header[i];
        if (i < header.size() - 1) {
            file << ",";
        }
    }
    file << "\n";

    for (int i = 0; i < map.getRowCount(); ++i) {
        std::vector<std::string>* row = map.getRow(i);
        if (row != nullptr) {
            for (size_t j = 0; j < row->size(); ++j) {
                file << (*row)[j];
                if (j < row->size() - 1)
                    file << ",";
            }
            file << "\n";
        }
    }

    file.close();
}