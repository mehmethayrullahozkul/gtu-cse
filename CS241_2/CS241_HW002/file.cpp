#include "file.h"

namespace OS
{
    const string File::defaultConfigExtension = ".json";
    File::File() : _name(""), _path(""), _last_modified(currentTime()), _size(0), _good(false) {}
    File::~File() {}

    File::iterator::iterator() {}
    File::iterator::~iterator() {}

    string File::id() const { return _id; }
    void File::id(const string &id) { _id = id; }
    void File::updateTime() { _last_modified = currentTime(); }

    string File::parent() const { return _parent; }
    void File::parent(const string &parent) { _parent = parent; }
    string File::path() const { return _path; }
    void File::path(const string &path) { _path = path; }
    string File::lastModified() const { return _last_modified; }
    void File::lastModified(const string &last_modified) { _last_modified = last_modified; }
    int File::size() const { return _size; }
    void File::size(int size) { _size = size; }
    FileType File::type() const { return _type; }
    void File::type(const FileType &type) { _type = type; }
    string File::name() const { return _name; }
    void File::name(const string &name) { _name = name; }
    bool File::good() const { return _good; }
    void File::good(const bool &good) { _good = good; }
} // namespace OS
