#ifndef CSV_READ
#define CSV_READ

#include "header.h"
#include "address.h"

void readCSV(const std::string& filename, addressMap<std::string>& map, std::vector<std::string>& headerRow) {
    if (!map.empty()){
        map.clear();
    }

    std::ifstream file(filename + ".csv"); // Open file

    if (!file.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        throw std::runtime_error("No such file");
    }

    std::string line;

    if(std::getline(file,line)){
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')){
            if (cell.empty()) {
                cell = "NULL"; // Handle empty header cells if needed
            }
            headerRow.push_back(cell);
        }
    }

    while(std::getline(file, line)){ // Read each line from file
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')){
            if (cell.empty()){
                cell = "NULL";
            }
            row.push_back(cell);
        }

        map.insertRow(row);
    }

    file.close();
}

#endif