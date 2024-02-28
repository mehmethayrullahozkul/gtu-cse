#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "json.h"
#include "shell.h"

using namespace OS;

int main()
{

    try
    {
        Shell shell;
        shell.run();
    }
    catch (const Exception &e)
    {
        cout << "exception: " << e.message() << e.type() << endl;
    }

    return 0;
}