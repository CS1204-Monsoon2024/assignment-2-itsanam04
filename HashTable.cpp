#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;
    vector<bool> occupied;
    int tableSize;//size of the hash table
    int numElements;//number of elements currently in the table
    const double loadFactorThreshold = 0.8; // Load factor threshold for resizing
public:
    HashTable(int size) {
        tableSize = size;
        table.resize(size, -1);  // Initialize with -1 (indicating empty slots)
        occupied.resize(size, false);  // All slots are initially unoccupied
        numElements = 0;
    }

    // Simple hash function (mod table size)
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Insert function using quadratic probing
    void insert(int key) {
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
