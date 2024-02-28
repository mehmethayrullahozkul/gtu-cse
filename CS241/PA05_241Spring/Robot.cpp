#include "Robot.h"
#include "Arena.h"

Robot::Robot() 
{
    x = 0;
    y = 0;
    type = EMPTY;
    name = "";
    strength = 0;
    hitpoints = 0;
    dead = false;
    moved = false;
    r_Arena = NULL;
}

Robot::Robot(int _type, int _strength, int _hitpoints, string _name,
             int posx, int posy, Arena *a)
{
    this->x = posx;
    this->y = posy;
    this->type = _type;
    this->name = _name;
    this->strength = _strength;
    this->hitpoints =  _hitpoints;
    this->dead = false;
    this->moved = false;
    this->r_Arena = a;
    a->setAt(this->x, this->y, this);
    a->RobotCount++;
}


Robot::~Robot() {}



int Robot::getDamage() {
    return (rand() % strength) + 1;
}

/*.......... Getter and Setters ..............*/

string Robot::getName() {return name;}
void Robot::setName(string s) {name = s;}
int Robot::getStrength() {return strength;}
void Robot::setStrength(int s) {strength = s;}
int Robot::getHitpoint() {return hitpoints;}
void Robot::setHitpoint(int s) {hitpoints = s;}
bool Robot::Moved() {if(this->moved) return true; return false;}


/*---------------------------------------------------------------------------------------------------------------------------------------------*/


/*............. FIGHT FUNCTION ..............*/

/* Fight function takes 2 arguments : attacker and defender

    in a loop where both hitpoint values are greater than 0
    {
    attacker attacks defender
    check if defender still alive:
        if not return ATTACKER_WON
    print out message

    defender attacks back to attacker
    check if attacker still alive:
        if not return VICTIM_WON
    print out message
    }

*/

int Fight(Robot *attacker, Robot *defender)
{
    int dmg;
    int a_health = attacker->hitpoints;
    int v_health = defender->hitpoints;

    while(a_health > 0 && v_health > 0)
    {

        // ATTACKERS TURN
        
        dmg = attacker->getDamage();

        cout << attacker->getName() << " (" << attacker->getHitpoint() << ") hits " << defender->getName() << " (" << defender->getHitpoint() <<") with " << dmg << endl;

        // change health value
        v_health = v_health - dmg;

        // set the new value
        defender->setHitpoint(v_health);

        if(defender->getHitpoint() <= 0)
        {
            cout << defender->getName() << " is killed by " << attacker->getName() << endl << endl;
            return ATTACKER_WON;
        }

        cout << "New hitpoints for " << defender->getName() << " is " << defender->getHitpoint() << endl << endl;



        // DEFENDERS TURN

        dmg = defender->getDamage();
        cout << defender->getName() << " (" << defender->getHitpoint() << ") hits " << attacker->getName() << " (" << attacker->getHitpoint() <<") with " << dmg << endl;

        // change health value
        a_health = a_health - dmg;

        // set the new value
        attacker->setHitpoint(a_health);

        if(attacker->getHitpoint() <= 0)
        {
            cout << attacker->getName() << " is killed by " << defender->getName() << endl << endl;
            return VICTIM_WON;
        }

        cout << "New hitpoints for " << attacker->getName() << " is " << attacker->getHitpoint() << endl << endl;
        
    }

    return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/






/*............. MOVE FUNCTION ..............*/

/* Our move function moves the robot once, 
    if it hits another robot:
        return a pointer to that robot.
    if doesnt hit any other robot
        move the robot to that cell
        empty the old cell
        return a null pointer 
*/

Robot * Robot::Move()
{
    int dir = rand() % 4;

    switch(dir)
    {
        case LEFT:
        {
            if(this->y > 0)
            {
                if(r_Arena->getAt(x, y-1) != NULL)
                    return r_Arena->getAt(x, y-1);
                r_Arena->setAt(x, y-1, this);
                r_Arena->setAt(x, y, NULL);
                this->y--;
            }
            break;
        }
        case RIGHT:
        {
            if(this->y < ARENA_SIZE - 1)
            {
                if(r_Arena->getAt(x, y+1) != NULL)
                    return r_Arena->getAt(x, y+1);

                r_Arena->setAt(x, y+1, this);
                r_Arena->setAt(x, y, NULL);
                this->y++;
            }
            break;
        }
        case UP:
        {
            if(this->x > 0)
            {
                if(r_Arena->getAt(x-1, y) != NULL)
                    return r_Arena->getAt(x-1, y);

                r_Arena->setAt(x-1, y, this);
                r_Arena->setAt(x, y, NULL);
                this->x--;
            }
            break;
            
        }
        case DOWN:
        {
            if(this->x < ARENA_SIZE - 1)
            {
                if(r_Arena->getAt(x+1, y) != NULL)
                    return r_Arena->getAt(x+1, y);

                r_Arena->setAt(x+1, y, this);
                r_Arena->setAt(x, y, NULL);
                this->x++;
            }
            break;
        }
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/


