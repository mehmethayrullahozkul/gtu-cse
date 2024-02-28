#ifndef FILE_H
#define FILE_H

#include "os.h"
#include "exception.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

namespace OS
{
    enum class FileType
    {
        REGULAR,
        DIRECTORY,
        LINK
    };

    class File
    {

    private:
        string _id;
        string _name;
        string _path;
        string _last_modified;
        string _parent;
        int _size;
        FileType _type;
        bool _good;

    public:
        File();
        ~File();
        string id() const;
        void id(const string &id);
        string path() const;
        void path(const string &path);
        string lastModified() const;
        void lastModified(const string &last_modified);
        int size() const;
        void size(int size);
        FileType type() const;
        void type(const FileType &type);
        string name() const;
        void name(const string &name);
        bool good() const;
        void good(const bool &good);
        void parent(const string &parent);
        string parent() const;
        void updateTime();

        // virtual bool exists(const string &filename) const = 0;
        virtual void print() = 0;
        virtual void read(const string &filename) = 0;
        virtual void readbyid(const string &file_id) = 0;
        virtual void remove() = 0;
        static const string defaultConfigExtension;

        class iterator
        {
        public:
            iterator();
            virtual ~iterator();

            virtual void next() = 0;
            virtual bool equals(const iterator &other) const = 0;
            virtual bool hasNext() const = 0;
            virtual iterator &operator++() = 0;
            // virtual iterator operator++(int) = 0;
            virtual bool operator==(const iterator &other) const = 0;
            virtual bool operator!=(const iterator &other) const = 0;
        };

        // virtual File::iterator begin() = 0;
        // virtual File::iterator end() = 0;
    };
} // namespace OS

#endif // FILE_H
