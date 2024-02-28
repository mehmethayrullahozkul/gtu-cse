#include "Robot.h"

using namespace std;

#ifndef roo_mba
#define roo_mba

class Roomba : public Robot {

    friend class Arena;
    
    public:

        Roomba();
        Roomba(int type, int strength, int hitpoints, string name, 
              int x, int y, Arena *a);
        int getType();
        int getDamage();
};


#endif