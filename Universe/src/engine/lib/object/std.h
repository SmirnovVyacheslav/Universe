// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_OBJECT_STD
#define ENGINE_LIB_OBJECT_STD

#include <cstdint>
#include <functional>


namespace engine
{
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using fp32 = float;
    using fp64 = double;


    uint64 hash(const int16& arg);
    uint64 hash(const int32& arg);
    uint64 hash(const int64& arg);

    uint64 hash(const uint16& arg);
    uint64 hash(const uint32& arg);
    uint64 hash(const uint64& arg);
}


namespace std
{
    template<>
    struct std::hash<engine::int16>
    {
        size_t operator()(const engine::int16& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };

    template<>
    struct std::hash<engine::int32>
    {
        size_t operator()(const engine::int32& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };

    template<>
    struct std::hash<engine::int64>
    {
        size_t operator()(const engine::int64& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };

    template<>
    struct std::hash<engine::uint16>
    {
        size_t operator()(const engine::uint16& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };

    template<>
    struct std::hash<engine::uint32>
    {
        size_t operator()(const engine::uint32& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };

    template<>
    struct std::hash<engine::uint64>
    {
        size_t operator()(const engine::uint64& arg) const
        {
            return static_cast<size_t>(engine::hash(arg));
        }
    };
}

#endif
