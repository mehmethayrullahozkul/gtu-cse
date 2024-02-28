#include <iostream>
#include <vector>


using namespace std;


int main() {



    int LINE_LENGHT;
    int currentLocation = 1;
    int gonnabeRemoved;

    vector<int> line;

    cout<<endl<<". Queue up for the princess, how long would you prefer line to be? ."<<endl;
    cin>>LINE_LENGHT;


    // FILLING UP THE VECTOR
    for(int i = 1 ; i <= LINE_LENGHT ; i++ )
    {
        line.push_back(i);
    }



    // IF LINE LENGHT EQUALS 1 HE ALREADY WON
    if(LINE_LENGHT == 1)
    {cout<<"Current line has one candidate, match found."<<endl;return 0;}

    else

    {
        // WHILE THERE ARE STILL CANDIDATES IN THE VECTOR CONTINUE
        while(line.size() > 1 )
        {


            // IF CURRENT LOCATION OF + 2 BIGGER THAN THE LINE SIZE
            if((currentLocation + 2) > line.size())
            {
                // FOR INSTANCE, IF WE HAVE A LINE OF 3 PEOPLE AND WE ARE START COUNTING FROM 3, THE ONE WILL BE ELIMINATED IS 2, SO FAR (3 + 2) - 3 
                // CURRENT LOCATION + 2 - LINE SIZE
                gonnabeRemoved = (currentLocation + 2) - line.size();
                if(gonnabeRemoved == line.size())
                {
                    currentLocation = 1;

                    // PRINTING OUT INFORMATION
                    /**/
                    for (const int& i : line) {
                    cout << i << " ";
                    }
                    cout<<"is current list of candidates, by counting from "<<line.at(currentLocation)<<", candidate '"<<line.at(line.size()-1)<<"' will be eliminated"<<endl;
                    /**/
                }
                else
                {
                    // PRINTING OUT INFORMATION
                    /**/
                    for (const int& i : line) {
                    cout << i << " ";
                    }
                    cout<<"is current list of candidates, by counting from "<<line.at(currentLocation-1)<<", candidate '"<<line.at(gonnabeRemoved-1)<<"' will be eliminated"<<endl;
                    /**/
                    currentLocation = gonnabeRemoved;
                }
                line.erase(line.begin() + (gonnabeRemoved - 1));
            }


            // IF CURRENT LOCATION + 2 SMALLER THAN THE LINE SIZE
            else if((currentLocation + 2) < line.size())
            {
                gonnabeRemoved = (currentLocation + 2);

                // PRINTING OUT INFORMATION
                /**/
                for (const int& i : line) {
                    cout << i << " ";
                    }
                    cout<<"is current list of candidates, by counting from "<<line.at(currentLocation-1)<<", candidate '"<<line.at(gonnabeRemoved-1)<<"' will be eliminated"<<endl;
                /**/
                line.erase(line.begin() + gonnabeRemoved - 1);
                currentLocation = gonnabeRemoved;
            }


            // IF CURRENT LOCATION + 2 EQUALS THE LINE SIZE
            else if ((currentLocation + 2) == line.size())
            {
                // PRINTING OUT INFORMATION
                /**/
                for (const int& i : line) {
                    cout << i << " ";
                    }
                    cout<<"is current list of candidates, by counting from "<<line.at(currentLocation-1)<<", candidate '"<<line.at(line.size()-1)<<"' will be eliminated"<<endl;
                /**/
                line.erase(line.end()-1);
                currentLocation = 1;
            }
        }


    }
    cout<<"Winner vector is : ";
    for (const int& i : line) {
    cout << i << "  ";
    }
    cout<<endl;


    std::cout<<endl<<" "<<endl<<"PRESS ENTER TO EXIT THE PROGRAM."<<endl;
    cin.ignore();
    cin.ignore();

}