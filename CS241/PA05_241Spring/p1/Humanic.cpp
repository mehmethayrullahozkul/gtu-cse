#include "Robot.h"
#include "Humanic.h"


Humanic::Humanic(int type, int strength, int hitpoints, string name, int x, int y, Arena *a) : Robot(type, strength, hitpoints, name, x, y, a) {}

int Humanic::getType()
{
    return EMPTY;
}

int Humanic::getDamage()
{

    int damage = Robot::getDamage();

    int random = rand() % 100;

    // %10 change to tactical nuke
    if(random < 10)
    {
        cout << "Humanic Robot : Tactical Nuke!" << endl;
        damage = damage + 50;
    }

    return damage;

}