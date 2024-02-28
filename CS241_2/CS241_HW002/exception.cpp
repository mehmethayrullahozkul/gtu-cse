#include "exception.h"

namespace OS
{

    Exception::Exception(const std::string &_message, ExceptionType _type)
        : e_message(_message), e_type(_type) {}

    const std::string &Exception::message() const
    {
        return e_message;
    }

    ExceptionType Exception::type() const
    {
        return e_type;
    }

}

ostream &operator<<(ostream &os, const OS::Exception &e)
{
    os << e.message() << " (" << e.type() << ")";
    return os;
}

ostream &operator<<(ostream &os, const OS::ExceptionType &type)
{
    switch (type)
    {
    case OS::ExceptionType::General:
        os << "general";
        break;
    case OS::ExceptionType::JSON:
        os << "JSON";
        break;
    case OS::ExceptionType::Shell:
        os << "shell";
        break;
    case OS::ExceptionType::RegularFile:
        os << "regularfile";
        break;
    case OS::ExceptionType::Directory:
        os << "directory";
        break;
    case OS::ExceptionType::Link:
        os << "link";
        break;
    case OS::ExceptionType::File:
        os << "file";
        break;
    default:
        os << "unknown";
        break;
    }
    return os;
}
