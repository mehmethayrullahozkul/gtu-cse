#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;



// POWER FUNCTION TO FURTHER USE IN EVALUATE FUNCTION

double power(double a, int b);

double power(double a, int b) {
    double sum = a;
    for(int i = 0 ; i < b ; i++)
    {
        sum *= a; 
    }
    return sum;
}

class Polynomial {
    private:
        int degree;
        double *polynom;
        
    public:

        // EMPTY CONSTRUCTOR
        Polynomial() {
            degree = 0;
            polynom = NULL;
        }

        // CONSTRUCTOR WITH INPUTS
        Polynomial(double *arr, int size) {
            degree = size;
            polynom = new double[degree];
            for(int i = 0 ; i < size ; i++)
            {
                polynom[i] = arr[i];
            }
        }

        // COPY CONSTRUCTOR
        Polynomial(Polynomial &P) {
            degree = P.degree;
            polynom = new double[degree];
            for(int i = 0 ; i < degree ; i++) 
            {
                polynom[i] = P.polynom[i];
            }
        }

        // ASSIGN OVERLOAD
        void operator=(const Polynomial& P) {
            delete[] polynom;
            degree = P.degree;
            polynom = new double[degree];
            for(int i = 0 ; i < degree ; i++) 
            {
                polynom[i] = P.polynom[i];
            } 
        }

        // BRACKET OVERLOAD
        double& operator[] (int s)  {
            if(s > degree)
            {
                cout<<"Cant acces this, invalid element."<<endl;
                return polynom[0];
            }
            else 
            {
                return polynom[s];
            }

        }

        // FRIEND FUNCTIONS
        friend Polynomial operator+(const Polynomial &a, const Polynomial &b);
        friend Polynomial operator-(const Polynomial &a, const Polynomial &b);
        friend Polynomial operator*(const Polynomial &a, const Polynomial &b);
        friend double evaulate(const Polynomial &a, double d);



        // DESTRUCTURE
        ~Polynomial() {
            delete[] polynom;
            polynom = NULL;
        }   
};



double evaulate(const Polynomial &a, double d) {
    double total = 0;
    for(int i = 0 ; i < a.degree ; i++ )
    {   
        total += (power(d, i) * a.polynom[i]);
    }
    return total;
}



Polynomial operator+(const Polynomial &a, const Polynomial &b) {
    int maxSize;
    if(a.degree >= b.degree) {maxSize = a.degree;}
    else {maxSize = b.degree;}
    double *totalPoly = new double[maxSize];
    for(int i = 0 ; i < maxSize ; i ++)
    {
        // CHECKS IF THEY ARE NOT IN THE SAME DEGREE
        if(a.degree < i || b.degree < i)
        {
            // IF B'S DEGREE BIGGER USE B AS TOTAL
            if(a.degree < i)
            {
                totalPoly[i] = b.polynom[i];
            }
            // IF A'S DEGREE BIGGER USE A AS TOTAL
            else 
            {
                totalPoly[i] = a.polynom[i];
            }
        }
        else 
        {
            totalPoly[i] = a.polynom[i] + b.polynom[i];
        }
    }
    Polynomial P(totalPoly, maxSize);
    return P;
}

Polynomial operator-(const Polynomial &a, const Polynomial &b) {
    int maxSize;
    if(a.degree >= b.degree) {maxSize = a.degree;}
    else {maxSize = b.degree;}
    double *totalPoly = new double[maxSize];
    for(int i = 0 ; i < maxSize ; i ++)
    {
        // CHECKS IF THEY ARE NOT IN THE SAME DEGREE
        if(a.degree < i || b.degree < i)
        {
            // IF B'S DEGREE BIGGER USE B AS TOTAL
            if(a.degree < i)
            {
                totalPoly[i] = -(b.polynom[i]);
            }
            // IF A'S DEGREE BIGGER USE A AS TOTAL
            else 
            {
                totalPoly[i] = a.polynom[i];
            }
        }
        else 
        {
            totalPoly[i] = a.polynom[i] - b.polynom[i];
        }
    }
    Polynomial P(totalPoly, maxSize);
    return P;
}

Polynomial operator*(const Polynomial &a, const Polynomial &b) {
    int maxSize = (a.degree) + (b.degree) + 1;
    double *total = new double[maxSize];
    for(int i = 0 ; i < maxSize ; i++)
    {
        total = 0;
    }
    for(int x = 0 ; x < a.degree ; x++)
    {
        for(int y = 0 ; y < b.degree ; y++)
        {
            total[x + y] += a.polynom[x] * b.polynom[y];
        }
    }
    Polynomial P(total, maxSize);
    return P;
}



int main () {
    Polynomial empty;
    double one[] = {1};
    Polynomial One(one, 1);
    double quad[] = {8, 1, 5};
    double cubic[] = {6, 4, 2, 3};
    Polynomial q(quad, 3);
    Polynomial c(cubic, 4);
    Polynomial p = q;
    Polynomial r;
    r = q;
    r = c;
    cout<<"Polynmoinal q : "<<endl;
    for(int i = 0 ; i < 3 ; i++) 
    {
        cout<<"term with degree : "<<i<<" has coefficent  "<<q[i]<<endl;
    }
    cout<<endl<<endl;
    cout<<"Polynmoinal c : "<<endl;
    for(int i = 0 ; i < 4 ; i++) 
    {
        cout<<"term with degree : "<<i<<" has coefficent  "<<c[i]<<endl;
    }

    cout<<endl;
    cout<<"Value of q(2) is : "<<evaulate(q, 2)<<endl;
    cout<<"Value of p(2) is : "<<evaulate(p, 2)<<endl;
    cout<<"Value of r(2) is : "<<evaulate(r, 2)<<endl;
    cout<<"Value of c(2) is : "<<evaulate(c, 2)<<endl;

    r = q + c;
    cout<<"Value of (q + c)(2) is : "<<evaulate(r, 2)<<endl;
    r = q - c;
    cout<<"Value of (q - c)(2) is : "<<evaulate(r, 2)<<endl;
    r = q * c;
    cout<<"Value of (q * c)(2) is : "<<evaulate(r, 2)<<endl;



}