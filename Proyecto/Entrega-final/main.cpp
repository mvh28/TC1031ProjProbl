#include "address.h"
#include "header.h"
#include "radixSort.h"
#include "readCSV.h"
#include "writeCSV.h"

void incPlayCount(addressMap<std::string>& map, int row, int col)
{
    std::string playCountStr = map.getCell(row, col);

    if (!playCountStr.empty()) {
        try {
            int playCount = std::stoi(playCountStr);
            playCount++;
            playCountStr = std::to_string(playCount);

            map.updateCell(row, col, playCountStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: play count is not a valid number" << std::endl;
        }
    }
}

void sortPlayCount(addressMap<std::string>& map, std::vector<int>& sortIndex)
{
    sortIndex.clear(); // Clear existing indices
    for (int i = 0; i < map.getRowCount(); i++) {
        if (map.getRow(i) != nullptr) { // Only add indices for existing rows
            sortIndex.push_back(i);
        }
    }

    if (!sortIndex.empty()) {
        try {
            publicSort(map, sortIndex, 3);
        } catch (const std::exception& e) {
            std::cerr << "Error during sorting: " << e.what() << std::endl;
        }
    }
}

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

        // To exit program, don't consider other cases
        if (input == "exit") {
            break;
        }

        // For help input show screan with options
        else if (input == "help") {
            std::cout << "Available commands with opt. inputs" << std::endl;
            std::cout << "help: Show this help message" << std::endl;
            std::cout << "read <filename>: Read a CSV file and update the song list" << std::endl;
            std::cout << "newList <filename>: Create a new song list" << std::endl;
            std::cout << "newSong: Add a new song, will prompt the user" << std::endl;
            std::cout << "removeSong <index>: Remove a song at the given index" << std::endl;
            std::cout << "play <index>: Play the song at the given index" << std::endl;
            std::cout << "save <filename>: Save the current song list to a CSV file" << std::endl;
            std::cout << "exit: Exit the program" << std::endl;
        }

        else if (input.substr(0, 4) == "save") {
            std::stringstream ss(input);
            std::string command;
            std::string saveFilename;
            ss >> command >> saveFilename;

            if (!saveFilename.empty() && saveFilename[0] == ' ') {
                saveFilename.erase(0, 1);
            }

            if (saveFilename.empty()) {
                std::cerr << "Save cancelled. No filename provided." << std::endl;
            } else {
                writeCSV(saveFilename, songArr, headerRow);
                std::cout << "List saved to " << saveFilename << ".csv" << std::endl;
            }
        }

        else if (input.substr(0, 4) == "read") {
            std::stringstream ss(input);
            std::string command;
            std::string filename;
            ss >> command >> filename;

            if (!filename.empty() && filename[0] == ' ') {
                filename.erase(0, 1);
            }

            if (filename.empty()) {
                std::cerr << "Invalid filename or input" << std::endl;
            } else {
                readCSV(filename, songArr, headerRow);
                sortPlayCount(songArr, sortIndex);
            }
        }

        else if (input.substr(0, 5) == "print") {
            std::stringstream ss(input);
            std::string command;
            int size = -1;
            ss >> command;

            if (!(ss >> size) || size < 0) {
                if (sortIndex.size() < 10) {
                    size = sortIndex.size();
                } else {
                    size = 10;
                }
            }

            if (size > sortIndex.size()){
                size = sortIndex.size();
            }

            for (int i = 0; i < headerRow.size(); i++) {
                std::cout << headerRow[i];
                if (i < headerRow.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;

            for (int i = 0; i < size; i++) {
                std :: cout << i << ". ";
                songArr.printRow(i);
            }
            std::cout << std::endl;
        }

        else if (input.substr(0, 4) == "play") {
            std::stringstream ss(input);
            std::string command;
            int i = -1;
            ss >> command;

            if (!(ss >> i)) {
                i = 0; // Default to first item if no index provided
            }

            if (i < 0 || i >= sortIndex.size()) {
                std::cout << "Invalid index. Must be between 0 and " << (sortIndex.size() - 1) << std::endl;
                continue;
            }

            std::string link = songArr.getCell(sortIndex[i], 4);
            if (!link.empty()) {
                system(("start " + link).c_str());
                incPlayCount(songArr, sortIndex[i], 3);
                sortPlayCount(songArr, sortIndex);
            } else {
                std::cout << "Cannot play song: invalid index " << i << std::endl;
            }
        }

        else if (input.substr(0, 7) == "newList") {
            std::stringstream ss(input);
            std::string command;
            std::string filename;
            ss >> command >> filename;
            if (!filename.empty() && filename[0] == ' ') {
                filename.erase(0, 1);
            }

            if (filename.empty()) {
                std::cerr << "Invalid filename" << std::endl;
            } else {
                std::ofstream file(filename + ".csv");

                if (!file.is_open()) {
                    std::cerr << "Error creating file: " << filename << std::endl;
                } else {
                    headerRow = { "Artist", "Song", "Genre", "Number of Plays", "Link to Song" };

                    for (int i = 0; i < headerRow.size(); i++) {
                        file << headerRow[i];
                        if (i < headerRow.size() - 1) {
                            file << ",";
                        }
                    }
                    file << "\n";

                    file.close();

                    readCSV(filename, songArr, headerRow);
                }
            }
        }

        else if (input.substr(0, 7) == "newSong") {
            std::vector<std::string> newSong(5);
            std::string inVal;

            std::cout << "What is the song name?" << std::endl;
            std::getline(std::cin, inVal);
            newSong[1] = inVal;

            std::cout << "What is the artist name?" << std::endl;
            std::getline(std::cin, inVal);
            newSong[0] = inVal;

            std::cout << "What is the genre?" << std::endl;
            std::getline(std::cin, inVal);
            newSong[2] = inVal;

            std::cout << "Please provide a link to the song" << std::endl;
            std::getline(std::cin, inVal);
            newSong[4] = inVal;

            newSong[3] = "0";

            songArr.insertRow(newSong);
            sortPlayCount(songArr, sortIndex);
        }

        else if (input.substr(0, 10) == "removeSong") {
            std::stringstream ss(input);
            std::string command;
            int i;
            ss >> command >> i;
            if (ss.fail()) {
                i = 0;
            }

            songArr.removeRow(sortIndex[i]);
            std::cout << "Cleared song at index " << sortIndex[i];
            sortPlayCount(songArr, sortIndex);
        }

        else {
            std::cout << "Invalid input, for help please type 'help'" << std::endl;
        }

        inNum += 1;
    }

    return -1;
}