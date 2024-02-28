#include "link-file.h"

namespace OS
{

    LinkFile::LinkFile() : File()
    {
        type(FileType::REGULAR);
    }

    LinkFile::LinkFile(const string &filepath) : LinkFile()
    {
        this->read(filepath);
    }

    LinkFile::~LinkFile()
    {
        for (std::ifstream *fs : _fileStreams)
        {
            fs->close();
            delete fs;
        }
    }

    bool LinkFile::try_open(const string &filepath)
    {
        const string filename = DEFAULT_OS_PATH + strHash(filepath) + File::defaultConfigExtension;
        if (!exists(filename))
        {
            cerr << "error opening file: " << filename << endl;
            return false;
        }

        JSON json;
        json.read(filename);

        if (json.get("type").value() != "regular")
        {
            cerr << "error not a regular file" << endl;
            return false;
        }

        const string linkedFilename = DEFAULT_OS_PATH + json.get("content_file").value();

        fstream linkedFile(linkedFilename);

        if (!linkedFile.is_open())
        {
            cerr << "content file " << linkedFilename << " does not exist" << endl;
            return false;
        }

        linkedFile.close();
        return true;
    }

    bool LinkFile::exists(const string &filename)
    {
        ifstream file(filename);
        return file.good();
    }

    void LinkFile::print()
    {
        if (!good())
            throw Exception("file is not good", ExceptionType::Link);

        LinkFile::iterator end = this->end();
        for (LinkFile::iterator it = begin(); it != end; ++it)
        {
            cout << *it;
        }
        cout << endl;
    }

    void LinkFile::read(const string &filepath)
    {
        if (!try_open(filepath))
        {
            cerr << "file " << filepath << " does not exist" << endl;
            return;
        }
        readbyid(strHash(filepath));
    }

    void LinkFile::readbyid(const string &file_id)
    {
        const string filename = DEFAULT_OS_PATH + file_id + File::defaultConfigExtension;
        if (!exists(filename))
            throw Exception("file doesn't exist", ExceptionType::File);
        JSON json;
        json.read(filename);
        id(json.get("id").value());
        name(json.get("name").value());
        path(json.get("path").value());
        lastModified(json.get("last_modified").value());
        size(stoi(json.get("size").value()));
        type(FileType::REGULAR);
        good(true);
        linkedFile(json.get("content_file").value());
        extension(json.get("extension").value());
    }

    void LinkFile::remove()
    {
        if (!good())
            return;
        const string filename = DEFAULT_OS_PATH + id() + File::defaultConfigExtension;
        if (!exists(filename))
            throw Exception("file doesn't exist", ExceptionType::Link);

        JSON json;
        json.read(filename);
        const string linkedFilename = DEFAULT_OS_PATH + json.get("content_file").value();
        if (!exists(linkedFilename))
            throw Exception("content file doesn't exist", ExceptionType::Link);
        std::remove(filename.c_str());
        std::remove(linkedFilename.c_str());
        good(false);
    }

    void LinkFile::updateSize()
    {

        if (!good())
            return;

        int old_size = size();
        int new_size = 0;
        std::ifstream inputFile(DEFAULT_OS_PATH + _linked_file, std::ios::binary);

        if (inputFile.is_open())
        {
            inputFile.seekg(0, std::ios::end);              // Move to the end of the file
            new_size = static_cast<int>(inputFile.tellg()); // Get the current position (file size)
            inputFile.close();                              // Close the file
        }
        if (old_size != new_size)
            updateTime();
        size(new_size);
    }

    void LinkFile::update()
    {
        updateSize();
        save();
    }

    void LinkFile::save()
    {
        if (!good())
            return;
        JSON json;
        json.add("id", id());
        json.add("name", name());
        json.add("last_modified", lastModified());
        json.add("size", to_string(size()));
        json.add("path", path());
        json.add("type", "regular");
        json.add("content_file", _linked_file);
        json.add("extension", _extension);
        const string dirname = DEFAULT_OS_PATH + id() + File::defaultConfigExtension;
        json.save(dirname);
    }

    LinkFile::iterator LinkFile::begin()
    {
        const string linkedFilename = DEFAULT_OS_PATH + _linked_file;
        std::ifstream *fs = new ifstream(linkedFilename);
        _fileStreams.push_back(fs);
        return iterator(*fs);
    }

    LinkFile::iterator LinkFile::end()
    {
        std::ifstream *fs = new ifstream();
        _fileStreams.push_back(fs);
        return iterator(*fs);
    }

    string LinkFile::extension() const { return _extension; }
    void LinkFile::extension(const string &extension) { _extension = extension; }
    string LinkFile::linkedFile() const { return _linked_file; }
    void LinkFile::linkedFile(const string &linked_file) { _linked_file = linked_file; }

    LinkFile::iterator::iterator(std::ifstream &fileStream) : _iteratorStream(fileStream), _character(' ')
    {
        if (_iteratorStream.is_open())
            _iteratorStream.get(_character);
        else
            _character = '\0';
    }

    LinkFile::iterator::~iterator()
    {
        _iteratorStream.close();
    }

    void LinkFile::iterator::next()
    {
        if (hasNext())
            _iteratorStream.get(_character);
    }

    bool LinkFile::iterator::equals(const File::iterator &other) const
    {
        const LinkFile::iterator *otherIterator = dynamic_cast<const LinkFile::iterator *>(&other);
        if (otherIterator)
        {
            return _iteratorStream.tellg() == otherIterator->_iteratorStream.tellg();
        }
        return false;
    }

    bool LinkFile::iterator::hasNext() const
    {
        return _character != '\0';
    }

    const char &LinkFile::iterator::operator*() const
    {
        return _character;
    }

    // Overload the pre-increment operator (++iter)
    LinkFile::iterator &LinkFile::iterator::operator++()
    {
        if (_iteratorStream.get(_character))
        {
            // get next character
        }
        else
        {
            // end of file
            _character = '\0';
        }

        return *this;
    }

    // Overload the post-increment operator (iter++)
    LinkFile::iterator LinkFile::iterator::operator++(int)
    {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Overload the equality operator (iter1 == iter2)
    bool LinkFile::iterator::operator==(const File::iterator &other) const
    {
        return equals(other);
    }

    // Overload the inequality operator (iter1 != iter2)
    bool LinkFile::iterator::operator!=(const File::iterator &other) const
    {
        return !equals(other);
    }

    string LinkFile::get_extension(const string &filename)
    {
        size_t pos = filename.find_last_of('.');
        if (pos == string::npos)
            return "";
        return "." + filename.substr(pos + 1);
    }

    int LinkFile::get_size(const string &filename)
    {
        std::ifstream inputFile(filename, std::ios::binary);

        if (inputFile.is_open())
        {
            inputFile.seekg(0, std::ios::end); // Move to the end of the file
            int size = static_cast<int>(inputFile.tellg());
            inputFile.close(); // Close the file
            return size;
        }
        return 0;
    }
}
