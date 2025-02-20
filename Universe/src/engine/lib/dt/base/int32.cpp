// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "int32.h"


namespace engine::lib::dt::base
{
    dt::base::uint64 hash(const int32& arg)
    {
        return static_cast<dt::base::uint64>(arg);
    }
}
