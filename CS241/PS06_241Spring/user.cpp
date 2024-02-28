#include <string>
#include <iostream>
using namespace std;

namespace {
    std::string username;
    int isValid() 
    {
        if(username.size() != 8) {return 0;}
        return 1;
    }
}

namespace Authenticate {
    void inputUserName()
    {
        do
        {
            std::cout << "Enter your username (8 letters only)" << std::endl;
            std::cin >> username;
        }while(!isValid());
    }
    std::string getUserName()
    {
        return username;
    }
}