#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Entry.h"
#include "Exception.h"

using std::string;
using std::cin;
using std::cout;
using std::list;

#ifndef _h_genre
#define _h_genre

namespace catalog
{
    const int TYPE_NULL = 0;
    const int TYPE_BOOK = -1;
    const int TYPE_MUSIC = -2;
    const int TYPE_MOVIE = -3;


    const string MOVIE = "movie";
    const string BOOK  = "book";
    const string MUSIC = "music";



    class Genre
    {
        template<class Type> friend class Catalog;

        public:

            Genre(); 

            virtual int Type() = 0;
            int FieldCount() const;

            string& Data();
            string Title() const;
            string Year() const;
            string Typename() const;
            bool setMultiField(string &s, list<string>& data_to_fill);

            void setTitle(string s);
            void setYear(string s);


        protected:

            string data;
            string title;
            string year;
            int field_count;
            string genre_typename;

    };

    Genre::Genre()
    {
        this->title = "";
        this->year = "";
        this->field_count = 0;
    }

    int Genre::FieldCount() const
    {
        return this->field_count;
    }

    string Genre::Typename() const 
    {
        return this->genre_typename;
    }

    bool Genre::setMultiField(string &s, list<string>& data_to_fill)
    {
        Entry Obj;
        data_to_fill.clear();
        Obj.Parse(s, 0, ',', BETWEEN);
        for(int i = 0 ; i < Obj.Size() ; i++)
        {   
            Trim(Obj[i], ' ', LEFT_RES);
            data_to_fill.push_back(Obj[i]);
        }
        return true;
    }

    string& Genre::Data()
    {
        return this->data;
    }

    string Genre::Title() const
    {
        return this->title;
    }

    string Genre::Year() const
    {
        return this->year;
    }
}

#endif

