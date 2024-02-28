#include "Humanic.h"
#include "Robocop.h"

int Robocop::getType()
{
    return ROBOCOP;
}

Robocop::Robocop(int type, int strength, int hitpoints, string name, int x, int y, Arena *a) : Humanic(type, strength, hitpoints, name, x, y, a) {}


int Robocop::getDamage()
{
    int damage = Humanic::getDamage();   
    return damage;
}