#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

#ifndef _h_exception
#define _h_exception


namespace catalog
{

    enum EntryExceptions {INVALID_STRING = 101, MISSING_FIELDS, MISSING_CAPSULATOR, INVALID_DATA, ACCES_ABORT, INVALID_MODE};

    enum CatalogExceptions {INVALD_TYPE = 201, CANT_OPEN_FILE};


    class Exception
    {
        public:

            Exception();
            Exception(string Ex, int Error_Code);

            string getMessage();
            int getError();

        private:

            string ex_msg;
            int ex_code;
    };


    Exception::Exception()
    {
        ex_msg = "404 | Unknown Error!";
        ex_code = EntryExceptions::MISSING_CAPSULATOR;
    } 

    Exception::Exception(string Ex, int Error_Code)
    {
        ex_msg = Ex + "\n";
        ex_code =  Error_Code;
    }

    string Exception::getMessage()
    {
        return ex_msg;
    }

    int Exception::getError()
    {
        return ex_code;
    }
}

#endif