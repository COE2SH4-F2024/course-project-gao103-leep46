#include "objPosArrayList.h"
#include <stdexcept>
// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

//copy constructor
objPosArrayList::objPosArrayList(const objPosArrayList &other){
    
    arrayCapacity = other.arrayCapacity;
    listSize = other.listSize;
    aList = new objPos[arrayCapacity];

    for (int i = 0; i<listSize; i++){
        aList[i] = other.aList[i];
    }
}

//copy assignment operator
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &other){
    if (this != &other){

        arrayCapacity = other.arrayCapacity;
        listSize = other.listSize;

        for (int i = 0; i<listSize; i++){
            aList[i] = other.aList[i];
        }
    }
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity){
        int newArrayCapacity = arrayCapacity + 1;
        objPos* newList =  new objPos[newArrayCapacity];

        for (int i = 0; i < listSize; i++){
            newList[i] = aList[i];
        }

        delete[] aList;

        aList = newList;
        arrayCapacity = newArrayCapacity;
    }


    for (int i = listSize -1; i>=0; i--){
        aList[i+1] = aList[i]; 
    }

    aList[0] = thisPos;

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity){
        int newArrayCapacity = arrayCapacity + 1;
        objPos* newList =  new objPos[newArrayCapacity];

        for (int i = 0; i < listSize; i++){
            newList[i] = aList[i];
        }

        delete[] aList;

        aList = newList;
        arrayCapacity = newArrayCapacity;
    }

    aList[listSize] = thisPos;

    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0){
        return;
    }

    for (int i = 0; i<listSize; i++){
        aList[i] = aList[i+1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0){
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    /*if (listSize == 0){
        throw std::out_of_range("Empty List.");
    }*/

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    /*if (listSize == 0){
        throw std::out_of_range("Empty List.");
    }*/

    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    /* if (index < 0 || index > listSize){
        throw std::out_of_range("Invalid indexes.");
    }*/
    return aList[index];
}