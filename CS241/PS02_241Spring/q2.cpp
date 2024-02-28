#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;


// DID NOT FINISH , MAYBE NEXT TIME...

int checkInput(string s);


int DIGIT_LIMIT = 20;

int main() {

    char NUMBER_ONE[(DIGIT_LIMIT)];
    char NUMBER_TWO[(DIGIT_LIMIT)];

    char INPUT[(DIGIT_LIMIT+1)];


    char select;

    do {
    
    cout<<" Addition program , press 'c' to continue, 'q' to exit the program."<<endl;

    cin>>select;

    if(select == 'q') 
    {
        cout<<" "<<endl<<"Exiting the program, see you next time."<<endl<<" "<<endl;
        return 0;
    }

    else if(select == 'c')
    {
        cout<<"Current number of digit limit is : "<<DIGIT_LIMIT<<"."<<endl;
        cout<<"Please enter number one : ";
        cin>>INPUT;
        if(!checkInput(INPUT))
        {
            cout<<"INVALID INPUT, PLEASE TRY AGAIN."<<endl;
            continue;
        }
        
    }

    else 
    {
        cout<<endl<<" "<<"Invalid input, try again."<<endl<<" "<<endl;    
    }

    } while(select != 'q');
}


int checkInput(string s) {
    for(int i = 0 ; i < s.length() ; i++)
    {
        if((s[i] - 48) < 0 || (s[i] - 48) > 9) {return 0;}
    }
    return 1;
}