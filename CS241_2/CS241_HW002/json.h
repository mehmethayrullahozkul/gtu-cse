#ifndef JSON_H
#define JSON_H

const int MAX_PATH_LENGTH = 10;

#include "exception.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

namespace OS
{

    const int MAX = 99999;

    class JSON;
    class Node;

    class Node
    {

    private:
        string _key;
        bool _hasJSON;
        string _value;
        JSON *_child;
        JSON *_parent;

    public:
        int size() const;
        void clear();
        Node &operator[](const string &key);
        string key() const { return this->_key; }
        void key(const string &key) { this->_key = key; }
        string value() const { return _value; }
        void value(const string &value) { this->_value = value; }
        JSON *child() { return _child; }
        JSON *child() const { return _child; }
        void child(JSON *child) { this->_child = child; }
        JSON *parent() { return _parent; }
        JSON *parent() const { return _parent; }
        bool hasJSON() const { return _hasJSON; }
        void setHasJSON(bool hasJSON) { this->_hasJSON = hasJSON; }

        Node(const std::string &key, const std::string &value, JSON *parent = nullptr); // Corrected parameters
        Node(const std::string &key, JSON *child = nullptr, JSON *parent = nullptr);
        ~Node();
        void print() const;
    };

    class JSON
    {

        friend class Node;

    public:
        JSON();
        JSON(const JSON &json);
        ~JSON();

        JSON &operator=(const JSON &json);
        void clear();
        void add(const string &key, JSON *json, const list<string> &path = {});
        void add(const string &key, const string &value, const list<string> &path = {});
        void remove(const string &key, const list<string> &path = {});
        void update(const string &key, const string &value, const list<string> &path = {});
        void update(const string &key, JSON *json, const list<string> &path = {});
        bool hasKey(const string &key) const;
        Node *findKeyRecursive(const string &key);
        Node *findKeyInPath(const string &key, const list<string> &path);
        Node *findKey(const string &key);
        bool hasChild(const string &key) const;

        int totalSize() const;
        int size() const;
        Node &operator[](const string &key);
        Node &operator[](int index);

        Node &get(const string &key, const list<string> &path = {});

        // Member function to convert the JSON object to a string
        string stringify(unsigned int depth = 0) const;

        JSON &decode(const string &data);

        // Member function to write the JSON object to a file
        void save(const string &filename) const;
        // Member function to read a JSON object from a file
        void read(const string &filename);

        void print() const;

    private:
        vector<Node *> data;
        void addDataPair(const string &key, const string &value);
        void addNewNode(const string &key, JSON *json);
    };

}

int findNthOccurrence(const std::string &str, char target, size_t startPos, int n = 0);
ostream &operator<<(ostream &os, const OS::JSON &json);
ostream &operator<<(ostream &os, const OS::Node &node);
inline string indent(const unsigned int &depth);

#endif // JSON_H