#include "objPosArrayList.h"
#include <stdexcept>

// Constructor
objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];

}

// Destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Copy Constructor
objPosArrayList::objPosArrayList(const objPosArrayList &other){
    
    arrayCapacity = other.arrayCapacity;
    listSize = other.listSize;
    aList = new objPos[arrayCapacity];

    for (int i = 0; i<listSize; i++){
        aList[i] = other.aList[i];
    }
}

// Copy Assignment Pperator
// First checks whether the objPosArrayList isn't identical
    // If not, it deletes the old array to prevent memory leakage and copies the objPosArrayList &other contents
    // If so, nothing happens
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &other){
    if (this != &other) {
        delete[] aList; // Deletes old array to prevent memory leakage
        arrayCapacity = other.arrayCapacity;
        listSize = other.listSize;

        for (int i = 0; i<listSize; i++){
            aList[i] = other.aList[i];
        }
    }
}

// Getter for the array length
int objPosArrayList::getSize() const
{
    return listSize;
}

// Inserts element to the head of the snake
void objPosArrayList::insertHead(objPos thisPos)
{
    // If the current list can't hold more elements...
    // Make a new list with an incremented list size and copy elements from the original list to the new list
    if (listSize >= arrayCapacity){
        int newArrayCapacity = arrayCapacity + 1;
        objPos* newList =  new objPos[newArrayCapacity];

        for (int i = 0; i < listSize; i++){
            newList[i] = aList[i];
        }

        // Delete old list contents to prevent memory leakage
        delete[] aList;

        // Updates the old list with the new list contents and size
        aList = newList;
        arrayCapacity = newArrayCapacity;
    }

    // Shuffles the elements one index to the right
    for (int i = listSize -1; i>=0; i--){
        aList[i+1] = aList[i]; 
    }

    // Inserts the new head element as the first element
    aList[0] = thisPos;

    // Increment list size
    listSize++;
}

// Inserts element to the tail of the snake
void objPosArrayList::insertTail(objPos thisPos)
{   
    // If the current list can't hold more elements...
    // Make a new list with an incremented list size and copy elements from the original list to the new list
    if (listSize >= arrayCapacity){
        int newArrayCapacity = arrayCapacity + 1;
        objPos* newList =  new objPos[newArrayCapacity];

        for (int i = 0; i < listSize; i++){
            newList[i] = aList[i];
        }

        // Delete old list contents to prevent memory leakage
        delete[] aList;

        // Updates the old list with the new list contents and size
        aList = newList;
        arrayCapacity = newArrayCapacity;
    }

    // Inserts the new head element as the last element
    aList[listSize] = thisPos;

    // Increment list size
    listSize++;
}

// Removes the head (first) element
void objPosArrayList::removeHead()
{
    // Don't do anything if the array size is zero
    if (listSize == 0){
        return;
    }

    // Shuffles the elements one index to the left
    for (int i = 0; i<listSize; i++){
        aList[i] = aList[i+1];
    }

    // List size is one less than before
    listSize--;
}

// Removes the tail (last) element
void objPosArrayList::removeTail()
{
    // Don't do anything if the array size is zero
    if (listSize == 0){
        return;
    }
    
    // Otherwise, list size is one less than before (which removes the last element)
    listSize--;
}

// Returns the head (first) element of the list
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

// Returns the tail (last) element of the list
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

// Returns the element (set by the parameter) of the list
objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}