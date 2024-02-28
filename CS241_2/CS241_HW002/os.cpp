#include "os.h"

namespace OS
{

    string strHash(const string &str, int seed)
    {
        int hash_size = 11;
        string hash = "";
        unsigned int buffer = 0;
        for (int i = 0; i < hash_size; i++)
        {
            buffer = 0;
            for (int j = 0; j < str.length(); j++)
            {
                buffer += str[j] * (i * i) * str[j / 2];
                buffer += (buffer << i);
                buffer += (seed + 1) * ((j + 1) * (i + 1));
                buffer ^= (buffer >> (j + i));
                buffer /= (i + 1 + seed);
                buffer += (str.length() - j) * i * str[j];
            }
            buffer = (buffer % 9) + 1;
            hash += to_string(buffer);
        }
        return hash;
    }

    string currentTime()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
}