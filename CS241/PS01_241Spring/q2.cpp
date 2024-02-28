#include <iostream>
#include<cstdlib>
using namespace std;


int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);

// Getting dice roll between 1 - 6
int getRoll();



int main(){
    int playerScore = 0;
    int computerScore = 0;
    int comingPoints;

    srand((unsigned) time(NULL));
    cout<<endl<<endl<<endl<<"THE GAME OF PIG, GOAL IS TO GET 100 POINTS BY ROLLING."<<endl;
    cout<<"GOOD LUCK!!!"<<endl;
    cout<<endl<<endl<<"--- PLAYER STARTS ---"<<endl<<endl;

    while(playerScore <= 100 && computerScore <= 100)
    {

        // PLAYERS TURN CHECKING IF PLAYER WON
        comingPoints = humanTurn(playerScore);
        playerScore += comingPoints;
        if(playerScore >= 100)
        {
            cout<<"Player has won by getting "<<playerScore<<" points, well done."<<endl;
            break;
        }

        // If player wants to quit, the function humanTurn() would return (-1) so checking the quit.
        if(comingPoints == -1)
        {
            cout<<endl<<"quitting game."<<endl;
            return 0;
        }

        // PLAYERS TURN CHECKING IF COMPUTER WON
        comingPoints = computerTurn(computerScore);
        computerScore += comingPoints;
        if(computerScore >= 100)
        {
            cout<<"Computer has won by getting "<<computerScore<<" points, bad luck."<<endl;
            break;
        }
    }
    cout<<endl<<endl<<"Press enter to end program..."<<endl;
    cin.ignore();
    cin.ignore();
}


int getRoll() {
    return ((rand() % 6) + 1);
}

int humanTurn(int humanTotalScore) {
    char select;
    int currentpoints = 0;
    int ongoing = 1;
    int checknumber;

    cout<<"Players current total score is : "<< humanTotalScore<<endl;

    // While game's ongoing repeat the function for player and take input.
    while(ongoing == 1)
    {
        cout<<"Player has "<<currentpoints<<" points on hold, wanna pass this round or roll?"<<endl;
        cout<<"Enter (q) to quit, (r) to roll again or (h) to hold and add your points to current total score."<<endl;
        cin>>select;

        // If input is not valid, try again.
        if(select != 'r' && select != 'h' && select != 'q')
        {
            cout<<"Undefined input! Please try again."<<endl;
            continue;
        }


        // Getting rolls for player and adds up to the current turns points.
        else if(select == 'r')
        {
            checknumber = getRoll();
            currentpoints += checknumber;
            cout<<"Player roll : "<<checknumber<<endl;
            if(checknumber == 1)
            {
                currentpoints = 0;
                ongoing = 0;
                cout<<"Player has rolled 1 and lost all his hold points changing turns."<<endl<<endl;
            }
            
        }

        // Returns the current turns point of player.
        else if(select == 'h')
        {
            cout<<"Total of "<<currentpoints<<" has returned, computers turn."<<endl<<endl;
            ongoing = 0;
        }

        // Quits the game.
        else if (select == 'q')
        {
            ongoing = 0;
            return -1;
        }
    }
    return currentpoints;
}


int computerTurn(int computerTotalScore) {
    int currentpoints = 0;
    int ongoing = 1;
    int checknumber;
    cout<<"Computers current total score is : "<< computerTotalScore<<endl;

    // Forcing computer to roll till it gets more than 20 points currently or 1.
    do {
            if( currentpoints < 20)
            {
                checknumber = getRoll();
                currentpoints += checknumber;
                cout<<"Computer roll : "<<checknumber<<endl;
                if(checknumber == 1)
                {
                    currentpoints = 0;
                    ongoing = 0;
                    cout<<"Computer has rolled 1 and lost all his hold points changing turns."<<endl<<endl;
                }

            }
            else if(currentpoints >= 20)
            {
                cout<<"Total of "<<currentpoints<<" has returned, players turn."<<endl<<endl;
                ongoing = 0;
            }
        }while(ongoing == 1);
    return currentpoints;
}




