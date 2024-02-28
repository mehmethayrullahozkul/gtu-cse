#include "Arena.h"
#include "Robot.h"
#include "Bulldozer.h"
#include "Roomba.h"
#include "Humanic.h"
#include "Optimusprime.h"
#include "Robocop.h"


// sets the cell's robot to entered robot
void Arena::setAt(int x, int y, Robot *robot)
{
    if((robot != NULL) && (x >= 0) && (x < ARENA_SIZE) && (y >= 0) && (y < ARENA_SIZE))
    {
        this->arena[x][y] = robot;
        return;
    }
    arena[x][y] = NULL;


}


// gets the robot on that cell
Robot * Arena::getAt(int x, int y)
{
    return arena[x][y];
}


// initializes the arena
Arena::Arena() 
{
    for(int a = 0 ; a < ARENA_SIZE ; a++)
    {
        for(int b = 0 ; b < ARENA_SIZE ; b++)
        {
            arena[a][b] = NULL;
        }
    }
}

// deletes all the robots
Arena::~Arena()
{
    for(int a = 0 ; a < ARENA_SIZE ; a++)
    {
        for(int b = 0 ; b < ARENA_SIZE ; b++)
        {
            if(arena[a][b] != NULL )delete arena[a][b];
        }
    }
}


// displays the game's current situation
void Arena::Display()
{
    for(int a = 0 ; a <= ARENA_SIZE ; a++)
    {
        for(int b = 0 ; b <= ARENA_SIZE ; b++)
        {

            if(a==0 && b==0)
                std::cout << "  ";
            
            else if(a==0 && b > 0)
                std::cout << b-1 << " ";
            
            else if(b==0 && a > 0)
                std::cout << a-1 << " ";

            else if(a > 0 && b > 0)
            {
                if(arena[a-1][b-1] == NULL) {std::cout << ". "; continue;}
                switch(arena[a-1][b-1]->getType())
                {
                    case OPTIMUSPRIME:
                        std::cout << "O "; break;
                    case ROBOCOP:
                        std::cout << "C "; break;
                    case ROOMBA:
                        std::cout << "R "; break;
                    case BULLDOZER:
                        std::cout << "B "; break;
                }
            }
        }
        std::cout << endl;
    }
    std::cout << endl;
}


/*........... INITIALIZE FUNCTION ............*/

/*  creates new robots in the game arena */

void Arena::Initialize()
{
    int a, b;

    int robot_count = 0;

    string bulldozer = "bulldozer_";
    string roomba = "roomba_";
    string optimusprime = "optimusprime_";
    string robocop = "robocop_";

    // create bulldozer
    while(robot_count < INITAL_ROBOT_COUNT)
    {
        int x = rand() % ARENA_SIZE;
        int y = rand() % ARENA_SIZE;

        if(arena[x][y] == NULL)
        {
            Bulldozer *bd = new Bulldozer(BULLDOZER, 50, 200, bulldozer + to_string(robot_count), x, y, this);
            robot_count++;
        }
    }

    robot_count = 0;

    // create roomba
    while(robot_count < INITAL_ROBOT_COUNT)
    {
        int x = rand() % ARENA_SIZE;
        int y = rand() % ARENA_SIZE;

        if(arena[x][y] == NULL)
        {
            Roomba *rb = new Roomba(ROOMBA, 3, 10, roomba + to_string(robot_count), x, y, this);
            robot_count++;
        }
    }

    robot_count = 0;

    // create optimusprime
    while(robot_count < INITAL_ROBOT_COUNT)
    {
        int x = rand() % ARENA_SIZE;
        int y = rand() % ARENA_SIZE;

        if(arena[x][y] == NULL)
        {
            Optimusprime *op = new Optimusprime(OPTIMUSPRIME, 100, 100, optimusprime + to_string(robot_count), x, y, this);
            robot_count++;
        }
    }

    robot_count = 0;

    // create robocop
    while(robot_count < INITAL_ROBOT_COUNT)
    {
        int x = rand() % ARENA_SIZE;
        int y = rand() % ARENA_SIZE;

        if(arena[x][y] == NULL)
        {
            Robocop *rp = new Robocop(ROBOCOP, 30, 40, robocop + to_string(robot_count), x, y, this);
            robot_count++;
        }
    }
}


/*............. PLAY FUNCTION ..............*/

/*  Runs through every cell until find a robot didnt moved yet
    when found:
        display the arena before robot moves
        store the position of the robot
        set Attacker temporary pointer to this robot
        Move the Attacker until move function returns an enemy
        when the enemy found:
            set Target pointer to the enemy
            display the arena before fight
            inform about attacker and defender name, position etc.
            with user input, start the fight
            store the fight result in a variable
            if attacker won:
                delete victim, move attacker position to victim's cell
                announce fight's winner
            if victim won:
                delete attacker
                announce fight's winner
    
    check if current count of robots is greater than 1 or not
        if there is more than 1 robot:
            continue to check for unmoved robots and fight
        if only 1:
            announce the robot as winner


*/


void Arena::Play()
{
    Robot *Attacker = NULL;
    Robot *Target = NULL;
    Robot *LastSurvivor = NULL;
    int posx, posy;
    string input;
    int FightResult;

    while(RobotCount > 1)
    {

        // resetting every robots moved flag to not moved
        resetMove();

        for(int a = 0 ;((a < ARENA_SIZE) && (RobotCount > 1)); a++)
        {
            for(int b = 0 ;((b < ARENA_SIZE) && (RobotCount > 1)); b++)
            {
                if(arena[a][b] != NULL)
                {
                    if(arena[a][b]->moved == false)
                    {  
                        // Display the arena after robot moves
                        Display();

                        // Store the position of robot
                        posx = a; 
                        posy = b;

                        // set moved
                        arena[a][b]->moved = true;

                        // Set attacker pointer to this robot
                        Attacker = arena[a][b];

                        Target = NULL;

                        // While the robot didnt find any opponent, continue moving till find one
                        while(Target == NULL)
                        {
                            Target = Attacker->Move();
                        }

                        // Display the arena after robot moves
                        Display();

                        // Inform before fight about fightning robots
                        std::cout << "Attacker " << Attacker->name <<" has moved from " << posx << "," << posy << " to " << Attacker->x << "," << Attacker->y << endl;
                        std::cout << "A: " << Attacker->name << " | V: " << Target->name << endl;
                        std::cout << "A pos: " << Attacker->x << "," << Attacker->y << " | V pos: " << Target->x << "," << Target->y << endl;

                        // Get input to start the fight
                        std::cout << endl << "Press enter to start the war." << endl;
                        std::getline(cin, input);

                        // Do the fight and store the result
                        FightResult = Fight(Attacker, Target);


                        // If attacker won the fight
                        if(FightResult == ATTACKER_WON)
                        {
                            this->setAt(Attacker->x, Attacker->y, NULL);
                            this->setAt(Target->x, Target->y, Attacker);
                            Attacker->x = Target->x;
                            Attacker->y = Target->y;
                            delete Target;
                            RobotCount--;
                            std::cout << "Attacker " << Attacker->getName() << " has won and taken his opponent place. " << endl << endl;
                            LastSurvivor = Target;
                        }

                        // If defender won the fight
                        else if(FightResult == VICTIM_WON)
                        {
                            this->setAt(Attacker->x, Attacker->y, NULL);
                            delete Attacker;
                            RobotCount--;
                            std::cout << "Defender " << Target->getName() << " has won. " << endl << endl;
                            LastSurvivor = Target;
                        }

                        // Announcing the winner
                        if(RobotCount < 2)
                            cout << LastSurvivor->getName() << " has won the game, congratz." << endl << endl;
                    }
                }
            }
        }
    }
}


void Arena::resetMove()
{
    for(int a = 0 ; a < ARENA_SIZE ; a++)
    {
        for(int b = 0 ; b < ARENA_SIZE ; b++)
        {
            if(arena[a][b] != NULL)
                arena[a][b]->moved = false;
        }
    }
}