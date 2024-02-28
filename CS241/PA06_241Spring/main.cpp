#include <iostream>
#include <fstream>
#include "Entry.h"
#include <list>
#include "Catalog.h"
#include "Exception.h"

using std::string;
using std::cin;
using std::cout;

using namespace catalog;

int Type(const string& filename);

int main()
{
    try
    {

        const int catalog_type = Type(DATA_FILE);

        switch (catalog_type)
        {
            case TYPE_BOOK:
            {
                Catalog<Book> Object;
                Object.Open(DATA_FILE);
                Object.Commands(COMMAND_FILE);
                Object.Execute();
                break;
            }
            case TYPE_MOVIE:
            {
                Catalog<Movie> Object;
                Object.Open(DATA_FILE);
                Object.Commands(COMMAND_FILE);
                Object.Execute();
                break;
            }
            case TYPE_MUSIC:
            {
                Catalog<Music> Object;
                Object.Open(DATA_FILE);
                Object.Commands(COMMAND_FILE);
                Object.Execute();

                break;
            }
        }


        


        //string data; 
        //getline(F, data);
        //list<Book> b;
        //N.Parse(data, 0, '\0', '\0', '\0');
        //for(int i = 0 ; i < N.Size() ; i++)
        //    cout << N[i] << endl;
    }
    catch(Exception E)
    {
        cout << E.getMessage() << " - " << E.getError() << endl;
    } 
}


int Type(const string& filename)
{
    std::ifstream get_type;
    string s;
    get_type.open(filename);
    if(!get_type)
        throw(Exception("Exception: file could not opened", CatalogExceptions::CANT_OPEN_FILE));
    get_type >> s;
    
    if(s == MOVIE)
        return TYPE_MOVIE;
    else if (s == BOOK)
        return TYPE_BOOK;
    else if (s == MUSIC)
        return TYPE_MUSIC;
    else
        throw(Exception("Exception: invalid catalog type", CatalogExceptions::INVALD_TYPE));
}