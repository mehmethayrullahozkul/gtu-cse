#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;


int NUMBER_OF_GAMES = 10000;

class DUELIST{
    private:
        int hit_chance;
        int is_alive = 1;
        int shot;
    public:
        void setChance(int s){
            hit_chance = s;
        }
        void setAlive() {
            is_alive = 1;
        }
        void setDead() {
            is_alive = 0;
        }
        int isAlive() {
            return is_alive;
        }
        int hitOrNot() {

            // SELECTS A RANDOM NUMBER BETWEEN 1 - 6 AND RETURNS IF SHOOTER COULD SHOT OR NOT.
            shot = (rand() % 6 + 1);
            if(shot > hit_chance) {
                return 0;
            }
            else {
                return 1;
            }

        }
};

int main(){

    srand((unsigned) time(NULL));
    DUELIST Aaron, Bob, Charlie;


    // CHANGE ALGORITH BASED ON 6 INSTEAD OF 100, 6 REFERS TO %100, AND 2 -> %33, 3 -> %50 AND SO FORTH.
    Aaron.setChance(2);
    Bob.setChance(3);
    Charlie.setChance(6);

    int AARON_WON = 0;
    int BOB_WON = 0;
    int CHARLIE_WON = 0;
    int FIRST_ROUND = 1;
    
    std::cout<<" "<<endl<<" "<<endl;

    for(int a = 0 ; a < NUMBER_OF_GAMES ; a++)
    {
        int number_of_deaths = 0;
        Aaron.setAlive();
        Bob.setAlive();
        Charlie.setAlive();

        do {

            // AARON'S TURN

            if(Aaron.isAlive()) 
            {
                if(Charlie.isAlive())
                {
                    if(Aaron.hitOrNot())
                    {
                        if(FIRST_ROUND) {std::cout<<"Aaron tried to shoot Charlie and killed him."<<endl;}
                        Charlie.setDead();
                        number_of_deaths++;
                    }
                    else {if(FIRST_ROUND) {std::cout<<"Aaron tried to shoot Charlie but couldn't kill him."<<endl;}}
                }
                else if (Bob.isAlive()) 
                {
                   {
                        if(Aaron.hitOrNot())
                        {
                            if(FIRST_ROUND) {std::cout<<"Aaron tried to shoot Bob and killed him."<<endl;}
                            Bob.setDead();
                            number_of_deaths++;
                        }
                        else {if(FIRST_ROUND) {std::cout<<"Aaron tried to shoot Bob but couldn't kill him."<<endl;}}
                    }
                }
            }


            // BOB'S TURN 

            if(Bob.isAlive()) 
            {
                // IF CHARLIE IS ALIVE TRY TO SHOOT HIM
                if(Charlie.isAlive())
                {
                    // BOB TRIES TO SHOOT
                    if(Bob.hitOrNot())
                    {
                        if(FIRST_ROUND) {std::cout<<"Bob tried to shoot Charlie and killed him."<<endl;}
                        Charlie.setDead();
                        number_of_deaths++;
                    }
                    else {if(FIRST_ROUND) {std::cout<<"Bob tried to shoot Charlie but couldn't kill him."<<endl;}}
                }

                // IF AARON IS ALIVE TRY TO SHOOT HIM
                else if (Aaron.isAlive()) 
                {
                   {
                        // BOB TRIES TO SHOOT
                        if(Bob.hitOrNot())
                        {
                            if(FIRST_ROUND) {std::cout<<"Bob tried to shoot Aaron and killed him."<<endl;}
                            Aaron.setDead();
                            number_of_deaths++;
                        }
                        else {if(FIRST_ROUND) {std::cout<<"Bob tried to shoot Aaron but couldn't kill him."<<endl;}}
                    }
                }
            }

            // CHARLIE'S TURN

            if(Charlie.isAlive()) 
            {
                // IF BOB IS ALIVE TRY TO SHOOT HIM
                if(Bob.isAlive())
                {
                    if(Charlie.hitOrNot())
                    {
                        if(FIRST_ROUND) {std::cout<<"Charlie tried to shoot Bob and killed him."<<endl;}
                        Bob.setDead();
                        number_of_deaths++;
                    }
                }

                // IF AARON IS ALIVE TRY TO SHOOT HIM
                else if (Aaron.isAlive()) 
                {
                   {
                        if(Charlie.hitOrNot())
                        {
                            if(FIRST_ROUND) {std::cout<<"Charlie tried to shoot Aaron and killed him."<<endl;}
                            Aaron.setDead();
                            number_of_deaths++;
                        }
                    }
                }
            }


            // IF NUMBER OF DEATHS GREATER THAN 1 THEN SOMEONE MUST WON THE ROUND, END THE ROUND.
            if(number_of_deaths>1)
            {
                if(Aaron.isAlive())
                {
                    AARON_WON++;
                    if(FIRST_ROUND) {std::cout<<"AARON WON THE FIRST ROUND."<<endl<<endl;}
                }
                else if(Bob.isAlive())
                {
                    BOB_WON++;
                    if(FIRST_ROUND) {std::cout<<"BOB WON THE FIRST ROUND."<<endl<<endl;}
                }
                else if(Charlie.isAlive())
                {
                    CHARLIE_WON++;
                    if(FIRST_ROUND) {std::cout<<"CHARLIE WON THE FIRST ROUND."<<endl<<endl;}
                }
                FIRST_ROUND = 0;
            }


        } while(number_of_deaths < 2);
    }

    std::cout<<"AARON WON : "<<AARON_WON<<"/10000 TIMES."<<endl;
    std::cout<<"BOB WON : "<<BOB_WON<<"/10000 TIMES."<<endl;
    std::cout<<"CHARLIE WON : "<<CHARLIE_WON<<"/10000 TIMES."<<endl;

    std::cout<<endl<<" "<<endl<<"PRESS ENTER TO EXIT THE PROGRAM."<<endl;
    cin.ignore();

}