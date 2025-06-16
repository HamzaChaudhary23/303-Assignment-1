//============================================================================

// Date: 16 June 2025
// Assignment 1
// Features implemented:
//   • Read integers from a file into an array (with size limit checking)
//   • Display array contents and current size
//   • Linear search for an element
//   • Modify an element at a given index (throws on invalid index)
//   • Append a new element (throws when the array is full)
//   • Remove an element at a given index (with element‑shifting)

//============================================================================

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

// Maximum size for the array
const int MAX_SIZE = 1000;

// -----------------------------------------------------------------------------
// Custom exception classes
// -----------------------------------------------------------------------------
/// Thrown when a user tries to access an array element with an out‑of‑range index.
class InvalidIndexException : public exception {
private:
    string message;
public:
    InvalidIndexException() : message("Invalid index") {}
    InvalidIndexException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ArrayFullException : public exception {
private:
    string message;
public:
    ArrayFullException() : message("Array is full") {}
    ArrayFullException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Global variables
int arr[MAX_SIZE];  // One dimensional array
int arraySize = 0;  // Current number of elements in array

// Function to read data from input file into array
bool readFromFile(const string& filename) {
    ifstream inputFile(filename);

    // Check if file opened successfully
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    int value;
    arraySize = 0;

    // Read integers from file until end of file or array is full
    while (inputFile >> value && arraySize < MAX_SIZE) {
        arr[arraySize] = value;
        arraySize++;
    }

    inputFile.close();
    cout << "Successfully read " << arraySize << " elements from file." << endl;
    return true;
}

// Function to check if a certain integer exists in the array
// Returns the index if found, -1 if not found
int searchElement(int value) {
    // Search through the array linearly
    for (int i = 0; i < arraySize; i++) {
        if (arr[i] == value) {
            return i;  // Return index where element is found
        }
    }
    return -1;  // Element not found
}

// Function to modify the value at a given index with exception handling
// Returns true if successful, throws exception if index is invalid
bool modifyElement(int index, int newValue, int& oldValue, int& returnedNewValue) {
    // Check if index is valid - throw exception if not
    if (index < 0 || index >= arraySize) {
        throw InvalidIndexException("Invalid index: " + to_string(index) +
            ". Index should be between 0 and " + to_string(arraySize - 1));
    }

    // Store old value
    oldValue = arr[index];

    // Set new value
    arr[index] = newValue;
    returnedNewValue = newValue;

    cout << "Element at index " << index << " modified successfully." << endl;
    cout << "Old value: " << oldValue << ", New value: " << returnedNewValue << endl;

    return true;
}

// Function to add a new integer to the end of the array with exception handling
// Returns true if successful, throws exception if array is full
bool addElement(int value) {
    // Check if array is full - throw exception if it is
    if (arraySize >= MAX_SIZE) {
        throw ArrayFullException("Array is full with " + to_string(MAX_SIZE) +
            " elements. Cannot add more elements.");
    }

    // Add element to the end of array
    arr[arraySize] = value;
    arraySize++;

    cout << "Element " << value << " added successfully at index " << (arraySize - 1) << endl;
    return true;
}

// Function to remove an integer at a given index
// Returns true if successful, false if index is invalid
bool removeElement(int index) {
    // Check if index is valid
    if (index < 0 || index >= arraySize) {
        cout << "Error: Invalid index. Index should be between 0 and " << (arraySize - 1) << endl;
        return false;
    }

    int removedValue = arr[index];

    // Shift all elements after the removed element to the left
    for (int i = index; i < arraySize - 1; i++) {
        arr[i] = arr[i + 1];
    }

    // Decrease size
    arraySize--;

    cout << "Element " << removedValue << " removed successfully from index " << index << endl;
    return true;
}

// Function to display the array
void displayArray() {
    if (arraySize == 0) {
        cout << "Array is empty." << endl;
        return;
    }

    cout << "Array contents (" << arraySize << " elements): ";
    for (int i = 0; i < arraySize; i++) {
        cout << arr[i];
        if (i < arraySize - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

// Function to get current size of array
int getSize() {
    return arraySize;
}

// Function to display menu options
void displayMenu() {
    cout << "\n========== Array Operations Menu ==========" << endl;
    cout << "1. Display Array" << endl;
    cout << "2. Search for an Element" << endl;
    cout << "3. Modify an Element (with Exception Handling)" << endl;
    cout << "4. Add an Element (with Exception Handling)" << endl;
    cout << "5. Remove an Element" << endl;
    cout << "6. Exit" << endl;
    cout << "===========================================" << endl;
    cout << "Enter your choice (1-6): ";
}

// Main function
int main() {
    // Initialize array elements to 0
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = 0;
    }

    // Read data from input file
    cout << "Reading data from A1input.txt..." << endl;
    if (!readFromFile("A1input.txt")) {
        cout << "Failed to read from file. Exiting program." << endl;
        return 1;
    }

    // Display initial array
    cout << "\nInitial ";
    displayArray();

    int choice;
    bool exitProgram = false;

    // Main menu loop
    while (!exitProgram) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // Display Array
            cout << "\nCurrent ";
            displayArray();
            break;
        }

        case 2: {
            // Search for an Element
            int searchValue;
            cout << "\nEnter the value to search for: ";
            cin >> searchValue;

            int index = searchElement(searchValue);
            if (index != -1) {
                cout << "Element " << searchValue << " found at index " << index << endl;
            }
            else {
                cout << "Element " << searchValue << " not found in the array." << endl;
            }
            break;
        }

        case 3: {
            // Modify an Element with Exception Handling
            int index, newValue, oldValue, returnedNewValue;
            cout << "\nEnter the index of element to modify: ";
            cin >> index;
            cout << "Enter the new value: ";
            cin >> newValue;

            try {
                modifyElement(index, newValue, oldValue, returnedNewValue);
            }
            catch (const InvalidIndexException& e) {
                cout << "Exception caught: " << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "Unexpected exception caught: " << e.what() << endl;
            }
            break;
        }

        case 4: {
            // Add an Element with Exception Handling
            int value;
            cout << "\nEnter the value to add: ";
            cin >> value;

            try {
                addElement(value);
            }
            catch (const ArrayFullException& e) {
                cout << "Exception caught: " << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "Unexpected exception caught: " << e.what() << endl;
            }
            break;
        }

        case 5: {
            // Remove an Element
            int index;
            cout << "\nEnter the index of element to remove: ";
            cin >> index;

            removeElement(index);
            break;
        }

        case 6: {
            // Exit
            cout << "\nThank you for using the Array Operations program!" << endl;
            exitProgram = true;
            break;
        }

        default: {
            cout << "\nInvalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
        }
    }

    return 0;
}