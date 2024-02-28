#include <iostream>
#include <string>
using namespace std;

class HA {
    private:
        int x;
        int y;
        int z;
    public:
        HA() {
            ret(*this);
        }
        int ret(HA& new_object) {
            new_object.x = 5;
            new_object.y = 5;
            new_object.z = 5;
            return 1;
        }
        void getXYZ() {
            cout<<endl<<"X : "<<x<<" | Y : "<<y<<" | Z : "<<z<<endl;
        }

};


int main(/*int argc, char * argv[]*/){
    //int i;
    //for(i = 0; i < argc; i++){
    //    std::cout << "Argument "<< i << " = " << argv[i] << std::endl;
    //}
    //return 0;
    HA nr;
    nr.getXYZ();
    return 1;
}