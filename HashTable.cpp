#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;
    vector<bool> occupied;
    int tableSize;
    int numElements;
    const double loadFactorThreshold = 0.5;  // Resize when more than 50% full

    // Helper function to calculate hash
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime number greater than n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Helper function to resize the table
    void resize() {
        int newSize = nextPrime(tableSize * 2);  // Find next prime >= 2 * tableSize
        vector<int> oldTable = table;
        vector<bool> oldOccupied = occupied;

        tableSize = newSize;
        table.resize(newSize, -1);
        occupied.resize(newSize, false);
        numElements = 0;

        // Reinsert old elements into the resized table
        for (int i = 0; i < oldTable.size(); i++) {
            if (oldOccupied[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor
    HashTable(int size) {
        tableSize = nextPrime(size);  // Initialize size as the next prime number
        table.resize(tableSize, -1);  // Initialize with -1 (indicating empty)
        occupied.resize(tableSize, false);  // All slots are initially unoccupied
        numElements = 0;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        // Check for duplicates
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // Resize if load factor is exceeded
        if (numElements >= tableSize * loadFactorThreshold) {
            resize();
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find an available slot
        while (i < tableSize) {
            int newIndex = (index + i * i) % tableSize;
            if (!occupied[newIndex]) {
                table[newIndex] = key;
                occupied[newIndex] = true;
                numElements++;
                return;
            }
            i++;
        }

        // If insertion fails after probing
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

    // Search function using quadratic probing
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

    // Print table function
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
