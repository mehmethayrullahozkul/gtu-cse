#include "simulation.cpp"
#include "simulation.h"

int main() {

    string input;
    srand(time(NULL));
    World nw;

    int ant_count = 0;

    while(ant_count < INITIAL_ANTS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if(nw.getAt(x, y) == NULL)
        {
            ant_count++;
            Ant *newAnt = new Ant(&nw, x, y);
        }
    }

    int doodle_count = 0;

    while(doodle_count < INITIAL_BUGS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if(nw.getAt(x, y) == NULL)
        {
            doodle_count++;
            Doodlebug *newDoodle = new Doodlebug(&nw, x, y);
        }
    }

    while(true)
    {
        nw.display();
        nw.simulateOneStep();
        cout << endl << "Press enter for next step" << endl;
        getline(cin, input);
    }
    return 0;
}