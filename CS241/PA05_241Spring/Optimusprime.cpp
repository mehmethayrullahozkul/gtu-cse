#include "Robot.h"
#include "Humanic.h"
#include "Optimusprime.h"

int Optimusprime::getType()
{
    return OPTIMUSPRIME;
}

Optimusprime::Optimusprime(int type, int strength, int hitpoints, string name, int x, int y, Arena *a) : Humanic(type, strength, hitpoints, name, x, y, a) {}



int Optimusprime::getDamage()
{

    int damage = Humanic::getDamage();

    int random = rand() % 100;

    // %15 chance to double attack
    if(random < 15)
    {
        cout << "Optimusprime : Double Attack!" << endl;
        damage *= 2;
    }
    
    return damage;
}