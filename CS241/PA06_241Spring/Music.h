#include "Genre.h"

using std::string;

#ifndef _h_music
#define _h_music

namespace catalog
{
    class Music : public Genre 
    {
        public:

            string Fields[4] = {"title",
                               "artists",
                               "year",
                               "genre"};

            int Type();

            Music();
            Music(string& entry);

            void Show();

            int ArtistSize();
            int GenreSize();

            std::list<string>& Artists();
            std::list<string>& Genres();

        private:

           std::list<string> artists;
           int artist_size;
           std::list<string> genres;
           int genre_size;

    };


    int Music::Type() 
    {
        return TYPE_MUSIC;
    }


    Music::Music(string& entry) : Genre()
    {
        this->field_count = 4;
        this->genre_typename = "music";
        Entry Obj;
        Obj.Parse(entry, this->field_count, '\"', CAPSULED);
        this->title = Obj[0];
        this->setMultiField(Obj[1], this->artists);
        this->year = Obj[2];
        this->setMultiField(Obj[3], this->genres);
        this->data = entry;
    }

    Music::Music() : Genre () 
    {
        this->field_count = 4;
        this->genre_typename = "music";
    }

    //void Music::Show()
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
