#include "Robot.h"
#include "Roomba.h"

int Roomba::getType()
{
    return ROOMBA;
}

Roomba::Roomba(int type, int strength, int hitpoints, string name, int x, int y, Arena *a) : Robot(type, strength, hitpoints, name, x, y, a) {}



int Roomba::getDamage()
{

    int damage1 = Robot::getDamage();
    int damage2 = Robot::getDamage();

    cout << "Roomba's are super fast, they attack twice, first attack " << damage1 << " second attack " << damage2 << endl;  

    return damage1 + damage2;
}