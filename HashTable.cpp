#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;
    vector<bool> occupied;
    int tableSize;
    int numElements;

    // Simple hash function (mod table size)
    int hashFunction(int key) {
        return key % tableSize;
    }

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

    // Function to resize and rehash the table
    void resize() {
        int newSize = nextPrime(tableSize);  // Get the next prime number size

        vector<int> newTable(newSize, -1);  // Create new table with the new size
        vector<bool> newOccupied(newSize, false);  // New occupancy vector

        // Rehash all existing elements into the new table
        for (int i = 0; i < tableSize; i++) {
            if (occupied[i]) {
                int key = table[i];
                int index = key % newSize;
                int j = 0;

                // Use quadratic probing in the new table
                while (j < newSize) {
                    int newIndex = (index + j * j) % newSize;
                    if (!newOccupied[newIndex]) {
                        newTable[newIndex] = key;
                        newOccupied[newIndex] = true;
                        break;
                    }
                    j++;
                }
            }
        }

        // Replace the old table with the new table
        table = newTable;
        occupied = newOccupied;
        tableSize = newSize;
    }

public:
    HashTable(int size) {
        tableSize = size;
        table.resize(size, -1);  // Initialize with -1 (indicating empty slots)
        occupied.resize(size, false);  // All slots are initially unoccupied
        numElements = 0;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        // Resize the table if it's more than half full
        if (numElements >= tableSize / 2) {
            resize();
        }

        // Check if the key already exists
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing: search for the next empty slot
        while (i < tableSize) {
            int newIndex = (index + i * i) % tableSize;

            // Insert if the slot is empty
            if (!occupied[newIndex]) {
                table[newIndex] = key;
                occupied[newIndex] = true;
                numElements++;
                return;
            }
            i++;
        }

        // If no empty slot was found
        cout << "Max probing limit reached!" << endl;
    }

    // Remove function using quadratic probing
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find the key
        while (i < tableSize) {
            int newIndex = (index + i * i) % tableSize;

            // Key found, remove it
            if (occupied[newIndex] && table[newIndex] == key) {
                table[newIndex] = -1;  // Mark slot as empty
                occupied[newIndex] = false;
                numElements--;
                return;
            }
            i++;
        }

        // Key not found
        cout << "Element not found" << endl;
    }

    // Search function
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find the key
        while (i < tableSize) {
            int newIndex = (index + i * i) % tableSize;

            // Key found
            if (occupied[newIndex] && table[newIndex] == key) {
                return newIndex;
            }
            i++;
        }

        return -1;  // Key not found
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (occupied[i]) {
                cout << table[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};
