#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;

class Student {
    private:
        string name;
        int numClasses;
        string *classList;
    public:
        void InputData() {
            cout<<"Please enter the name of the student : ";
            cin>>name;
            cout<<"Please enter the number of classes student taking : ";
            cin>>numClasses;
            cout<<"Please enter the name of the classes with spacing."<<endl<<" example input, math physics chemistry :: ";
            std::string all_classes;

            // Ignoring the last character in case any problem for std::getline()
            cin.ignore();

            // Getting user input as a line.
            std::getline(std::cin, all_classes);
            classList = new string[numClasses];
            istringstream input(all_classes);
            
            string single_class;

            // This right here tries to convert string from user to words.
            for(int i = 0; input>>single_class ; i++) {
                classList[i] = single_class;
            }
        }


        void OutputData() {
            cout<<"Name of the student : "<<name<<endl;
            if(numClasses < 1)
            {
                cout<<"This student is not taking any classes at the moment."<<endl;
            }
            else
            {
                cout<<"Number of classes student's taking : "<<numClasses<<endl;
                cout<<"Classes student's taking : ";
                for(int i = 0 ; i < numClasses ; i++) 
                {   
                    cout<<" "<<classList[i]<<" ";
                } 
            }
            
        }

        // Deletes the old string array.
        void ResetClasses() {
            numClasses = 0;
            delete[] classList;
            classList = NULL;
        }

        // Copies the old content
        void operator=(const Student& S)
        {
        numClasses = S.numClasses;
        name = S.name;
        classList = new string[numClasses];
        for(int i = 0 ; i < numClasses ; i++) 
        {
            classList[i] = S.classList[i];
        }
        }

        ~Student() {
            delete[] classList;
            classList = NULL;
        }
};



int main () {
    Student Ali;
    Ali.InputData();
    cout<<" "<<endl;
    Ali.OutputData();
    cout<<" "<<endl<<endl;
    Student Ayse;
    Ayse = Ali;
    Ayse.OutputData();
    cout<<" "<<endl<<endl;
    Ali.ResetClasses();
    Ali.OutputData();
    cout<<" "<<endl<<endl;
    Ayse.OutputData();
}