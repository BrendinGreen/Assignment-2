/*
 * List.cpp
 *
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - List is sorted by patient's care card number.
 *                   - Each element is sorted into specific section based on care card number
 *
 * Last modified on: May 2017
 * Author: Brendin Green
 */

#include "List.h"

using namespace std;

// Default constructor
List::List() {
    // Set up element counts and elements array of pointers
    for (int i = 0; i < HASH_SIZE; i++){
        this->elementCounts[i] = 0;
        this->capacities[i] = this->MAX_ELEMENTS;
        this->elements[i] = new Patient[this->MAX_ELEMENTS];
    }
}

// Deep Copy Constructor
List::List(const List& listToCopy){
    for (int i = 0; i < HASH_SIZE; i++){
        this->elementCounts[i] = listToCopy.elementCounts[i];
        this->capacities[i] = listToCopy.capacities[i];
        this->elements[i] = new Patient[this->capacities[i]];

        for (int j = 0; j < this->elementCounts[i]; j++){
            this->elements[i][j] = listToCopy.elements[i][j];
        }
    }
}

// Default deconstructor
List::~List(){
    for (int i = 0; i < HASH_SIZE; i++){
        delete [] this->elements[i];
        this->elements[i] = NULL;
    }
}

int List::getSection(const Patient& newElement) const {
    return newElement.getCareCard()[0] - '0';
}

// Description: Returns the total element count currently stored in List.
int  List::getElementCount() const {
    int sum = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        sum += this->elementCounts[i];
    }
    return sum;
}

// Description: Insert an element.
//              When "this" List is full, its data structure is expanded to accommodate
//              a new element. This is done unbeknown to the client code.
//              If the insertion is successful, true is returned otherwise, false is returned.
// Precondition: newElement must not already be in data collection.
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
bool List::insert(const Patient& newElement){
    int section = getSection(newElement);

    // Increases size if needed
    if (elementCounts[section] == capacities[section]) {
        Patient* newArray = new Patient[2*capacities[section]];
        for (int i = 0; i < elementCounts[section]; i++) {
            newArray[i] = elements[section][i];
        }
        capacities[section] = capacities[section]*2;
        delete [] elements[section];
        elements[section] = newArray;
    }
    // Insert new element
    for (int j = 0; j < elementCounts[section]; j++) {
        if (elements[section][j] == newElement) {
            return false;
        }
        if (elements[section][j] > newElement) {
            for (int k = elementCounts[section]; k > j; k--){
                elements[section][k] = elements[section][k-1];
            }
            elements[section][j] = newElement;
            elementCounts[section]++;
            return true;
        }
    }

    elements[section][elementCounts[section]] = newElement;
    elementCounts[section]++;
    return true;

}

// Description: Remove an element.
//              If the removal is successful, true is returned otherwise, false is returned.
// Postcondition: toBeRemoved is removed, the appropriate elementCount has been decremented.
bool List::remove( const Patient& toBeRemoved ){

    int section = getSection(toBeRemoved);

    for (int i = 0; i < elementCounts[section]; i++){
        if (elements[section][i] == toBeRemoved){
            for (int j = i + 1; j < elementCounts[section]; j++ ) {
                elements[section][j-1] = elements[section][j];
            }
            elementCounts[section]--;
            return true;
        }
    }
    return false;

}

// Description: Remove all elements.
void List::removeAll(){
    for (int i = 0; i < HASH_SIZE; i++){
        elementCounts[i] = 0;
    }
}

// Description: Search for target element and returns a pointer to it if found,
//              otherwise, returns NULL.
Patient* List::search(const Patient& target){

    int section = getSection(target);
    for (int i = 0; i < elementCounts[section]; i++) {
        elements[section][i].printPatient();
        if (elements[section][i] == target){
            return &elements[section][i];
        }
    }
    return NULL;
}

// Description: Prints all n elements stored in List in sort order and does so in O(n).
void List::printList() {
    for (int i = 0; i < HASH_SIZE; i++) {
        for (int j = 0; j < elementCounts[i]; j++) {
            elements[i][j].printPatient();
        }
    }
}