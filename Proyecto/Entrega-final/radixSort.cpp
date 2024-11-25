#include "header.h"
#include "address.h"

const int R = 256; // Radix for characters in ASCII format

// If d is greater than the length of the string, return -1
int charAt(addressMap<std::string> &map, int row, int col, int d) {
    const std::string& str = map.getCell(row, col);
    if (d < str.length()) {
        return str[d];
    } else {
        return -1;  // Handle shorter strings
    }
}

// MSD radix sort
void radixSort(addressMap<std::string> &map, std::vector<int> &index, std::vector<int> &aux, int low, int high, int d, int col) {
    if(high <= low){
        return;
    }

    std::vector<int> count(R + 2, 0);

    for (int i = low; i <= high; i++) {
        int c = charAt(map, index[i], col, d);
        count[c + 2]++;
    }

    for (int r = 0; r < R + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = low; i <= high; i++) {
        int character = charAt(map, index[i], col, d);
        aux[count[character + 1]++] = index[i];
    }

    for (int i = low; i <= high; i++) {
        index[i] = aux[i - low];
    }

    // Sort further using recursion
    for (int r = 0; r < R; r++) {
        radixSort(map, index, aux, low + count[r], low + count[r + 1] - 1, d + 1, col);
    }
}

void publicSort(addressMap<std::string> &map, std::vector<int> &index, int col) {
    std::vector<int> aux(map.getRowCount());  // temp storage of index
    radixSort(map, index, aux, 0, map.getRowCount() - 1, 0, col);
}