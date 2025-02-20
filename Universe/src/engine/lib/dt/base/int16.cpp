// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "int16.h"


namespace engine::lib::dt::base
{
    dt::base::uint64 hash(const int16& arg)
    {
        return static_cast<dt::base::uint64>(arg);
    }
}
