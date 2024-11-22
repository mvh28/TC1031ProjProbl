#include "header.h"
#include "addressMap.h"
#include "readCSV.h"

int main() {
  addressMap<std::string> csvStorage;
  std::string filename = "./rock-songs.csv";

  std::vector<std::string> headerRow;
  headerRow = {};

  readCSV(filename, csvStorage, headerRow);

  // Print first 10 rows
  std::cout << "Printing first 10 rows:" << std::endl;
  for (const auto& header : headerRow){
    std::cout << header << " ";
  }
  std::cout << std::endl;
  
  for (int i = 0; i < 10; i++) {
      csvStorage.printRow(i);
      csvStorage.printRowAddress(i);
  }

  std::vector<std::string> testA, testB;

  std::cout << "TEST 1: REMOVE ROW" << std::endl;
  csvStorage.removeRow(8);
  std::cout << "Printing first 10 rows:" << std::endl;
  for (const auto& header : headerRow){
    std::cout << header << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < 10; i++) {
      csvStorage.printRow(i);
      csvStorage.printRowAddress(i);
  }

  std::cout << "TEST 2: ADD BACK ROW" << std::endl;
  testA = {"Walk this Way","Run-D.M.C.", "1986", "Raising Hell", "1", "1", "8", "8"};
  csvStorage.insertRow(testA);

  std::cout << "Printing first 10 rows:" << std::endl;
  for (const auto& header : headerRow){
    std::cout << header << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < 10; i++) {
      csvStorage.printRow(i);
      csvStorage.printRowAddress(i);
  }

  std::cout << "TEST 3: ADD A WRONG ROW" << std::endl;
  testB = {"ABCD", "EFGH", "IJKL", "MNOP"};
  csvStorage.insertRow(testB);
}