#include <iostream>
#include <vector>
#include <optional>
#include <stdexcept>

class HashTable {
private:
    struct Entry {
        int key;
        int value;
        bool isOccupied;
        bool isTombstone;

        Entry() : key(0), value(0), isOccupied(false), isTombstone(false) {}
        Entry(int k, int v) : key(k), value(v), isOccupied(true), isTombstone(false) {}
    };

    std::vector<Entry> table;
    size_t size;
    size_t count;
    static constexpr double LOAD_FACTOR_THRESHOLD = 0.8;

    size_t hash(int key) const {
        return static_cast<size_t>(key) % table.size();
    }

    size_t probe(int key, size_t i) const {
        return (hash(key) + i * i) % table.size();
    }

    void resize() {
        std::vector<Entry> oldTable = std::move(table);
        size_t newSize = oldTable.size() * 2;
        table = std::vector<Entry>(newSize);
        size = newSize;
        count = 0;

        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isTombstone) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTable(size_t initialSize = 16) : table(initialSize), size(initialSize), count(0) {}

    void insert(int key, int value) {
        if (static_cast<double>(count) / size > LOAD_FACTOR_THRESHOLD) {
            resize();
        }

        size_t i = 0;
        while (i < size) {
            size_t index = probe(key, i);
            if (!table[index].isOccupied || table[index].isTombstone) {
                table[index] = Entry(key, value);
                count++;
                return;
            } else if (table[index].key == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
        }
        std::cout << "Max probing limit reached!" << std::endl;
    }

    std::optional<int> search(int key) const {
        size_t i = 0;
        while (i < size) {
            size_t index = probe(key, i);
            if (!table[index].isOccupied) {
                return std::nullopt;
            }
            if (table[index].key == key && !table[index].isTombstone) {
                return table[index].value;
            }
            i++;
        }
        return std::nullopt;
    }

    bool remove(int key) {
        size_t i = 0;
        while (i < size) {
            size_t index = probe(key, i);
            if (!table[index].isOccupied) {
                std::cout << "Element not found" << std::endl;
                return false;
            }
            if (table[index].key == key && !table[index].isTombstone) {
                table[index].isTombstone = true;
                count--;
                return true;
            }
            i++;
        }
        std::cout << "Element not found" << std::endl;
        return false;
    }

    void printTable() const {
        for (size_t i = 0; i < size; ++i) {
            if (table[i].isOccupied && !table[i].isTombstone) {
                std::cout << table[i].value;
            } else {
                std::cout << "-";
            }
            if (i < size - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    size_t getSize() const { return size; }
    size_t getCount() const { return count; }
};

