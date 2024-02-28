#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <list>
#include "Entry.h"
#include "Book.h"
#include "Movie.h"
#include "Music.h"

#ifndef _h_catalog
#define _h_catalog


namespace catalog
{
    const string DATA_FILE    = "data.txt";
    const string COMMAND_FILE = "commands.txt";
    const string LOG_FILE     = "output.txt";


    template <class Type> class Catalog
    {
        friend class Movie;
        friend class Book;
        friend class Music;

        public:
            Catalog();
            Catalog(const string data_file, const string command_file, const string log_file);

            int whatType();
            bool Open(const string& filename);
            bool Commands(const string& filename);
            bool CheckDuplicate(list<Type>& compare_data, list<Type>& duplicate_list);
            bool Execute();
            bool Log(const string& log);
            bool Sort(const string& field);

        private:

            Type Check;
            list<Type> Data;
            int entry_count;
            int type;
            vector<string> CommandList;
    };






    template <class Type> Catalog<Type>::Catalog()
    {
        this->type = Check.Type();
    }




    template <class Type> Catalog<Type>::Catalog(const string data_file, const string command_file, const string log_file)
    {
        this->type = Check.Type();
        Open(data_file);
    }




    template <class Type> bool Catalog<Type>::Open(const string& filename)
    {
        string token;
        std::ifstream read;
        read.open(filename);

        if(!read)
            throw(Exception("Exception: cant open file", CatalogExceptions::CANT_OPEN_FILE));


        read >> token;
        read.ignore(1);
        if(Check.Typename() != token)
            throw(Exception("Exception: catalog type doesn't match", CatalogExceptions::INVALD_TYPE));
        
        Log("Catalog Read: " + Check.Typename());

        int i = 0;
        while(getline(read, token))
        {
            try
            {
                Type *t_data = new Type(token);
                Data.push_back(*t_data);
            }
            catch (Exception E)
            {
                Log(E.getMessage() + token);
            }
        }
        read.close();

        std::list<Type> Duplicates;
        CheckDuplicate(Data, Duplicates);

        typename std::list<Type>::iterator it;
        typename std::list<Type>::iterator at;

        for(it = Duplicates.begin() ; it != Duplicates.end() ; it++)
        {
            Log("Exception: duplicate entry \n" + (*it).Data());
        }
        

        for(it = Duplicates.begin() ; it != Duplicates.end() ; it++)
        {
            for(at = Data.begin() ; at != Data.end() ; at++)
            {
                if((*it).Title() == (*at).Title())
                    {
                        Data.erase(at);
                        break;
                    }
            }
        }
        Log("\nUnique entries found: " + std::to_string(Data.size()));
        for(at = Data.begin() ; at != Data.end() ; at++)
        {
            Log((*at).Data());
        }
        
        return true;
    }





    template <class Type> bool Catalog<Type>::Log(const string& log)
    {
        std::ofstream append;
        append.open(LOG_FILE, std::ios::app);

        if(!append)
            throw(Exception("Exception: couldn't write to log file", CatalogExceptions::CANT_OPEN_FILE));

        append << log << endl;
        append.close();
        return true;
    }





    template <class Type> int Catalog<Type>::whatType()
    {
        return this->type;
    }




    template <class Type> bool Catalog<Type>::CheckDuplicate(list<Type>& compare_data, list<Type>& duplicate_list)
    {
        bool already_registered;
        typename std::list<Type>::iterator it;
        typename std::list<Type>::iterator at;
        typename std::list<Type>::iterator ot;
        //for(it = compare_data.begin() ; it != compare_data.end() ; it++)
        //    EntryList->push_back(it);
        
        for(it = compare_data.begin() ; it != compare_data.end() ; ++it)
        {
            for(at = compare_data.begin() ; at != compare_data.end() ; ++at)
            {
                if(it == at)
                {   
                    continue;
                }
                if((*it).Title() == (*at).Title())
                {
                    already_registered = false;
                    for(ot = duplicate_list.begin() ; ot != duplicate_list.end() ; ++ot)
                    {
                        if((*ot).Title() == (*it).Title())
                        {
                            already_registered = true;
                            break;
                        }
                    }
                    if(!already_registered)
                    {   
                        duplicate_list.push_back(*it);
                        duplicate_list.push_back(*at);
                    }
                }
                
            }
        }

        return false;
    }


    template <class Type> bool Catalog<Type>::Commands(const string& filename)
    {
        std::ifstream read;
        bool check_field = 0;
        string token;
        read.open(filename);
        if(!read)
            throw(Exception("Exception: cant open file", CatalogExceptions::CANT_OPEN_FILE));
        
        while(getline(read, token))
        {
            CommandList.push_back(token);
        }
        for(int a = 0 ; a < CommandList.size() ; a++)
        {
            std::istringstream ObjectStream(CommandList[a]);
            ObjectStream >> token;


            
            if(token == "search")
            {
                ObjectStream >> token >> token >> token;
                try
                {
                    Trim(token, '\"', BOTH_RES);
                }
                catch (Exception E)
                {
                    Log("Exception: command is wrong \n" + CommandList[a]);
                }
                check_field = false;
                for(int b = 0 ; b < Check.FieldCount() ; b++)
                {
                    if(Check.Fields[b] == token)
                        check_field = true;
                }
                if(!check_field)
                {
                    Log("Exception: command is wrong \n" + CommandList[a]);
                    CommandList.erase(CommandList.begin() + a);
                    a--;
                }
                else
                    Log(CommandList[a]);
            }


            else if (token == "sort")
            {
                ObjectStream >> token;
                try
                {
                    Trim(token, '\"', BOTH_RES);
                }
                catch (Exception E)
                {
                    Log("Exception: command is wrong \n" + CommandList[a]);
                }
                check_field = false;
                for(int b = 0 ; b < Check.FieldCount() ; b++)
                {
                    if(Check.Fields[b] == token)
                        check_field = true;
                }
                if(!check_field)
                {
                    Log("Exception: command is wrong \n" + CommandList[a]);
                    CommandList.erase(CommandList.begin() + a);
                    a--;
                }
                else
                {
                    Log(CommandList[a]);
                }
            }
            else
            {
                Log("Exception: command is wrong \n" + CommandList[a]);
                CommandList.erase(CommandList.begin() + a);
                a--;
            }
        }
        Log("\nUnique commands found : " + std::to_string(CommandList.size()));
        for(int i = 0 ; i < CommandList.size() ; i++)
            Log(CommandList[i]);
        return true;
    }



    template <class Type> bool Catalog<Type>::Execute()
    {
        string token;
        string searched;
        list<Type> FoundList;
        typename std::list<Type>::iterator it;
        for(int a = 0 ; a < CommandList.size() ; a++)
        {
            std::istringstream ObjectStream(CommandList[a]);
            ObjectStream >> token;
            if(CommandList[a] == "search")
            {
                ObjectStream >> searched >> token >> token;
                Trim(searched, '\"', BOTH_RES);
                Trim(token, '\"', BOTH_RES);
                if(token == "year")
                {
                    for(it = Data.begin() ; it != Data.end() ; it++)
                    {
                        if((*it).Year() == searched)
                        {
                            FoundList.push_back(*it);
                        }
                    }
                }
                else if(token == "title")
                {
                    for(it = Data.begin() ; it != Data.end() ; it++)
                    {
                        if((*it).Title() == searched)
                        {
                            FoundList.push_back(*it);
                        }
                    }
                }
            }
            else if(CommandList[a] == "sort") {}
        }
        for(it = FoundList.begin() ; it != FoundList.end() ; it++)
            Log((*it).Data());
        return true;
    }
}

#endif
