#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>


using namespace std;

#ifndef sim_ulation
#define sim_ulation

const int WORLD_SIZE = 20;
const int INITIAL_ANTS = 100;
const int INITIAL_BUGS = 5;
const int DOODLEBUG = 1;
const int ANT = 2;
const int ANT_BREED = 3;
const int DOODLE_BREED = 8;
const int DOODLE_STARVE = 3;


class Organism;
class Doodlebug;
class Ant;

class World {
    friend class Organism;
    friend class Doodlebug;
    friend class Ant;
    public:
        World();
        ~World();
        Organism * getAt(int x, int y);
        void setAt(int x, int y, Organism* org);
        void display();
        void simulateOneStep();
    private:
        Organism * game_grid[WORLD_SIZE][WORLD_SIZE];
};




class Organism {

    friend class World;

    public:
        Organism();
        ~Organism();
        Organism(World *w, int x, int y);
        virtual void Move() = 0;
        virtual void Breed() = 0;
        virtual int getType() = 0;
        virtual bool Starve() = 0;
    protected:
        int x, y;
        bool moved;
        int breedTicks;
        World *world;
};


class Ant : public Organism {
    
    friend class World;
    public:
        Ant();
        Ant(World *w, int x, int y);
        void Breed();
        void Move();
        int getType();
        bool Starve() {return false;}
};

class Doodlebug : public Organism {

    friend class World;
    public:
        Doodlebug();
        Doodlebug(World *w, int x, int y);
        void Breed();
        void Move();
        int getType();
        bool Starve();
    private:
        int starveTicks;
};
#endif