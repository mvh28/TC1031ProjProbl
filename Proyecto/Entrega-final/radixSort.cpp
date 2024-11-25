#include <iostream>
#include <vector>
#include <string>

const int R = 256; // Radix for characters in ASCII format

// If d is greater than the length of the string, return -1
int charAt(std::vector<std::vector<std::string>> &arr, int row, int col, int d) {
    const std::string& str = arr[row][col];
    if (d < str.length()) {
        return str[d];
    } else {
        return -1;  // Handle shorter strings
    }
}

// MSD radix sort
void radixSort(std::vector<std::vector<std::string>> &arr, std::vector<int> &index, std::vector<int> &aux, int low, int high, int d, int col) {
    if(high <= low){
        return;
    }

    std::vector<int> count(R + 2, 0);

    for (int i = low; i <= high; i++) {
        int c = charAt(arr, index[i], col, d);
        count[c + 2]++;
    }

    for (int r = 0; r < R + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = low; i <= high; i++) {
        int character = charAt(arr, index[i], col, d);
        aux[count[character + 1]++] = index[i];
    }

    for (int i = low; i <= high; i++) {
        index[i] = aux[i - low];
    }

    // Sort further using recursion
    for (int r = 0; r < R; r++) {
        radixSort(arr, index, aux, low + count[r], low + count[r + 1] - 1, d + 1, col);
    }
}

void publicSort(std::vector<std::vector<std::string>> &arr, std::vector<int> &index, int col) {
    std::vector<int> aux(arr.size());  // temp storage of index
    radixSort(arr, index, aux, 0, arr.size() - 1, 0, col);
}

void printArray(std::vector<std::vector<std::string>> &arr, std::vector<int> &index){
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[index[i]].size(); j++) {
            std::cout << arr[index[i]][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    int input;
    std::vector<std::vector<std::string>> arr =
    {{"X8jJ7", "fNATD", "eyJJC", "xmejC", "RDRHN"},
    {"vMqMU", "RcZzZ", "9U8Wt", "rYwkE", "gNAUE"},
    {"r3Bah", "GVdX3", "mH0J0", "m5hAP", "AyeHu"},
    {"RDYkQ", "P7dJW", "NNM4G", "c9xSB", "u1DFd"},
    {"TQaTe", "nbKyh", "xWQZt", "jSG3n", "mBurQ"},
    {"idNEr", "vkTqV", "AFkK0", "mCJAV", "3BEGD"},
    {"PYzLH", "RJpjY", "RFvLz", "4xu04", "HavYc"},
    {"0vQ1j", "9hKHt", "BB5wv", "iiq6j", "c1Yr4"},
    {"GaxPd", "xgt0g", "x27uT", "HBVm4", "WpuyH"},
    {"bgyzv", "4mcR9", "cZN09", "9tzU0", "awAZL"}};
    
    std::vector<int> sortIndex(arr.size());
    for (int i = 0; i < arr.size(); i++){
        sortIndex[i] = i;
    }

    std::cout << "Sort by column (index starting @ 0): ";
    std::cin >> input; // Using std::getline() to be able to read whitespaces as well

    if (input > arr.size() || input < 0){
        std::cout << "Invalid column number";
        return -1;
    }

    std::cout << "Array before sorting:" << std::endl;
    printArray(arr, sortIndex);
    std::cout << std::endl;

    publicSort(arr, sortIndex, input);

    std::cout << "Array after sorting" << std::endl;
    printArray(arr, sortIndex);

    return 0;
}