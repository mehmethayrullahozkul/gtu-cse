#include "PFArrayD.h"
#include <iostream>
// inc test array h

using std::cin;
using std::cout;
using std::endl;

void testPFArrayD();

int main() 
{
    cout << "This program tests the class PFArrayD. " << endl;

    char ans;
    do
    {
        testPFArrayD();
        cout << "Test Again? (y/n)" << endl;
        cin >> ans;
    }while((ans=='y') || (ans=='Y'));

    return 0;
}

void testPFArrayD()
{
    int cap;
    cout << "Enter capacity of this super array : ";
    cin >> cap;
    PFArrayD temp(cap);

    cout << "Enter up to " << cap << "non negative numbers." << endl;
    cout << "Place a negative number at the end" << endl;

    double next;
    cin >> next;

    while((next >= 0 ) && (!temp.full()))
    {
        try
        {
            temp.addElement(next);
            cin >> next;
        }
        catch(OutOfRange E)
        {
            cout << E.getMessage();
        }
        
    }

    cout << "You entered the following : " << endl <<
    temp.getNumberUsed() << " numbers: " << endl;

    int count = temp.getNumberUsed();

    for(int i = 0 ; i < count ; i++)
    {
        try
        {
            cout << temp[i] << "-";
        }
        catch(OutOfRange e)
        {
            cout << e.getMessage();
        }
        
    }
    cout << endl;

    cout << "Trying to acces [-1] " << endl;
    try
    {
        cout << temp[-1] << endl;
    }
    catch(OutOfRange E)
    {
        cout << E.getMessage();
    }
    

    try
    {
        temp.addElement(99999);
    }
    catch(OutOfRange E)
    {
        cout << E.getMessage();
    }

}