// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_DT_BASE_UINT64
#define ENGINE_LIB_DT_BASE_UINT64

#include <cstdint>
#include <functional>


namespace engine::lib::dt::base
{
    using uint64 = std::uint64_t;

    dt::base::uint64 hash(const uint64& arg);
}


namespace std
{
    template<>
    struct std::hash<engine::lib::dt::base::uint64>
    {
        size_t operator()(const engine::lib::dt::base::uint64& arg) const
        {
            return static_cast<size_t>(engine::lib::dt::base::hash(arg));
        }
    };
}

#endif
