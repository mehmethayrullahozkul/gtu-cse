#include "Genre.h"

using std::string;

#ifndef _h_movie
#define _h_movie

namespace catalog
{
    class Movie : public Genre 
    {
        public:

            string Fields[5] = {"title",
                               "director",
                               "year",
                               "genre",
                               "starring"};

            int Type();

            Movie();
            Movie(string& entry);

            void Show();

            int GenreSize();
            int StarringSize();

            std::list<string>& Genres();
            std::list<string>& Starring();

        private:

           string director;
           std::list<string> genre;
           int genre_size;
           std::list<string> starring;
           int starring_size;

    };


    int Movie::Type() 
    {
        return TYPE_MOVIE;
    }


    Movie::Movie(string& entry) : Genre()
    {
        this->field_count = 5;
        this->genre_typename = "movie";
        Entry Obj;
        Obj.Parse(entry, this->field_count, '\"', CAPSULED);
        this->title = Obj[0];
        this->director = Obj[1];
        this->year = Obj[2];
        this->setMultiField(Obj[3], this->genre);
        this->setMultiField(Obj[4], this->starring);
        this->data = entry;
    }

    Movie::Movie() : Genre () 
    {
        this->field_count = 4;
        this->genre_typename = "movie";
    }

    //void Movie::Show()
    //{
    //    cout << "Title:   " << this->title << endl;
    //    cout << "Authors: ";
    //    for(std::list<string>::iterator it = authors.begin() ; it != authors.end() ; it++)
    //        cout << *it << "-";
    //    cout << endl;
    //    cout << "Title:   " << this->year << endl;
    //    cout << "Tags:    ";
    //    for(std::list<string>::iterator it = tags.begin() ; it != tags.end() ; it++)
    //        cout << *it << "-";
    //    cout << endl;
    //}

}

#endif
