#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int partition(vector<int>& arr, int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] > pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    void quicksort(vector<int>& arr, int low, int high)
    {
        if (low < high) {
            int pi = partition(arr, low, high);

            quicksort(arr, low, pi - 1);
            quicksort(arr, pi + 1, high);
        }
    }

public:
    int hIndex(vector<int>& citations)
    {
        int size = citations.size();
        int h = 0;

        // Sort the array first using a simple sort algo (quicksort) or std::sort
        quicksort(citations, 0, size - 1);

        // Linear search to find h-index
        for (int i = 0; i < size; i++) {
            if (i + 1 <= citations[i]) {
                h++;
            } else {
                break;
            }
        }

        // for (int i = 0; i < size; i++){
        //     cout << citations[i] << " ";
        // }
        // cout << endl;
        return h;
    }
};