#include "directory-file.h"
#include "regular-file.h"

namespace OS
{

    DirectoryFile::DirectoryFile() : File()
    {
        type(FileType::DIRECTORY);
    }

    DirectoryFile::DirectoryFile(const string &dirname) : DirectoryFile()
    {
        this->read(dirname);
    }

    DirectoryFile::~DirectoryFile()
    {
        for (list<File *> *fs : _dirStreams)
        {
            delete fs;
        }
        _dirStream.clear();
    }

    bool DirectoryFile::try_open(const string &dirpath)
    {
        const string dirname = DEFAULT_OS_PATH + strHash(dirpath) + File::defaultConfigExtension;
        if (!exists(dirname))
            /* file doesn't exist */
            return false;

        JSON json;
        json.read(dirname);

        if (json.get("type").value() != "dir")
            /* file is not a directory file */
            return false;

        return true;
    }

    bool DirectoryFile::exists(const string &dirname)
    {
        ifstream file(dirname);
        return file.good();
    }

    void DirectoryFile::print()
    {
        if (!good())
            throw Exception("directory hasn't initialized yet", ExceptionType::Directory);

        cout << path() << ": " << endl;
        DirectoryFile::iterator end = this->end();
        for (DirectoryFile::iterator it = begin(); it != end; ++it)
        {
            if ((*it).type() == FileType::REGULAR)
                cout << (*it).name() << endl;
            else if ((*it).type() == FileType::DIRECTORY)
                cout << (*it).name() << "/" << endl;
        }
        cout << endl;

        for (DirectoryFile::iterator it = begin(); it != end; ++it)
        {
            if ((*it).type() == FileType::DIRECTORY)
            {
                DirectoryFile *dir = dynamic_cast<DirectoryFile *>(&(*it));
                dir->print();
            }
        }
    }

    void DirectoryFile::readbyid(const string &file_id)
    {

        const string dirname = DEFAULT_OS_PATH + file_id + File::defaultConfigExtension;
        if (!exists(dirname))
            throw Exception("Error opening dir: " + dirname, ExceptionType::Directory);
        JSON json;
        json.read(dirname);
        id(json.get("id").value());
        name(json.get("name").value());
        path(json.get("path").value());
        lastModified(json.get("last_modified").value());
        size(stoi(json.get("size").value()));
        type(FileType::DIRECTORY);
        good(true);
        for (int i = 0; i < json["/"].child()->size(); i++)
        {
            JSON *child = json["/"].child()->operator[](i).child();
            if (child->get("type").value() == "regular")
            {
                RegularFile *file = new RegularFile();
                file->readbyid(child->get("id").value());
                _dirStream.push_back(file);
            }
            else if (child->get("type").value() == "dir")
            {
                DirectoryFile *file = new DirectoryFile();
                file->readbyid(child->get("id").value());
                _dirStream.push_back(file);
            }
        }
    }

    void DirectoryFile::addFile(File *file)
    {
        _dirStream.push_back(file);
    }

    void DirectoryFile::removeFile(File *file)
    {
        _dirStream.remove(file);
    }

    void DirectoryFile::read(const string &dirpath)
    {
        if (!try_open(dirpath))
            throw Exception("Error opening dir: " + dirpath);

        const string dirname = DEFAULT_OS_PATH + strHash(dirpath) + File::defaultConfigExtension;
        JSON json;
        json.read(dirname);
        id(json.get("id").value());
        name(json.get("name").value());
        path(json.get("path").value());
        lastModified(json.get("last_modified").value());
        size(stoi(json.get("size").value()));
        type(FileType::DIRECTORY);
        good(true);
        for (int i = 0; i < json["/"].child()->size(); i++)
        {
            JSON *child = json["/"].child()->operator[](i).child();
            if (child->get("type").value() == "regular")
            {
                RegularFile *file = new RegularFile();
                file->readbyid(child->get("id").value());
                _dirStream.push_back(file);
            }
            else if (child->get("type").value() == "dir")
            {
                DirectoryFile *file = new DirectoryFile();
                file->readbyid(child->get("id").value());
                file->type(FileType::DIRECTORY);
                _dirStream.push_back(file);
            }
        }
    }

    void DirectoryFile::update()
    {
        if (!good())
            return;

        int dir_size = 0;

        for (File *file : _dirStream)
        {
            if (file->type() == FileType::DIRECTORY)
            {
                DirectoryFile *dir = dynamic_cast<DirectoryFile *>(file);
                if (DirectoryFile::exists(DEFAULT_OS_PATH + dir->id() + File::defaultConfigExtension))
                {
                    dir->update();
                    dir_size += dir->size();
                }
                else
                {

                    dir->remove();
                    _dirStream.remove(dir);
                }
            }
            else
            {
                RegularFile *regularFile = dynamic_cast<RegularFile *>(file);
                if (DirectoryFile::exists(DEFAULT_OS_PATH + regularFile->id() + File::defaultConfigExtension))
                {
                    regularFile->update();
                    dir_size += regularFile->size();
                }
                else
                {
                    regularFile->remove();
                    _dirStream.remove(regularFile);
                };
            }
        }
        size(dir_size);
        save();
    }

    void DirectoryFile::removeFile(const string &file_id)
    {
        for (File *file : _dirStream)
        {
            if (file->id() == file_id)
            {
                file->remove();
                _dirStream.remove(file);
                break;
            }
        }
        update();
    }

    void DirectoryFile::save()
    {
        if (!good())
            return;
        JSON json;
        json.add("id", id());
        json.add("name", name());
        json.add("path", path());
        json.add("last_modified", lastModified());
        json.add("size", to_string(size()));
        json.add("parent", parent());
        json.add("type", "dir");
        JSON *files = new JSON();
        for (File *file : _dirStream)
        {
            JSON *child = new JSON();
            child->add("id", file->id());
            child->add("name", file->name());
            child->add("path", file->path());
            child->add("last_modified", file->lastModified());
            child->add("size", to_string(file->size()));
            child->add("type", file->type() == FileType::REGULAR ? "regular" : "dir");
            if (file->type() == FileType::REGULAR)
            {
                files->add(file->id(), child);
                RegularFile *regularFile = dynamic_cast<RegularFile *>(file);
                child->add("content_file", regularFile->linkedFile());
                child->add("extension", regularFile->extension());
            }
            else
            {
                files->add(file->name(), child);
                child->add("parent", path());
            }
        }
        json.add("/", files);
        const string dirname = DEFAULT_OS_PATH + id() + File::defaultConfigExtension;
        json.save(dirname);
    }

    void DirectoryFile::remove()
    {
        for (File *file : _dirStream)
        {
            file->remove();
        }
        _dirStream.clear();

        const string dirname = DEFAULT_OS_PATH + id() + File::defaultConfigExtension;
        if (!DirectoryFile::exists(dirname))
            throw Exception("error removing dir: " + dirname, ExceptionType::Directory);

        std::remove(dirname.c_str());
        good(false);
    }

    DirectoryFile::iterator DirectoryFile::begin()
    {
        list<File *> *fs = new list<File *>(_dirStream);

        _dirStreams.push_back(fs);
        return iterator(*fs);
    }

    DirectoryFile::iterator DirectoryFile::end()
    {
        list<File *> *fs = new list<File *>();
        _dirStreams.push_back(fs);
        return iterator(*fs);
    }

    DirectoryFile::iterator::iterator(list<File *> &_dirStream) : _files(_dirStream)
    {
        if (!_files.empty())
        {
            _current_file = _files.front();
            _files.pop_front();
        }
        else
        {
            _current_file = nullptr;
        }
    }

    DirectoryFile::iterator::~iterator()
    {
        _files.clear();
    }

    void DirectoryFile::iterator::next()
    {
        if (hasNext())
        {
            _current_file = _files.front();
            _files.pop_front();
        }
        else
        {
            _current_file = nullptr;
        }
    }

    bool DirectoryFile::iterator::equals(const File::iterator &other) const
    {
        const DirectoryFile::iterator *otherIterator = dynamic_cast<const DirectoryFile::iterator *>(&other);
        if (otherIterator)
        {
            return _current_file == otherIterator->_current_file;
        }
        return false;
    }

    bool DirectoryFile::iterator::hasNext() const
    {
        return !_files.empty();
    }

    File &DirectoryFile::iterator::operator*() const
    {
        return *_current_file;
    }

    // Overload the pre-increment operator (++iter)
    DirectoryFile::iterator &DirectoryFile::iterator::operator++()
    {
        if (hasNext())
        {
            _current_file = _files.front();
            _files.pop_front();
        }
        else
        {
            _current_file = nullptr;
        }
        return *this;
    }

    // Overload the post-increment operator (iter++)
    DirectoryFile::iterator DirectoryFile::iterator::operator++(int)
    {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Overload the equality operator (iter1 == iter2)
    bool DirectoryFile::iterator::operator==(const File::iterator &other) const
    {
        return equals(other);
    }

    // Overload the inequality operator (iter1 != iter2)
    bool DirectoryFile::iterator::operator!=(const File::iterator &other) const
    {
        return !equals(other);
    }
}
