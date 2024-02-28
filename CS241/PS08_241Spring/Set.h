#include <iostream>
#include <iostream>

using namespace std;
 
#ifndef set_tt
#define set_tt

template <class T> class Set {
private:
    T* arr;
    int size;

public:
    Set();
    T *getArray();
    int getSize();
    void add(T new_item);
    void Print();

};

#endif