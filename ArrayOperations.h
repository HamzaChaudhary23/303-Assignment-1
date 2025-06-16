#ifndef ARRAYOPERATIONS_H
#define ARRAYOPERATIONS_H
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

class ArrayOperations {
private:
    int arr[MAX_SIZE];  // One dimensional array
    int size;           // Current number of elements in array

public:
    // Constructor
    ArrayOperations();

    // Function to read data from input file into array
    bool readFromFile(const string& filename);

    // Function to check if a certain integer exists in the array
    // Returns the index if found, -1 if not found
    int searchElement(int value);

    // Function to modify the value at a given index with exception handling
    // Returns true if successful, throws InvalidIndexException if index is invalid
    bool modifyElement(int index, int newValue, int& oldValue, int& returnedNewValue);

    // Function to add a new integer to the end of the array with exception handling
    // Returns true if successful, throws ArrayFullException if array is full
    bool addElement(int value);

    // Function to remove an integer at a given index
    // Returns true if successful, false if index is invalid
    bool removeElement(int index);

    // Function to display the array
    void displayArray();

    // Function to get current size of array
    int getSize();
};

#endif