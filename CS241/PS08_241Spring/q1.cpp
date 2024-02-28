
#include "Set.h"
#include "Set.cpp"

int main () {
    Set<int> s1;
    Set<string> s2;

    int *intArray = NULL;
    string *stringArray = NULL;

    int i;

    s1.add(10);
    s1.add(20);
    s1.add(15);
    s1.add(40);


    intArray = s1.getArray();

    cout << "Set one has " << s1.getSize() << " items in it." << endl;
    cout << "Items listed as : " << endl;

    for(int i = 0 ; i < s1.getSize() ; i++)
        cout << intArray[i] << "  ";
    
    cout << endl;

    if(intArray != NULL)
        delete [] intArray;
    

    s2.add("new york");
    s2.add("amsterdam");
    s2.add("istanbul");
    s2.add("mexico");

    stringArray = s2.getArray();

    cout << "Set two has " << s2.getSize() << " items in it." << endl;
    cout << "Items listed as : " << endl;

    for(int i = 0 ; i < s2.getSize() ; i++)
        cout << stringArray[i] << "  ";
    
    cout << endl;

    if(stringArray != NULL)
        delete [] stringArray;


}