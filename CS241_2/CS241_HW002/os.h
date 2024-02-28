#ifndef MY_OS_H
#define MY_OS_H

#include "json.h"

namespace OS
{
    const string DEFAULT_OS_PATH = "os/";
    const int DEFAULT_HASH_SEED = 131;
    const int EXTENSION_HASH_SEED = 443;

    string strHash(const string &str, int seed = EXTENSION_HASH_SEED);

    string currentTime();
}

#endif // OS_H