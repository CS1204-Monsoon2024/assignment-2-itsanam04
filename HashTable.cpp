#include <iostream>
#include <vector> 
using namespace std;

class HashTable {
private:
    vector<int> table; //creaing a hash table
    int size; //size of the hash table
    vector<bool> occ ; //keeps track of occupied buckets
    int elements_count; // keeps a count of numbers stored

    // Simple hash function 
    int hashFunction(int key) {
        return key % size;
    } 

    // checks if a number is prime
    bool is_prime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // finds the next prime number. Ex: If the double of prime is composite, it will find the next prime number\\
    int next_prime(int current_size) {
        int new_size= current_size * 2;
        while (!is_prime(new_size)) { 
            new_size++;
        }
        return new_size;
    } 
    // Function to resize and rehash the table
    void resize() {
        int new_size = next_prime(size);  // Get the next prime number size

        vector<int> new_table(new_size, -1);  // Create new table with the new size
        vector<bool> new_occ(new_size, false);  

        // Rehash all existing elements into the new table
        for (int i = 0; i < size; i++) {
            if (occ[i]) {
                int key = table[i];
                int index = key % new_size;
                int j = 0;

                // Use quadratic probing in the new table
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

        // Replace the old table with the new table
        table = new_table;
        occ = new_occ;
        size = new_size;
    }

public:
    HashTable(int n) {
        size = n;
        table.resize(n, -1);  // intialization with -1 indicates empty slots
        occ.resize(n, false);  // 
        elements_count = 0;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        // Resize the table if it's more than 80% full
        if (elements_count >= size * 0.8) {
            resize();
        }
        // Check if the key already exists, if it does then raises the duplicate error
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        int index = hashFunction(key);
        int i = 0;

        //  Search for the next empty slot using quadratic probing
        while (i < size) {
            int new_index = (index + i * i) % size;

            // Insert if the slot is empty
            if (!occ[new_index]) {
                table[new_index] = key;
                occ[new_index] = true;
                elements_count++;
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

        // Quadratic probing to find the key
        while (i < size) {
            int new_index = (index + i * i) % size;

            // Remove the key if found
            if (occ[new_index] && table[new_index] == key) {
                table[new_index] = -1;  // Mark slot as empty
                occ[new_index] = false;
                elements_count--; //decrease in the size of the table
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
        while (i < size) {
            int new_index = (index + i * i) % size;

            // if key is found, return it
            if (occ[new_index] && table[new_index] == key) {
                return new_index;
            }
            i++;
        }

        return -1;  // If key not found, return -1
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (occ[i]) {
                cout << table[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};
