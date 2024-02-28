#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include "Robot.h"

using namespace std;

#ifndef this_is_arena
#define this_is_arena


const int ARENA_SIZE = 10;

class Arena {

    friend class Robot;

    public:

        int RobotCount = 0;
        
        Arena();
        ~Arena();
        Robot * getAt(int x, int y);
        void setAt(int x, int y, Robot *robot);
        void Display();
        void resetMove();

        void Play();
        void Initialize();
    
    protected:
        Robot *arena[ARENA_SIZE][ARENA_SIZE];

};


#endif