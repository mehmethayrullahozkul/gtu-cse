#include <iostream>
using namespace std;

int main(){
    int primecheck;
    cout<<"\n PRIME NUMBERS BETWEEN 3 and 100 are : \n";

    for(int a = 3 ; a < 100 ; a++)
    {
        primecheck = 1;
        for(int b = 2 ; b < a ; b++)
        {
            if(a % b == 0)
            {
                // If the number a can be divided succesfully to b, then its not prime so primecheck variable becomes 0.
                primecheck = 0;
                break;
            }
        }
        // if primecheck is not 0, then print it because its prime.
        if(primecheck != 0)
        {
            cout<<a<<" ";
        }
    }
    cout<<endl<<endl<<"Press enter to end program..."<<endl;
    cin.ignore();
    return 0;
}
