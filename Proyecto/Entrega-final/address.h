#ifndef ADDRESS_STORAGE
#define ADDRESS_STORAGE

#include "header.h"

template <class T> class addressMap;

template <class T>
class addressMap{
    private:
        std::unordered_map<int, std::vector<T>*> storage;
        int rowCount;
        std::stack<int> freeIndex;
    public:
        addressMap();
        ~addressMap();
        void clear();
        bool empty() const;
        void insertRow(const std::vector<T>&);
        std::vector<T>* getRow(int);
        T& getCell(int, int);
        void printRow(int);
        void printRowAddress(int);
        void updateRow(int, const std::vector<T>&);
        void updateCell(int, int, const T&);
        void removeRow(int);
        int getRowCount() const;
};

template <class T>
addressMap<T>::addressMap() : rowCount(0) {};

template <class T>
addressMap<T>::~addressMap(){
    clear();
}

template <class T>
void addressMap<T>::clear() {
    for (auto& pair : storage) {
        delete pair.second; // Free memory
    }
    storage.clear(); // Clear the map
}

template <class T>
bool addressMap<T>::empty() const{
    return storage.empty();
}

template <class T>
void addressMap<T>::insertRow(const std::vector<T>& rowInfo){
    int index;
    if (storage.empty()){
        index = 0;
        storage[index] = new std::vector<T>(rowInfo);
        rowCount = 1;
    }
    else{
        int expectedColumns = storage.begin()->second->size();
        if (rowInfo.size() != expectedColumns){
            std::cout << "Expected columns: " << expectedColumns << std::endl;
            std::cout << "Actual: " << rowInfo.size() << std::endl;
            std::cerr << "Couldn't insert row" << std::endl;
        }
    
        std::vector<T>* newRow = new std::vector<T>(rowInfo);

        if (!freeIndex.empty()){
            index = freeIndex.top();
            freeIndex.pop();
        }
        else{
            index = rowCount++;
        }

        storage[index] = newRow;
    }
    std::cout << "Row inserted at index " << index << std::endl;
}

template <class T>
std::vector<T>* addressMap<T>::getRow(int index){
    if (storage.find(index) != storage.end()){
        return storage.at(index);
    }
    else{
        std::cerr << "No such element" << std::endl;
        return nullptr;
    }
}

template <class T>
T& addressMap<T>::getCell(int index, int col){
    if (storage.find(index) == storage.end()){
        throw std::out_of_range("Row index out of bounds");
    }
    
    std::vector<T>* row = getRow(index);
    
    if (col < 0 || col >= row->size()){
        throw std::out_of_range("Column index out of bounds");
    }

    return (*row)[col];
}

template <class T>
void addressMap<T>::printRow(int index){
    try{
        std::vector<T>* row = getRow(index);
        if (row != nullptr){
            for (const auto& cell : *row){
                std::cout << cell << ", ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::out_of_range& e){
        throw;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

template <class T>
void addressMap<T>::printRowAddress(int rowIndex) {
    try {
        if (storage.find(rowIndex) == storage.end()) {
            throw std::out_of_range("Row index out of bounds");
        }

        std::vector<T>* row = storage[rowIndex];  // Get the pointer to the row
        std::cout << "Address of row " << rowIndex << ": " << row << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

template <class T>
void addressMap<T>::updateRow(int index, const std::vector<T>& rowInfo){
    try{
        std::vector<T>* row = getRow(index);

        if(row != nullptr){
            *row = rowInfo;
        }
    }
    catch (const std::out_of_range& e){
        throw;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

template <class T>
void addressMap<T>::updateCell(int index, int col, const T& newVal){
    try{
        T& cell = getCell(index, col);
        cell = newVal;
    }
    catch (const std::out_of_range& e){
        throw;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

template <class T>
void addressMap<T>::removeRow(int index){
    try{
        if (storage.find(index) == storage.end()){
            throw std::out_of_range("Row index out of bounds");
        }

        delete storage[index];
        storage.erase(index);
        freeIndex.push(index);
        std::cout << "Row " << index << " removed and slot freed" << std::endl;
    }
    catch (const std::out_of_range& e){
        throw;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

template <class T>
int addressMap<T>::getRowCount() const {
    return rowCount;
}

#endif// HASH_STORAGE