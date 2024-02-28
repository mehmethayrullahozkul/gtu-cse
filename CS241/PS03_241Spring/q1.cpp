#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;


int NUMBER_OF_GAMES = 10000;

class HotDogStand{
    private:

        // ID FOR HOTDOG STANDS
        long unsigned int ID;

        // VARIABLE FOR TRACKING HOW MANY SOLD TODAY
        int how_many_sold;

        // TOTAL HOT DOGGIES SOLD TODAY
        static unsigned int totalHotDogsSold;
    public:

        // CONSTRUCTOR WITH ID AND HOW MANY SOLD TODAY
        HotDogStand(int id, int sold) {
            ID = id;
            how_many_sold = sold;
            totalHotDogsSold += sold;
        }

        // JUSTSOLD METHOD AS ASKED
        void JustSold() {
            how_many_sold++;
            totalHotDogsSold++;
        }

        // RETURNS HOW MANY HOT DOGS SOLD FOR THIS STAND
        int getSold() {
            return how_many_sold;
        }

        // GETINFO METHOD FOR EASY TRACKING
        void getInfo() {
            cout<<" "<<endl<<"ID : "<<ID<<endl<<"Today's sold : "<<how_many_sold<<endl<<endl;
        }

        // STATIC VARIABLE TO KEEP TOTAL AMOUNT OF SOLD
        static int hotDoggiesTotal();
};


int HotDogStand::hotDoggiesTotal(){
    return totalHotDogsSold;
}

unsigned int HotDogStand::totalHotDogsSold = 0;

int main(){


    // WE HAVE TOTAL OF 4 HOT DOGS STAND
    HotDogStand Alice(31252513, 1);
    HotDogStand Marley(15683523, 2);
    HotDogStand Lousaine(8922123, 0);
    HotDogStand Harvey(2141128, 5);


    // PRINTING INITIALIZED VALUES
    std::cout<<endl<<"--- HOT DOG STAND ---"<<endl<<endl;
    std::cout<<" "<<"Hotdogger Alice's stand info is : ";
    Alice.getInfo();
    cout<<" "<<"Hotdogger Marley's stand info is : ";
    Marley.getInfo();
    cout<<" "<<"Hotdogger Lousaine's stand info is : ";
    Lousaine.getInfo();
    cout<<" "<<"Hotdogger Harvey's stand info is : ";
    Harvey.getInfo();

    cout<<"Total hotdoggies sold today : "<<HotDogStand::hotDoggiesTotal()<<endl<<endl;



    // SELLING AND PRINTING PART

    Alice.JustSold();
    cout<<"Alice just sold one hotdog, current Alice's sold amount : "<<Alice.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Alice.JustSold();
    cout<<"Alice just sold one hotdog, current Alice's sold amount : "<<Alice.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Marley.JustSold();
    cout<<"Marley just sold one hotdog, current Marley's sold amount : "<<Marley.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Marley.JustSold();
    cout<<"Marley just sold one hotdog, current Marley's sold amount : "<<Marley.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Marley.JustSold();
    cout<<"Marley just sold one hotdog, current Marley's sold amount : "<<Marley.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Lousaine.JustSold();
    cout<<"Lousaine just sold one hotdog, current Lousaine's sold amount : "<<Lousaine.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;
    Harvey.JustSold();
    cout<<"Harvey just sold one hotdog, current Harvey's sold amount : "<<Harvey.getSold()<<", current total sold is : "<<HotDogStand::hotDoggiesTotal()<<endl;


    std::cout<<endl<<" "<<endl<<"PRESS ENTER TO EXIT THE PROGRAM."<<endl;
    cin.ignore();

}