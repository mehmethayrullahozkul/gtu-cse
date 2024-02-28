#include "Genre.h"

using std::string;

#ifndef _h_book
#define _h_book

namespace catalog
{
    class Book : public Genre 
    {
        public:

            string Fields[4] = {"title",
                               "authors",
                               "year",
                               "tags"};

            int Type();

            Book();
            Book(string& entry);

            void Show();

            int AuthorSize();
            int TagSize();

            std::list<string>& Tags();
            std::list<string>& Authors();

        private:

           std::list<string> authors;
           int author_size;
           std::list<string> tags;
           int tag_size;


    };


    int Book::Type() 
    {
        return TYPE_BOOK;
    }


    Book::Book(string& entry) : Genre()
    {
        this->field_count = 4;
        this->genre_typename = "book";
        Entry Obj;
        Obj.Parse(entry, this->field_count, '\"', CAPSULED);
        this->title = Obj[0];
        this->setMultiField(Obj[1], this->authors);
        this->year = Obj[2];
        this->setMultiField(Obj[3], this->tags);
        this->data = entry;
    }

    Book::Book() : Genre () 
    {
        this->field_count = 4;
        this->genre_typename = "book";
    }

    void Book::Show()
    {
        cout << "Title:   " << this->title << endl;
        cout << "Authors: ";
        for(std::list<string>::iterator it = authors.begin() ; it != authors.end() ; it++)
            cout << *it << "-";
        cout << endl;
        cout << "Title:   " << this->year << endl;
        cout << "Tags:    ";
        for(std::list<string>::iterator it = tags.begin() ; it != tags.end() ; it++)
            cout << *it << "-";
        cout << endl;
    }

}

#endif
