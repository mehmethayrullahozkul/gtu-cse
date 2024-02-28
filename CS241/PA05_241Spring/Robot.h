#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

using namespace std;

#ifndef robots_vs_humans
#define robots_vs_humans

const int OPTIMUSPRIME = -1;
const int ROBOCOP = -2;
const int ROOMBA = -3;
const int BULLDOZER = -4;
const int EMPTY = -5;

const int ATTACKER_WON = 1;
const int VICTIM_WON = 2;

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

const int INITAL_ROBOT_COUNT = 5;

class Arena;

class Robot {
    
    friend class Arena;
    friend int Fight(Robot *attacker, Robot *defender);

    public:

        Robot();
        Robot(int _type, int _strength, int _hitpoints, string _name,
             int posx, int posy, Arena *a);
        ~Robot();

        virtual int getType() = 0;
        Robot *Move();
        virtual int getDamage();
        bool Moved();

        string getName();
        void setName(string s);

        int getStrength();
        void setStrength(int s);

        int getHitpoint();
        void setHitpoint(int s);

    protected:

        int x, y;
        int type;
        string name;
        int strength;
        int hitpoints;
        bool dead, moved;
        Arena *r_Arena;
};

#endif