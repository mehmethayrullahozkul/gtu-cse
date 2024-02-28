#include <iostream>
#include <iostream>

using namespace std;

template <class T, class S> class Pair {
private:
    T first_item;
    S second_item;

public:
    Pair() {first_item = 0 ; second_item = 0;}
    Pair(T f, S s) {first_item = f ; second_item = s;}
    void setFirst(T t) {first_item = t;}
    void setSecond(S s) {second_item = s;}
    T getFirst() {return first_item;}
    S getSecond() {return second_item;}

};

int main () {

    Pair<char, char> p('A', 'B');

    cout << "First is : " << p.getFirst() << endl;

    p.setFirst('Z');

    cout << "First changed to : " << p.getFirst() << endl;

    cout << "The pair is : " << p.getFirst() << " - " << p.getSecond() << endl;

    Pair<int, string> p2(34, "Hallelujah");

    cout << "Second pair is : " << p2.getFirst() << " - " << p2.getSecond();
}