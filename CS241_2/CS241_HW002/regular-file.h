#ifndef REGULAR_FILE_H
#define REGULAR_FILE_H

#include "file.h"

namespace OS
{

    class RegularFile : public File

    {

    private:
        string _extension;
        string _linked_file;
        mutable list<ifstream *> _fileStreams = {};

    public:
        RegularFile();
        RegularFile(const string &path);
        ~RegularFile();
        string extension() const;
        void extension(const string &extension);
        string linkedFile() const;
        void linkedFile(const string &linked_file);
        static bool try_open(const string &filename);
        static bool exists(const string &filename);
        static string get_extension(const string &filename);
        static int get_size(const string &filename);
        void print();
        void read(const string &filename);
        void readbyid(const string &file_id);
        void save();
        void remove();
        void update();
        void updateSize();

        class iterator : public File::iterator
        {
        public:
            iterator(std::ifstream &fileStream);
            iterator(const string &filename);
            ~iterator();

            void next() override;

            bool equals(const File::iterator &other) const override;

            bool hasNext() const override;

            const char &operator*() const;

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
            ifstream &_iteratorStream;
            char _character;
        };

        // RegularFile::iterator begin();
        // RegularFile::iterator end();
        RegularFile::iterator begin();
        RegularFile::iterator end();
    };
} // namespace OS namespace OS

#endif // REGULAR_FILE_H