#include "json.h"

namespace OS
{
    Node::Node(const std::string &key, const std::string &value, JSON *parent)
    {
        this->_key = key;
        this->_value = value;
        this->_child = nullptr;
        this->_hasJSON = false;
        this->_parent = parent;
    }

    Node::Node(const std::string &key, JSON *child, JSON *parent)
    {
        this->_key = key;
        this->_value = ""; // You may want to set a default value for 'value'
        this->_child = child;
        this->_hasJSON = true;
        this->_parent = parent;
    }

    void Node::print() const
    {
        if (_hasJSON)
        {
            cout << _key << ": " << endl;
            _child->print();
        }
        else
        {
            cout << _key << ": " << _value << endl;
        }
    }

    Node &Node::operator[](const string &key)
    {
        if (this->_hasJSON)
        {
            for (int i = 0; i < this->_child->data.size(); i++)
            {
                if (this->_child->data[i]->key() == key)
                    return *(this->_child->data[i]);
            }
        }
        return *this;
    }

    int Node::size() const
    {
        if (this->_hasJSON)
        {
            return this->_child->size();
        }
        return 1;
    }

    void Node::clear()
    {
        if (this->_hasJSON)
            this->_child->clear();
        this->key("");
        this->value("");
        this->_hasJSON = false;
        this->_child = nullptr;
        delete this;
    }

    Node::~Node()
    {
        // Already implemented, nothing to do here
    }

    JSON::JSON()
    {
        this->data = {};
    }

    JSON::~JSON()
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i]->clear();
        }
        data.clear();
        // delete this;
    }

    JSON::JSON(const JSON &json)
    {
        for (int i = 0; i < json.data.size(); i++)
        {
            this->data.push_back(new Node(json.data[i]->key(), json.data[i]->value(), this));
            if (json.data[i]->hasJSON())
            {
                this->data[i]->setHasJSON(true);
                this->data[i]->child(new JSON(*(json.data[i]->child())));
            }
        }
    }

    JSON &JSON::operator=(const JSON &json)
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i]->clear();
        }
        data.clear();
        for (int i = 0; i < json.data.size(); i++)
        {
            this->data.push_back(new Node(json.data[i]->key(), json.data[i]->value(), this));
            if (json.data[i]->hasJSON())
            {
                this->data[i]->setHasJSON(true);
                this->data[i]->child(new JSON(*(json.data[i]->child())));
            }
        }
        return *this;
    }

    void JSON::clear()
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i]->clear();
        }
        data.clear();
    }

    void JSON::add(const string &key, const string &value, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    data[i]->value(value);
                    return;
                }
            }
            this->addDataPair(key, value);
            return;
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    JSON *child = new JSON();
                    ptr->addNewNode(*it, child);
                    ptr = child;
                }
            }
            if (ptr->hasKey(key))
            {
                (*(ptr))[key].value(value);
            }
            else
            {
                ptr->addDataPair(key, value);
            }
        }
    }

    void JSON::add(const string &key, JSON *json, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    // if the key already present, do nothing and return
                    return;
                }
            }
            // if not present, add the key and json
            ptr->addNewNode(key, json);
            return;
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    JSON *child = new JSON();
                    ptr->addNewNode(*it, child);
                    ptr = child;
                }
            }
            if (ptr->hasKey(key))
            {
                // if already present, do nothing and return
            }
            else
            {
                ptr->addNewNode(key, json);
            }
        }
    }

    Node *JSON::findKeyRecursive(const string &key)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i]->key() == key)
            {
                return data[i];
            }
            else if (data[i]->hasJSON())
            {
                if (data[i]->child()->findKeyRecursive(key) != nullptr)
                    return data[i]->child()->findKeyRecursive(key);
            }
        }
        return nullptr;
    }

    Node *JSON::findKeyInPath(const string &key, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    return data[i];
                }
            }
            return nullptr;
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    return nullptr;
                }
            }
            if (ptr->hasKey(key))
            {
                return ptr->findKey(key);
            }
            else
            {
                return nullptr;
            }
        }
    }

    Node *JSON::findKey(const string &key)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i]->key() == key)
            {
                return data[i];
            }
        }
        return nullptr;
    }

    void JSON::remove(const string &key, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    data.erase(find(data.begin(), data.end(), data[i]));
                    data[i]->clear();
                    return;
                }
            }
            throw Exception("remove, key not found in json", ExceptionType::JSON);
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    return;
                }
            }
            if (ptr->hasKey(key))
            {
                Node *node = ptr->findKey(key);
                if (node->parent() != nullptr)
                    node->parent()->data.erase(find(node->parent()->data.begin(), node->parent()->data.end(), node));
                node->clear();
            }
            else
                throw Exception("remove, key not found in json", ExceptionType::JSON);
        }
    }

    void JSON::update(const string &key, const string &value, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    if (!data[i]->hasJSON())
                        data[i]->value(value);
                    return;
                }
            }
            throw Exception("update, key not found in json", ExceptionType::JSON);
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    return;
                }
            }
            if (ptr->hasKey(key))
            {
                if (!ptr->findKey(key)->hasJSON())
                    ptr->findKey(key)->value(value);
            }
            else
                throw Exception("update, key not found in json", ExceptionType::JSON);
        }
    }

    void JSON::update(const string &key, JSON *json, const list<string> &path)
    {
        JSON *ptr = this;
        if (path.size() == 0)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i]->key() == key)
                {
                    if (data[i]->hasJSON())
                        data[i]->child();
                    data[i]->setHasJSON(true);
                    data[i]->child(json);
                    return;
                }
            }
            throw Exception("update, key not found in json", ExceptionType::JSON);
        }
        else
        {
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                {
                    ptr = ptr->operator[](*it).child();
                }
                else
                {
                    return;
                }
            }
            if (ptr->hasKey(key))
            {
                if (ptr->findKey(key)->hasJSON())
                    delete ptr->findKey(key)->child();
                ptr->findKey(key)->setHasJSON(true);
                ptr->findKey(key)->child(json);
            }
            else
                throw Exception("update, key not found in json", ExceptionType::JSON);
        }
    }

    bool JSON::hasKey(const string &key) const
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i]->key() == key)
                return true;
        }
        return false;
    }

    bool JSON::hasChild(const string &key) const
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i]->key() == key)
            {
                if (data[i]->hasJSON())
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    Node &JSON::operator[](const string &key)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i]->key() == key)
                return *(data[i]);
        }
        throw Exception("invalid access, key not found in json", ExceptionType::JSON);
        // return *(data[0]);
    }

    Node &JSON::operator[](int index)
    {
        if (index < data.size())
            return *(data[index]);
        throw Exception("invalid access, index out of range", ExceptionType::JSON);
    }

    Node &JSON::get(const string &key, const list<string> &path)
    {
        if (path.size() == 0)
            return this->operator[](key);
        else
        {
            JSON *ptr = this;
            list<string>::const_iterator it = path.begin();
            for (; it != path.end(); ++it)
            {
                if (ptr->hasChild(*it))
                    ptr = ptr->operator[](*it).child();
                else
                    throw Exception("get, key not found in json", ExceptionType::JSON);
            }
            if (ptr->hasKey(key))
                return ptr->operator[](key);
            else
                throw Exception("get, key not found in json", ExceptionType::JSON);
        }
    }

    void JSON::addDataPair(const string &key, const string &value)
    {
        Node *node = new Node(key, value, this);
        this->data.push_back(node);
    }

    void JSON::addNewNode(const string &key, JSON *json)
    {
        Node *node = new Node(key, json, this);
        this->data.push_back(node);
    }

    // Member function to convert the JSON object to a string
    string JSON::stringify(unsigned int depth) const
    {
        string json = "{\n";
        for (int i = 0; i < data.size(); i++)
        {
            json += indent(depth + 1);
            json += "\"" + data[i]->key() + "\": ";
            if (data[i]->hasJSON())
            {
                json += data[i]->child()->stringify(depth + 1);
            }
            else
            {
                json += "\"" + data[i]->value() + "\"";
            }
            if (i != data.size() - 1)
                json += ", ";
            json += "\n";
        }
        json += indent(depth);
        json += "}";
        return json;
    }

    // Member function to write the JSON object to a file
    void JSON::save(const string &filename) const
    {
        ofstream file(filename, std::ios::out);
        if (file.is_open())
        {
            file << stringify();
            file.close();
        }
        else
            throw Exception("error saving file", ExceptionType::JSON);
    }

    // Member function to read a JSON object from a file
    void JSON::read(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            stringstream buffer;
            buffer << file.rdbuf();
            decode(buffer.str());
            file.close();
        }
        else
            throw Exception("error reading file", ExceptionType::JSON);
    }

    int JSON::totalSize() const
    {
        int total = 0;
        for (int i = 0; i < data.size(); i++)
        {
            total += data[i]->size();
        }
        return total;
    }

    int JSON::size() const
    {
        return this->data.size();
    }

    // Private member function to parse a JSON string
    JSON &JSON::decode(const string &json)
    {
        size_t start = json.find_first_of('{') + 1;
        size_t end = json.find_last_of('}');
        string jsonContent = json.substr(start, end - start);
        istringstream iss(jsonContent);

        char ch;
        string buffer;
        string key;
        bool nextKey = true, nextValue = false, inQuotes = false;
        while (iss.get(ch))
        {
            if (nextKey)
            {
                if (ch != '\"')
                    continue;
                else if (ch == '\"')
                {
                    getline(iss, key, '\"');
                    nextKey = false;
                    nextValue = true;
                }
            }
            else if (nextValue)
            {
                int posCurlyBraces = findNthOccurrence(jsonContent, '{', iss.tellg());
                int posQuotes = findNthOccurrence(jsonContent, '\"', iss.tellg());
                if (posCurlyBraces < posQuotes && posCurlyBraces != OS::MAX)
                {
                    int cbCount = 0;
                    int posEndCurlyBraces;
                    while (iss.get(ch))
                    {
                        if (ch == '}')
                        {
                            if (cbCount <= 1)
                            {
                                posEndCurlyBraces = iss.tellg();
                                break;
                            }
                            else
                                cbCount--;
                        }
                        else if (ch == '{')
                            cbCount++;
                    }
                    string childJson = jsonContent.substr(posCurlyBraces, posEndCurlyBraces - posCurlyBraces + 1);
                    JSON *childJSON = new JSON();
                    childJSON->decode(childJson);
                    this->addNewNode(key, childJSON);
                }
                else if (posQuotes < posCurlyBraces && posQuotes != OS::MAX)
                {
                    while (iss.get(ch))
                    {
                        if (ch == '\"')
                            break;
                    }
                    getline(iss, buffer, '\"');
                    this->addDataPair(key, buffer);
                }
                nextKey = true;
                nextValue = false;
            }
        }
        return *this;
    }

    void JSON::print() const
    {
        cout << stringify() << endl;
    };
}

int findNthOccurrence(const std::string &str, char target, size_t startPos, int nth)
{
    size_t length = str.length();
    int count = 0;

    // Iterate through the string starting from the specified position
    for (size_t i = startPos; i < length; ++i)
    {
        // Check if the current character is the target
        if (str[i] == target)
        {
            if (count == nth)
                // Return the position if found
                // cout << "searching for " << target << " found at " << i << "starting pos: " << startPos << endl;
                return static_cast<int>(i);
            else
                count++;
        }
    }

    // Return -1 if the target is not found
    // cout << "searching for " << target << " not found" << endl;
    return OS::MAX;
}

ostream &operator<<(ostream &os, const OS::JSON &json)
{
    os << json.stringify();
    return os;
}
ostream &operator<<(ostream &os, const OS::Node &node)
{
    if (node.hasJSON())
    {
        os << node.key() << ": " << endl;
        os << node.child()->stringify();
    }
    else
    {
        os << node.key() << ": " << node.value();
    }
    return os;
}

inline string indent(const unsigned int &depth)
{
    string indent = "";
    for (int i = 0; i < depth; i++)
    {
        indent += "    ";
    }
    return indent;
}