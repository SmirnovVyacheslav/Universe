// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_error.h"


namespace engine
{
    error::error(const char* message) : message(message)
    {}

    const char* error::what()
    {
        return message;
    }
}
