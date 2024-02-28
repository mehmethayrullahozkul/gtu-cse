#include <iostream>
#include "PFArrayD.h"
#include <string>

using namespace std;

int OutOfRange::getIndex() const
{
    return index;
}

string OutOfRange::getMessage() const {
    return (message + "\n");
}

OutOfRange::OutOfRange(string thisMessage, int thisIndex)
                : message(thisMessage), index(thisIndex)
{}

PFArrayD::PFArrayD() : capacity(50), used(0)
{
    a = new double[capacity];
}

PFArrayD::PFArrayD(int size) : capacity(size), used(0)
{
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject)
    :capacity(pfaObject.getCapacity()), used(pfaObject.getNumberUsed())

{
    a = new double[capacity];
    for(int i = 0 ; i < used ; i++)
        a[i] = pfaObject.a[i];
}

void PFArrayD::addElement(double element)
{
    if(used >= capacity)
    {
        throw OutOfRange("OutofRange Exception, attempt to insert beyond declared size ", used);
    }
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index)
{
    if(index >= used)
    {
        throw OutOfRange("OutOfRange Exception, index value: ", index);
    }
    return a[index];
}

PFArrayD& PFArrayD::operator=(const PFArrayD& rightSide)
{
    if(this == &rightSide)
    {
        return *this;
    }
    if(capacity != rightSide.capacity)
    {
        delete [] a;
        a = new double[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;

    for(int i = 0 ; i < used ; i++)
        a[i] = rightSide.a[i];

    return *this;
}

PFArrayD::~PFArrayD() 
{
    delete [] a;
}