#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;  // Hash table to store values
    vector<bool> occupied;  // To track if the bucket is occupied
    int tableSize;

public:
    HashTable(int size) {
        tableSize = size;
        table.resize(size, -1);  // Initialize hash table with -1 (indicating empty)
        occupied.resize(size, false);  // Initialize occupied vector with false
    }

    // Hash function (simple modulo hash)
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        int index = hashFunction(key);
        int i = 0;  // Quadratic probing starts with i = 0

        // Keep probing until an empty spot is found
        while (occupied[(index + i * i) % tableSize]) {
            i++;  // Quadratic step (i^2)
            if (i == tableSize) {
                cout << "Hash table is full, cannot insert key: " << key << endl;
                return;
            }
        }

        // Insert the key in the calculated index
        index = (index + i * i) % tableSize;
        table[index] = key;
        occupied[index] = true;
        cout << "Inserted key " << key << " at index " << index << endl;
    }

    // Search function using quadratic probing
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Keep probing until the key is found or we determine it's not present
        while (occupied[(index + i * i) % tableSize]) {
            int newIndex = (index + i * i) % tableSize;
            if (table[newIndex] == key) {
                return newIndex;  // Key found
            }
            i++;
            if (i == tableSize) {
                break;  // Stop searching after probing the entire table
            }
        }

        return -1;  // Key not found
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < tableSize; i++) {
            if (occupied[i])
                cout << "Index " << i << ": " << table[i] << endl;
            else
                cout << "Index " << i << ": empty" << endl;
        }
    }
};

