#include "Arena.h"
#include "Robot.h"
#include "Bulldozer.h"
#include "Roomba.h"
#include "Humanic.h"
#include "Optimusprime.h"
#include "Robocop.h"


int main()
{
    srand(time(NULL));
    Arena our_arena;
    our_arena.Initialize();
    our_arena.Play();
}