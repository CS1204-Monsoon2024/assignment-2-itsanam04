#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int size;
    int count; // To track the number of elements in the hash table
    const double loadFactorThreshold = 0.8;

    int hashFunction(int key) {
        return key % size;
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num == 2) return true;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    void rehash() {
        int newSize = nextPrime(size * 2); // Double the size and find the next prime
        vector<int> oldTable = table;      // Backup the current table
        table.clear();
        table.resize(newSize, -1); // Resize the table to the new size
        size = newSize;
        count = 0; // Reset the count and reinsert existing elements

        for (int value : oldTable) {
            if (value != -1) {
                insert(value); // Reinsert elements
            }
        }
    }

    double currentLoadFactor() {
        return (double) count / size; // Calculate the load factor
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize); // Ensure the size is prime
        table.resize(size, -1);        // Initialize table with -1 (empty slots)
        count = 0;
    }

    void insert(int key) {
        // Check if resizing is needed based on the load factor
        if (currentLoadFactor() > loadFactorThreshold) {
            rehash();
        }

        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
            if (i == size) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }
        table[(index + i * i) % size] = key;
        count++;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                table[(index + i * i) % size] = -1;
                count--;
                return;
            }
            i++;
            if (i == size) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }
        cout << "Element not found" << endl;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                return (index + i * i) % size;
            }
            i++;
            if (i == size) {
                return -1; // Not found
            }
        }
        return -1; // Not found
    }
    //print table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
