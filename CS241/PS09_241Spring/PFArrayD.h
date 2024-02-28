// HEADER START FOR PFARRAYD.H

#ifndef PF_ARR
#define PF_ARR

#include <string>

using std::string;

class Exception {

};

class OutOfRange : public Exception 
{
    public:
        OutOfRange(string thisMessage, int thisIndex);
        string getMessage() const;
        int getIndex() const;
    private:
        string message;
        int index;
};

class PFArrayD 
{
    public:
        PFArrayD();
        PFArrayD(int capacityValue);
        PFArrayD(const PFArrayD& pfaObject);
        void addElement(double element);

        bool full() const {return (capacity == used);}

        int getCapacity() const {return capacity;}
        int getNumberUsed() const {return used;}

        void emptyArray() { used = 0;}

        double& operator[](int index);

        PFArrayD& operator=(const PFArrayD& rightSide);
        ~PFArrayD();


    private:
        double *a;
        int capacity;
        int used;
};

#endif
