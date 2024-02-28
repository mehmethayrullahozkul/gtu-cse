#include "Humanic.h"

using namespace std;

#ifndef optimus_prime
#define optimus_prime

class Optimusprime : public Humanic {

    friend class Arena;
    
    public:

        Optimusprime();
        Optimusprime(int type, int strength, int hitpoints, string name, 
              int x, int y, Arena *a);
        int getType();
        int getDamage();
};


#endif