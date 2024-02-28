#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Exception.h"


#ifndef _h_Entry
#define _h_Entry

using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::vector;


namespace catalog
{
    enum ParseOptions {LEFT_RES = 1, RIGHT_RES = 2, BOTH_RES = 3};
    enum DelModes {CAPSULED = 1, BETWEEN};

    bool Trim(string &s, const char trim_char, const int OPTION);

    class Entry 
    {
        friend bool Trim(string &s, const char trim_char, const int OPTION);

        public:

            Entry();
            ~Entry();


            bool isValid();
            int Size();

            bool Parse(string Object,
                      const int fieldCount = 0,
                      const char Delimeter = '\0',
                      const int DelimeterMode = CAPSULED,
                      const char Capsulator = '\0',
                      const char Removals = '\0');


            string& operator[](int At);



        private:

            string entry;
            int field_count;
            bool valid;
            vector<string> data;


    };

    Entry::Entry()
    {
        this->entry = "";
        //this->data.clear();
        this->field_count = 0;
        this->valid = false;
    }




    bool Entry::Parse(string Object, const int fieldCount, const char Delimeter, const int DelimeterMode, const char Capsulator, const char Removal)
    {

        bool isDelimited   =  (Delimeter == '\0') ? false : true;
        bool isCapsulated  =  (Capsulator == '\0') ? false : true;
        bool doFilter      =  (Removal == '\0') ? false : true;

        // check string size
        if(Object.size() > 200 || Object.size() <= 0)
            throw(Exception("Exception: given string is empty or too long", EntryExceptions::INVALID_STRING));

        // remove capsulator
        if(isCapsulated)
        {    
            if(!Trim(Object, Capsulator, BOTH_RES))
                throw(Exception("Exception: given string doesnt have capsulation as expected", EntryExceptions::MISSING_CAPSULATOR));
        }

        // check field count
        if(isDelimited)
        {
            if(DelimeterMode == CAPSULED)
            {
                if(std::count(Object.begin(), Object.end(), Delimeter) != (fieldCount * 2))
                    throw(Exception("Exception: given string has missing / excessing fields", EntryExceptions::MISSING_FIELDS));
            }
            else if(DelimeterMode != BETWEEN)
            {
                throw(Exception("Exception: invalid parsing mode", EntryExceptions::INVALID_MODE));
            }
        }

        // remove all appaerences of a character
        if(doFilter)
        {
            Object.erase(std::remove(Object.begin(), Object.end(), Removal), Object.end());
        }

        std::istringstream ObjectStream(Object);
        string token;

        data.clear();

        int i = 0;
        int count = 0;
        if((isDelimited) && (DelimeterMode == CAPSULED))
        {
            while(getline(ObjectStream, token, Delimeter))
            {
                if(i == 1)
                {
                    data.push_back(token);
                    count++;
                }
                else if (i >= 2)
                    i = 0;
                i++;
            }
        }
        else if((isDelimited) && (DelimeterMode == BETWEEN))
        {
            while(getline(ObjectStream, token, Delimeter))
            {
                data.push_back(token);
                count++;
            }
        }
        else
        {
            while(ObjectStream >> token)
            {
                data.push_back(token);
                count++;
            }
        }

        this->field_count = count;
        this->entry = Object;
        this->valid = true;
        return true;
    }



    bool Trim(string &s, const char t_char, const int OPTION)
    {
        switch (OPTION)
        {
            case LEFT_RES:
            {
                size_t loc = s.find(t_char);
                if(loc == string::npos) return false;
                s.erase(loc, 1);
                break;
            }
            case RIGHT_RES:
            {
                size_t loc = s.find_last_of(t_char);
                if(loc == string::npos) return false;
                s.erase(loc, 1);
                break;
            }
            case BOTH_RES:
            {
                size_t loc_left = s.find(t_char);
                size_t loc_right = s.find_last_of(t_char);
                if((loc_left == string::npos) ||
                    (loc_right == string::npos) ||
                    (loc_left == loc_right))
                     return false;
                s.erase(loc_left, 1);
                s.erase(loc_right - 1, 1);
                break;
            }
        }
        return true;
    }


    string& Entry::operator[](int At)
    {
        if((At < 0) || (At >= this->data.size()))
            throw(Exception("Exception: seg fault, access to undefined", EntryExceptions::ACCES_ABORT));

        return this->data[At];
    }

    bool Entry::isValid()
    {
        return this->valid;
    }

    int Entry::Size()
    {
        return this->field_count;
    }


    Entry::~Entry() {}
}


#endif







