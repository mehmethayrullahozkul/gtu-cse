#include "Robot.h"

using namespace std;

#ifndef hum_anic
#define hum_anic

class Humanic : public Robot {

    friend class Arena;
    
    public:

        Humanic();
        Humanic(int type, int strength, int hitpoints, string name, 
              int x, int y, Arena *a);
        int getType();
        int getDamage();
};


#endif