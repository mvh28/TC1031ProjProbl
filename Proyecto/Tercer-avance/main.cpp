#include "address.h"
#include "header.h"
#include "readCSV.h"

int main()
{
    std::string input;
    int inNum = 0;
    addressMap<std::string> songArr;
    std::vector<std::string> headerRow;
    headerRow = {};

    std::vector<int> sortIndex(songArr.getRowCount());
    for (int i = 0; i < songArr.getRowCount(); i++) {
        sortIndex[i] = i;
    }

    while (true) {
        std::cout << "Input " << inNum << ": ";
        std::getline(std::cin, input);

        // To exit proram, don't consider other cases
        if (input == "exit") {
            break;
        }

        // For help input show screan with options
        else if (input == "help") {
            std::cout << "Available commands with opt. inputs\n"
                      << std::endl;
        }

        else if (input.substr(0, 4) == "read") {
            std::stringstream ss(input);
            std::string command;
            std::string filename;
            ss >> command;

            std::getline(ss, filename);
            if (!filename.empty() && filename[0] == ' ') {
                filename.erase(0, 1);
            }

            if (filename.empty()) {
                std::cout << "Invalid filename or input" << std::endl;
            } else {
                readCSV(filename, songArr, headerRow);
            }
        }

        else if (input.substr(0, 5) == "print") {
            std::stringstream ss(input);
            std::string command;
            int size;
            ss >> command >> size;

            if (ss.fail()) {
                if (sortIndex.size() < 10) {
                    size = sortIndex.size();
                } else {
                    size = 10;
                }
            }

            for (int i = 0; i < size; i++) {
                songArr.printRow(i);
            }
            std::cout << std::endl;
        }

        else if (input.substr(0, 6) == "filter") {

        }

        else if (input.substr(0, 4) == "play") {
            std::stringstream ss(input);
            std::string command;
            int i;
            ss << command << i;

            if (ss.fail()){
                i = 0;
            }

            std::string link = songArr.getCell(sortIndex[i], 4);
            system(("start " + link).c_str());
        }

        else if (input.substr(0, 7) == "newList") {

        }

        else if (input.substr(0, 7) == "newSong") {

        }

        else if (input.substr(0, 10) == "removeSong") {
            std::stringstream ss(input);
            std::string command;
            int i;
            ss << command << i;
            if (ss.fail()){
                i = 0;
            }

            songArr.removeRow(sortIndex[i]);
            std::cout << "Cleared song at index " << sortIndex[i];
        }

        else {
            std::cout << "Invalid input, for help please type 'help'" << std::endl;
        }

        inNum += 1;
    }

    return -1;
}