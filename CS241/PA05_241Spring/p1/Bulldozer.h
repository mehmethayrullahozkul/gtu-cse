#include "Robot.h"

using namespace std;

#ifndef bull_dozer
#define bull_dozer

class Bulldozer : public Robot {

    friend class Arena;
    
    public:

        Bulldozer();
        Bulldozer(int type, int strength, int hitpoints, string name, 
              int x, int y, Arena *a);
        int getType();
        int getDamage();
};


#endif