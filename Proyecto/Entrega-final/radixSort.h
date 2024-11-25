#include "address.h"
#include "header.h"

const int R = 256; // Radix for characters in ASCII format

// If d is greater than the length of the string, return -1
int charAt(addressMap<std::string>& map, int row, int col, int d)
{
    std::string& str = map.getCell(row, col);

    if (col == 3) {
        int num = std::stoi(str);
        std::string numStr = std::to_string(num);
        int pos = numStr.length() - d - 1;
        if (pos >= 0) {
            return numStr[pos] - '0';
        }
        return -1;
    }
    if (d < str.length()) {
        return str[d];
    }
    return -1; // Handle shorter strings
}

// MSD radix sort
void radixSort(addressMap<std::string>& map, std::vector<int>& index, std::vector<int>& aux, int low, int high, int d, int col)
{
    if (high <= low) {
        return;
    }

    int radix = (col == 3) ? 11 : R + 2;
    std::vector<int> count(radix, 0);

    for (int i = low; i <= high; i++) {
        int c = charAt(map, index[i], col, d);
        count[c + 2]++;
    }

    for (int r = 0; r < R + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = low; i <= high; i++) {
        int c = charAt(map, index[i], col, d);
        aux[count[c + 1]++] = index[i];
    }

    for (int i = low; i <= high; i++) {
        index[i] = aux[i - low];
    }

    // Sort further using recursion
    int maxR = (col == 3) ? 10 : R;
    for (int r = 0; r < maxR; r++) {
        radixSort(map, index, aux, low + count[r], low + count[r + 1] - 1, d + 1, col);
    }
}

void reverseOrder(std::vector<int>& index, int low, int high) {
    while (low < high) {
        std::swap(index[low], index[high]);
        low++;
        high--;
    }
}

void publicSort(addressMap<std::string> &map, std::vector<int> &index, int col) {
    int size = map.getRowCount();
    if (size <= 1) return;
    
    std::vector<int> aux(size);
    radixSort(map, index, aux, 0, size - 1, 0, col);
    
    // For play count column, reverse the order to get descending sorting
    if (col == 3) {
        reverseOrder(index, 0, size - 1);
    }
}