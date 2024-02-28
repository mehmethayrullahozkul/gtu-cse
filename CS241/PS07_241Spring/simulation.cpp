#include "simulation.h"

World::World() {
    for(int a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(int b = 0 ; b < WORLD_SIZE ; b++)
        {
            game_grid[a][b] = NULL;
        }
    }
}


World::~World() {
    for(int a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(int b = 0 ; b < WORLD_SIZE ; b++)
        {
            if(game_grid[a][b] != NULL) delete game_grid[a][b];
        }
    }
}

Organism* World::getAt(int x, int y) {
    if((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        return game_grid[x][y];
    return NULL;
}

void World::setAt(int x, int y, Organism *org) {
    if((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        game_grid[x][y] = org;
}

void World::display() {
    cout << endl;
    for(int a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(int b = 0 ; b < WORLD_SIZE ; b++)
        {
            if(game_grid[a][b] == NULL)
            {
                cout << ".";
            }
            else if(game_grid[a][b]->getType() == ANT)
            {
                cout << "o";
            }
            else {cout << "X";}
        }
        cout << endl;
    }
}

void World::simulateOneStep() {

    // INIT MOVE
    int a, b;
    for(a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(b = 0 ; b < WORLD_SIZE ; b++)
        {
            if(game_grid[a][b] != NULL) game_grid[a][b]->moved = false;
        }
    }

    // DOODLEBUG MOVE
    for(a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(b = 0 ; b < WORLD_SIZE ; b++)
        {
            if(game_grid[a][b] != NULL && game_grid[a][b]->getType() == DOODLEBUG)
            {
                if(game_grid[a][b]->moved == false)
                {
                    game_grid[a][b]->moved = true;
                    game_grid[a][b]->Move();
                }
            }
        }
    }

    // ANT MOVE
    for(a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(b = 0 ; b < WORLD_SIZE ; b++)
        {
           if(game_grid[a][b] != NULL && game_grid[a][b]->getType() == ANT)
            {
                if(game_grid[a][b]->moved == false)
                {
                    game_grid[a][b]->moved = true;
                    game_grid[a][b]->Move();
                }
            } 
        }
    }

    // CHECK DOODLEBUG STARVE
    for(a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(b = 0 ; b < WORLD_SIZE ; b++)
        {
           if(game_grid[a][b] != NULL && game_grid[a][b]->getType() == DOODLEBUG)
            {
                if(game_grid[a][b]->Starve() == true)
                {
                    delete game_grid[a][b];
                    game_grid[a][b] = NULL;
                }
            } 
        }
    }

    // BREED THEM ALL
    for(a = 0 ; a < WORLD_SIZE ; a++)
    {
        for(b = 0 ; b < WORLD_SIZE ; b++)
        {
           if(game_grid[a][b] != NULL && game_grid[a][b]->moved == true)
            {
                game_grid[a][b]->Breed();
            } 
        }
    }
}

Organism::Organism() {
    world = NULL;
    moved = false;
    breedTicks = 0;
    x = 0;
    y = 0;
}

Organism::Organism(World *w, int x, int y) {
    this->world = w;
    moved = false;
    breedTicks = 0;
    this->x = x;
    this->y = y;
    w->setAt(x, y, this);
}

int Ant::getType() {
    return ANT;
}

int Doodlebug::getType() {
    return DOODLEBUG;
}

void Ant::Breed() {

    breedTicks++;
    if(breedTicks == ANT_BREED)
    {
        breedTicks = 0;

        if((y > 0) && world->getAt(x, y-1) == NULL)
        {
            Ant *newAnt = new Ant(world, x, y-1);
        }
        else if((y < WORLD_SIZE-1) && world->getAt(x, y+1) == NULL)
        {
            Ant *newAnt = new Ant(world, x, y+1);
        }
        else if((x > 0) && world->getAt(x-1, y) == NULL)
        {
            Ant *newAnt = new Ant(world, x-1, y);
        }
        else if((x < WORLD_SIZE-1) && world->getAt(x+1, y) == NULL)
        {
            Ant *newAnt = new Ant(world, x, y+1);
        }
    }
}

void Ant::Move() {

    int direction = rand() % 4;

    if(direction == 0)
    {
        if(y > 0 && world->getAt(x, y-1) == NULL)
        {
            world->setAt(x, y-1, world->getAt(x, y));
            world->setAt(x, y, NULL);
            y--;
        }
    }
    else if (direction == 1)
    {
        if((y < WORLD_SIZE-1) && world->getAt(x, y+1) == NULL)
        {
            world->setAt(x, y+1, world->getAt(x, y));
            world->setAt(x, y, NULL);
            y++;
        }
    }
    else if(direction == 2)
    {
        if((x > 0) && world->getAt(x-1, y) == NULL)
        {
            world->setAt(x-1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x--;
        }
    }
    else if(direction == 3)
    {
        if((x < WORLD_SIZE-1) && world->getAt(x+1, y) == NULL)
        {
            world->setAt(x+1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x++;
        }
    }
}

Doodlebug::Doodlebug() : Organism() {
    starveTicks = 0;
}

Doodlebug::Doodlebug(World *w, int x, int  y) : Organism(w, x, y) {
    starveTicks = 0;
}

Ant::Ant(World *w, int x, int y) : Organism(w, x, y) {}

void Doodlebug::Breed() {
    breedTicks++;
    if(breedTicks == DOODLE_BREED)
    {
        breedTicks = 0;

        if(y > 0 && world->getAt(x, y-1) == NULL)
        {
            Doodlebug *newBug = new Doodlebug(world, x, y-1);
        }
        else if((y < WORLD_SIZE-1) && world->getAt(x, y+1) == NULL)
        {
            Doodlebug *newBug = new Doodlebug(world, x, y+1);
        }
        else if((x > 0) && world->getAt(x-1, y) == NULL)
        {
            Doodlebug *newBug = new Doodlebug(world, x-1, y);
        }
        else if((x < WORLD_SIZE-1) && world->getAt(x+1, y) == NULL)
        {
            Doodlebug *newBug = new Doodlebug(world, x+1, y);
        }
    }
}

void Doodlebug::Move() {
    
    if((y > 0 ) && (world->getAt(x, y-1) != NULL) && (world->getAt(x, y-1)->getType() == ANT))
    {
        delete (world->game_grid[x][y-1]);
        world->game_grid[x][y-1] = this;
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y--;
        return;
    }
    else if((y < WORLD_SIZE-1) && (world->getAt(x, y+1) != NULL) && (world->getAt(x, y+1)->getType() == ANT))
    {
        delete (world->game_grid[x][y+1]);
        world->game_grid[x][y+1] = this;
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y--;
        return;
    }
    else if((x > 0 ) && (world->getAt(x-1, y) != NULL) && (world->getAt(x-1, y)->getType() == ANT))
    {
        delete (world->game_grid[x-1][y]);
        world->game_grid[x-1][y] = this;
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y--;
        return;
    }
    else if((x < WORLD_SIZE-1) && (world->getAt(x+1, y) != NULL) && (world->getAt(x+1, y)->getType() == ANT))
    {
        delete (world->game_grid[x+1][y]);
        world->game_grid[x+1][y] = this;
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y--;
        return;
    }

    int direction = rand() % 4;

    if(direction == 0)
    {
        if(y > 0 && world->getAt(x, y-1) == NULL)
        {
            world->setAt(x, y-1, world->getAt(x, y));
            world->setAt(x, y, NULL);
            y--;
        }
    }
    else if (direction == 1)
    {
        if((y < WORLD_SIZE-1) && world->getAt(x, y+1) == NULL)
        {
            world->setAt(x, y+1, world->getAt(x, y));
            world->setAt(x, y, NULL);
            y++;
        }
    }
    else if(direction == 2)
    {
        if((x > 0) && world->getAt(x-1, y) == NULL)
        {
            world->setAt(x-1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x--;
        }
    }
    else if(direction == 3)
    {
        if((x < WORLD_SIZE-1) && world->getAt(x+1, y) == NULL)
        {
            world->setAt(x+1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x++;
        }
    }

}

bool Doodlebug::Starve() {
    if(starveTicks > DOODLE_STARVE)
    {
        return true;
    }
    else
        return false;
}


Organism::~Organism() {}