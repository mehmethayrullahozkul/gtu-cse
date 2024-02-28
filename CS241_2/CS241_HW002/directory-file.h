#ifndef DIRECTORY_FILE_H
#define DIRECTORY_FILE_H

#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>

namespace OS
{

    class DirectoryFile : public File

    {

    private:
        string _parent;
        mutable list<File *> _dirStream = {};
        list<list<File *> *> _dirStreams = {};

    public:
        DirectoryFile();
        DirectoryFile(const string &path);
        ~DirectoryFile();
        static bool try_open(const string &directory_path);
        static bool exists(const string &directory);
        void print();
        void read(const string &directory);
        void readbyid(const string &file_id);
        void remove();
        void save();
        void addFile(File *file);
        void removeFile(File *file);
        void removeFile(const string &file_id);
        void update();

        class iterator : public File::iterator
        {
        public:
            iterator(list<File *> &_dirStream);
            ~iterator();

            void next() override;

            bool equals(const File::iterator &other) const override;

            bool hasNext() const override;

            File &operator*() const;

            // Overload the pre-increment operator (++iter)
            iterator &
            operator++() override;

            // Overload the post-increment operator (iter++)
            iterator operator++(int);

            // Overload the equality operator (iter1 == iter2)
            bool operator==(const File::iterator &other) const override;

            // Overload the inequality operator (iter1 != iter2)
            bool operator!=(const File::iterator &other) const override;
            // Overload the dereference operator (*iter)

        private:
            list<File *> _files;
            File *_current_file;
        };

        // DirectoryFile::iterator begin();
        // DirectoryFile::iterator end();
        DirectoryFile::iterator begin();
        DirectoryFile::iterator end();
    };
} // namespace OS namespace OS

#endif // Directory_FILE_H