// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "uint16.h"


namespace engine::lib::dt::base
{
    dt::base::uint64 hash(const uint16& arg)
    {
        return static_cast<dt::base::uint64>(arg);
    }
}
