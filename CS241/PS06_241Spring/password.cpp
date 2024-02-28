#include <string>
#include <iostream>
using namespace std;

namespace {
    std::string password;
    int isValid() 
    {
        if(password.size() < 8) {return 0;}
        for(int i = 0 ; i < password.size() ; i++) {if(password[i] > '0' || password[i] < '9') return 1;} return 0;
    }
}

namespace Authenticate {
    void inputPassword()
    {
        do
        {
            std::cout << "Enter your password (at least 8 characters " <<"and at least one non-letter)" << std::endl;
            std::cin >> password;
        }while(!isValid());
    }
    std::string getPassword()
    {
        return password;
    }
}