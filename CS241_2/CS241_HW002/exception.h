#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

namespace OS
{
    enum class ExceptionType
    {
        General,
        JSON,
        Shell,
        RegularFile,
        Directory,
        Link,
        File
    };

    class Exception
    {
    public:
        Exception(const std::string &_message, ExceptionType _type = ExceptionType::General);

        const std::string &message() const;

        ExceptionType type() const;

    private:
        std::string e_message;
        ExceptionType e_type;
    };
}

ostream &operator<<(ostream &os, const OS::Exception &e);

ostream &operator<<(ostream &os, const OS::ExceptionType &type);

#endif // EXCEPTION_H