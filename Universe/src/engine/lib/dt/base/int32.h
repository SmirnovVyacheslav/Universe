// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_DT_BASE_INT32
#define ENGINE_LIB_DT_BASE_INT32

#include <cstdint>
#include <functional>

#include "engine/lib/dt/base/uint64.h"


namespace engine::lib::dt::base
{
    using int32 = std::int32_t;

    dt::base::uint64 hash(const int32& arg);
}


namespace std
{
    template<>
    struct std::hash<engine::lib::dt::base::int32>
    {
        size_t operator()(const engine::lib::dt::base::int32& arg) const
        {
            return static_cast<size_t>(engine::lib::dt::base::hash(arg));
        }
    };
}

#endif
