// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_DT_BASE_INT16
#define ENGINE_LIB_DT_BASE_INT16

#include <cstdint>
#include <functional>

#include "engine/lib/dt/base/uint64.h"


namespace engine::lib::dt::base
{
    using int16 = std::int16_t;

    dt::base::uint64 hash(const int16& arg);
}


namespace std
{
    template<>
    struct std::hash<engine::lib::dt::base::int16>
    {
        size_t operator()(const engine::lib::dt::base::int16& arg) const
        {
            return static_cast<size_t>(engine::lib::dt::base::hash(arg));
        }
    };
}

#endif
