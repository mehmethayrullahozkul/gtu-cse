#include "Humanic.h"

using namespace std;

#ifndef robo_cop
#define robo_cop

class Robocop : public Humanic {

    friend class Arena;
    
    public:

        Robocop();
        Robocop(int type, int strength, int hitpoints, string name, 
              int x, int y, Arena *a);
        int getType();
        int getDamage();
};


#endif