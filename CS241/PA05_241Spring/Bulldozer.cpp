#include "Robot.h"
#include "Bulldozer.h"

int Bulldozer::getType()
{
    return BULLDOZER;
}

Bulldozer::Bulldozer(int type, int strength, int hitpoints, string name, int x, int y, Arena *a) : Robot(type, strength, hitpoints, name, x, y, a) {}



int Bulldozer::getDamage()
{
    int dmg = Robot::getDamage();

    return dmg;
}