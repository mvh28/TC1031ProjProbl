#include "address.h"
#include "header.h"
// If d is greater than the length of the string, return -1
int charAt(addressMap<std::string>& map, int row, int col, int d)
{
    if (map.getRowCount() <= row) {
        return -1;
    }
    try {
        std::string& str = map.getCell(row, col);
        if (d < 0) {
            return -1;
        }
        if (d < str.length()) {
            return static_cast<unsigned char>(str[d]);
        }
        return -1;
    } catch (...) {
        return -1;
    }
}

// MSD radix sort
void radixSort(addressMap<std::string>& map, std::vector<int>& index, std::vector<int>& aux, int low, int high, int d, int col)
{
    if (low < 0 || high < 0 || low > high || high >= index.size()) {
        return;
    }

    if (d > 10){
        return;
    }

    const int R = 256; // Radix for characters in ASCII format
    std::vector<int> count(R + 2, 0);

    for (int i = low; i <= high; i++) {
        if (i >= index.size()){
            break;
        }
        int c = charAt(map, index[i], col, d);
        if (c >= 0 && c < R){
            count[c + 2]++;
        }
    }

    for (int r = 0; r < R + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = low; i <= high; i++) {
        if (i >= index.size()){
            break;
        }
        int character = charAt(map, index[i], col, d);
        if (character >= 0 && character < R && (count[character + 1] - low) < aux.size()){
            aux[count[character + 1] - low] = index[i];
            count[character + 1]++;
        }
    }

    for (int i = low; i <= high; i++) {
        if (i - low < aux.size() && i < index.size()){
            index[i] = aux[i - low];
        }
    }

    // Sort further using recursion
    for (int r = 0; r < R; r++) {
        int lo = low + count[r];
        int hi = high + count[r + 1] - 1;
        if (lo < hi){
            radixSort(map, index, aux, lo, hi, d + 1, col);
        }
    }
}

void reverseOrder(std::vector<int>& index, int low, int high)
{
    while (low < high) {
        std::swap(index[low], index[high]);
        low++;
        high--;
    }
}

void publicSort(addressMap<std::string>& map, std::vector<int>& index, int col)
{
    int size = map.getRowCount();
    if (size <= 1)
        return;

    std::vector<int> aux(size);
    radixSort(map, index, aux, 0, size - 1, 0, col);

    // For play count column, reverse the order to get descending sorting
    if (col == 3) {
        reverseOrder(index, 0, size - 1);
    }
}