// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_DP_HASH
#define ENGINE_LIB_DP_HASH

#include <functional>

#include "engine/lib/dt/base/uint32.h"


namespace engine::lib::dp
{
    template<typename t>
    struct hash
    {
        dt::base::uint32 operator()(const t& arg) const
        {
            return static_cast<dt::base::uint32>(arg);
        }
    };
}

#endif
