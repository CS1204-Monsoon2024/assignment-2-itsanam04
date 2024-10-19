#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;//creaing a hash table
    vector<bool> occ; //keeps track of occupied buckets
    int tableSize;//size of the hash table
    int numElements;// keeps a count of numbers stored

    // Simple hash function 
    int hashFunction(int key) {
        return key % tableSize;
    }

    // checks if a number is prime
    bool is_prime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // // finds the next prime number. Ex: If the double of prime is composite, it will find the next prime number\\
    int next_prime(int current_size) {
    int nextPrime(int currentSize) {
        int new_size = currentSize * 2;
        while (!is_prime(new_size)) {
            new_size++;
        }
        return new_size;
    }

    // Function to resize and rehash the table
    void resize() {
        int new_size = nextPrime(tableSize);  // Get the next prime number size

        vector<int> new_table(new_size, -1);  // Create new table with the new size
        vector<bool> new_occ(new_size, false);  
        // Rehash all existing elements into the new table
        for (int i = 0; i < tableSize; i++) {
            if (occ[i]) {
                int key = table[i];
                int index = key % new_size;
                int j = 0;

                // Use quadratic probing
                while (j < new_size) {
                    int new_index = (index + j * j) % new_size;
                    if (!new_occ[new_index]) {
                        new_table[new_index] = key;
                        new_occ[new_index] = true;
                        break;
                    }
                    j++;
                }
            }
        }

        // replacing old table with the new one
        table = new_table;
        occ = new_occ;
        tableSize = new_size;
    }

public:
    HashTable(int size) {
        tableSize = size;
        table.resize(size, -1);  // intialization with -1 indicates empty slots
        occ.resize(size, false); 
        numElements = 0;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        // Resize the table if it's more than 80% full
        if (numElements >= tableSize * 0.8) {
            resize();
        }

        // Check if the key already exists, if it doesn't, raise a duplicate error
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing: search for the next empty slot
        while (i < tableSize) {
            int new_index = (index + i * i) % tableSize;

            // Insert if the slot is empty
            if (!occ[new_index]) {
                table[new_index] = key;
                occ[new_index] = true;
                numElements++;
                return;
            }
            i++;
        }

        
        cout << "Max probing limit reached!" << endl;
    }

    // Remove function 
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;

    
        while (i < tableSize) {
            int new_index = (index + i * i) % tableSize;

            // Key found, remove it
            if (occ[new_index] && table[new_index] == key) {
                table[new_index] = -1;  // Mark slot as empty
                occ[new_index] = false;
                numElements--;
                return;
            }
            i++;
        }

        // Key not found
        cout << "Element not found" << endl;
    }

    //  Search
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find the key
        while (i < tableSize) {
            int new_index = (index + i * i) % tableSize;

            // Key found
            if (occ[new_index] && table[new_index] == key) {
                return new_index;
            }
            i++;
        }

        return -1;  // Key not found
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (occ[i]) {
                cout << table[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};
