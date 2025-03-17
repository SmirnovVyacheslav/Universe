// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "sys.h"

#include <cstdlib>
#include <iostream>
#include <fstream>


namespace engine
{
    void exit(const char* msg) noexcept
    {
        std::ofstream crash_file;
        crash_file.open("crash.log");
        crash_file <<  "ERROR: " << msg << std::endl;
        crash_file.close();

        std::exit(-1);
    }
}
