#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    int i;
    for(i = 0; i < argc; i++){
        std::cout << "Argument "<< i << " = " << argv[i] << std::endl;
    }
    cout<<endl<<"Argc value : "<<argc<<endl;
    return 0;
}