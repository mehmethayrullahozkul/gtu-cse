#include "Set.h"

template <class T> Set<T>::Set()
{
    arr = NULL;
    size = 0;
}

template <class T> void Set<T>::add(T new_item) 
{
    T *copy_arr;

    copy_arr = new T[size+1];
    
    for(int i = 0 ; i < size ; i++)
        copy_arr[i] = arr[i];

    copy_arr[size] = new_item;

    if(arr != NULL)
        delete [] arr;

    arr = new T[size+1];

    for(int i = 0 ; i < size+1 ; i++ )
        arr[i] = copy_arr[i];
    
    size++;
}
 
template <class T> T* Set<T>::getArray()
{
    return arr;
}

template <class T> int Set<T>::getSize()
{
    return size;
}