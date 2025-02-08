// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include <cstdint>
#include <functional>

#ifndef ENGINE_STD
#define ENGINE_STD

namespace engine::lib::dt::base
{
    using uint32 = std::uint32_t;

    /*template<>
    struct hash<uint32>
    {
        size_t operator()(const uint32& arg) const
        {
            return static_cast<size_t>(arg);
        }
    };*/
}

#endif
