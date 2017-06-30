#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <algorithm>

using namespace std;

class HashTable {
    private:
    int* table;
    int numElems;
    int nullVal;
    int delVal;

    public:
    int tableSize;
    int numNonNull;

    // constructor func
    HashTable(int tableSize = 13) {
        this->tableSize = tableSize;
        this->nullVal = 0;
        this->delVal = -1;
        this->numElems = 0;
        this->numNonNull = 0;
        this->table = new int[this->tableSize];
        fill_n(this->table, this->tableSize, this->nullVal);
    }

    void printTable() const {
        cout << "Table: " << endl;
        cout << "[ ";
        for(int i = 0; i < this->tableSize; i++) {
            cout << this->table[i] << ", ";
        }
        cout << " ]" << endl;
    }

    // k mod 13 hash function
    int hash(int k) {
        return k % 13;
    }

    // returns an index (or hash) if it exists in the hashtable, otherwise returns -1
    int find(int x) {
        int index = hash(x);

        while (this->table[index] != this->nullVal) {
            // return the index if it is the value we are searching for
            if (this->table[index] != this->delVal && x == this->table[index]) return index; 

            // increment index, because we are ensuring occpancy levels, 
            // we can count on eventually running into a null entry
            index = (index == this->tableSize - 1) ? 0 : index + 1; // increment index
        }

        return -1;
    }

    // if (int x) does not exist in the hashtable, add it
    bool add(int x) {
        int index = find(x);
        if (index != -1) return false;

        // resize table
        if (2 * (this->numNonNull + 1) > this->tableSize) resize();

        index = hash(x);
        // start from index searching linearly for a place to store the new x
        while (this->table[index] != this->nullVal && this->table[index] != this->delVal) {
            // increment index, because we are ensuring occpancy levels, 
            // we can count on eventually running into a null entry
            index = (index == this->tableSize -1) ? 0 : index + 1; // increment index
        }

        // keep track of non null entries
        if (this->table[index] == this->nullVal) {
            this->numNonNull++;
        }

        // increment num elems and set x
        this->numElems++;
        this->table[index] = x;

        return true;
    }

    // if (int x) exists in the hashtable remove it
    bool remove(int x) {
        int index = find(x); // search for an index
        if (index == -1) return false; // return false if it does not exist

        // decrement numElems
        this->numElems--;
        this->table[index] = this->delVal; // delete x

        return true;
    }

    // resizes the array to the minimum size required to satisfy [(2 ^ d) < (3 * number of non nul elems)]
    void resize() {
        // we need to find the smallest non negative number that will satisfy 2 ^ d < 3 * number of non null elems
        int d = 1;
        while ((2 ^ d) < 3*this->numNonNull) d++;

        // copy our current table to a new one 
        int told[this->tableSize];
        int toldSize = this->tableSize;
        for (int i = 0; i < toldSize - 1; i++) {
            told[i] = this->table[i];
        }

        // resize our table and refill with null values
        this->table[(2^d)];
        this->tableSize = (2^d);
        fill_n(this->table, this->tableSize, this->nullVal);

        // iterate through our old hashtable and copy the non null and non deleted values to our new array
        for (int k = 0; k < toldSize - 1; k++) {
            if (told[k] != this->nullVal && told[k] != this->delVal) {
                int index = hash(told[k]);
                while(this->table[index] != this->nullVal) {
                    index = (index == this->tableSize - 1) ? 0 : index + 1;
                }
                this->table[index] = told[k];
            }
        }
    }
};

#endif  // HASHTABLE_H