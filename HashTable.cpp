#include <iostream>
#include <cmath>
using namespace std;

class HashTable {
private:
    int* table;        // Array for hash table
    int tableSize;     // Current size of hash table
    int numElements;   // Number of elements currently in the table
    int maxProbing;    // Maximum number of quadratic probes allowed

    // Helper function to check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime number (for resizing)
    int nextPrime(int currentSize) {
        int newSize = currentSize * 2;
        while (!isPrime(newSize)) {
            newSize++;
        }
        return newSize;
    }

    // Function to resize the hash table
    void resize() {
        // Find the next prime number size
        int newSize = nextPrime(tableSize);
        
        // Create a new table of the new size
        int* newTable = new int[newSize];
        for (int i = 0; i < newSize; i++) {
            newTable[i] = -1;  // Initialize with empty values (assuming -1 indicates empty)
        }

        // Rehash all the existing elements into the new table
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != -1) {
                int newIndex = table[i] % newSize;
                int j = 1;
                // Handle collisions using quadratic probing in the new table
                while (newTable[newIndex] != -1) {
                    newIndex = (newIndex + j * j) % newSize;  // Quadratic probing
                    j++;
                }
                newTable[newIndex] = table[i];
            }
        }

        // Delete the old table and replace it with the new one
        delete[] table;
        table = newTable;
        tableSize = newSize;
    }

public:
    // Constructor to initialize table with initial size
    HashTable(int size) {
        tableSize = size;
        numElements = 0;
        maxProbing = size / 2; // Quadratic probing limit (half the table size for efficiency)
        table = new int[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = -1;  // Initialize table with empty values
        }
    }

    // Destructor to clean up memory
    ~HashTable() {
        delete[] table;
    }

    // Insert a value into the hash table using quadratic probing
    void insert(int value) {
        if (numElements >= tableSize / 2) {
            resize();  // Resize the table if it is more than half full
        }

        int index = value % tableSize;
        int j = 1;  // Quadratic probing counter

        // Handle collisions using quadratic probing
        while (table[index] != -1 && table[index] != value) {
            if (j > maxProbing) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
            index = (index + j * j) % tableSize;
            j++;
        }

        if (table[index] == value) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        table[index] = value;
        numElements++;
    }

    // Remove a value from the hash table
    void remove(int value) {
        int index = search(value);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = -1;  // Mark the position as empty
            numElements--;
        }
    }

    // Search for a value in the hash table using quadratic probing
    int search(int value) {
        int index = value % tableSize;
        int j = 1;
        int startIndex = index;

        while (table[index] != -1) {
            if (table[index] == value) {
                return index;
            }
            index = (index + j * j) % tableSize;
            j++;
            if (j > maxProbing || index == startIndex) {
                break;  // If max probing reached or full loop, stop searching
            }
        }
        return -1;
    }

    // Print the current contents of the hash table
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
