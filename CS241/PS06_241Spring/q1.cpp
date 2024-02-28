#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;


class DynamicStringArray {
    private:
        string *dynamicArray;
        int size;
    public:

        DynamicStringArray () 
        {
            dynamicArray = NULL;
            size = 0;
        }


        DynamicStringArray(DynamicStringArray &A)
        {
            if(A.size == 0 || A.dynamicArray == NULL)
            {
                this->size = 0;
                this->dynamicArray = NULL;
            }
            else 
            {
                this->dynamicArray = new string[A.size];
                this->size = A.size;
                for(int i = 0 ; i < this->size ; i++)
                {
                    this->dynamicArray[i] = A.dynamicArray[i];
                }
            }
        }


        ~DynamicStringArray () 
        {
            delete[] dynamicArray;
            dynamicArray = NULL;
        }


        DynamicStringArray& operator=(DynamicStringArray &A);
        void addEntry(string s);
        int deleteEntry(string s);
        string getEntry(int a);

        int getSize() {return size;}
        void setSize(int a) {size = a; if(this->dynamicArray != NULL) {delete [] dynamicArray;} dynamicArray = new string[a];}

};


int main(void) {
DynamicStringArray names;
    names.addEntry("Frank");
    names.addEntry("Wiggum");
    names.addEntry("Nahasapeemapetilon");
    names.addEntry("Quimby");
    names.addEntry("Flanders");

    cout << "List of names:" << endl;
    for(int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    names.addEntry("Spuckler");
    cout << "After adding a name:" << endl;
    for(int i = 0; i < names.getSize(); i++)
        cout << names.getEntry(i) << endl;
    
    cout << endl;
    names.deleteEntry("Nahasapeemapetilon");
    cout << "After removing a name:" << endl;
    for(int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
    cout << endl;names.deleteEntry("Skinner");
    cout << "After removing a name that isn't on the list:" << endl;
    for(int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
    cout << endl;

    names.addEntry("Muntz");
    cout << "After adding another name:" << endl;
    for(int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
    cout << endl;

    while(names.getSize() > 0) 
    {names.deleteEntry(names.getEntry(names.getSize() - 1));}
    cout << "After removing all of the names:" << endl;
    for(int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;cout << endl;
    names.addEntry("Burns");
    cout << "After adding a name:" << endl;
    for(int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;cout << endl;
    cout << "Testing copy constructor" << endl;
    DynamicStringArray names2(names);
    names.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for(int i = 0; i < names2.getSize(); i++)
    cout << names2.getEntry(i) << endl;
    cout << endl;
    cout << "Testing assignment" << endl;
    DynamicStringArray names3 = names2;
    names2.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for(int i = 0; i < names3.getSize(); i++)
    cout << names3.getEntry(i) << endl;cout << endl;
    cout << "Enter a character to exit." << endl;char wait;cin >> wait;
    return 0;
}
















void DynamicStringArray::addEntry(string s)
{
    string *copy_arr = new string[size+1];
    for(int i = 0 ; i < size ; i++)
    {
        copy_arr[i] = this->dynamicArray[i];
    }
    copy_arr[size] = s;
    this->setSize(this->size + 1);
    for(int i = 0 ; i < size ; i++)
    {
        this->dynamicArray[i] = copy_arr[i];
    }
}

int  DynamicStringArray::deleteEntry(string s)
{

    // check if array is empty
    if(size == 0 || dynamicArray == NULL)
    {
        return 0;
    }

    // check if given string exists in dynamic array
    int is_found = 0;
    int index = 0;
    int count = -1;
    for(int i = 0 ; i < size ; i++)
    {
      if(dynamicArray[i] == s)
      {
        is_found = 1;
        index = i;
      }  
    }

    if(!is_found) {return false;}

    string *copy_arr = new string[size-1];
    for(int i = 0 ; i < size ; i++)
    {
        count++;
        if(this->dynamicArray[i] == s) {count--;continue;}
        copy_arr[count] = this->dynamicArray[i];

    }
    this->setSize(this->size - 1);
    for(int i = 0 ; i < size ; i++)
    {
        dynamicArray[i] = copy_arr[i];
    }
    return true;
}

string  DynamicStringArray::getEntry(int a)
{
    if(a >= size || a < 0) {return "";}

    return this->dynamicArray[a];

}



DynamicStringArray& DynamicStringArray::operator=(DynamicStringArray &A)
{
    if(A.size == 0 || A.dynamicArray == NULL)
    {
        this->size = 0;
        this->dynamicArray = NULL;
    }
    else 
    {
        this->dynamicArray = new string[A.size];
        this->size = A.size;
        for(int i = 0 ; i < this->size ; i++)
        {
            this->dynamicArray[i] = A.dynamicArray[i];
        }
    }
    return *this;
}