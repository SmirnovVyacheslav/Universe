// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "std.h"


namespace engine
{
    uint64 hash(const int16& arg)
    {
        return static_cast<uint64>(arg);
    }

    uint64 hash(const int32& arg)
    {
        return static_cast<uint64>(arg);
    }

    uint64 hash(const int64& arg)
    {
        return static_cast<uint64>(arg);
    }


    uint64 hash(const uint16& arg)
    {
        return static_cast<uint64>(arg);
    }

    uint64 hash(const uint32& arg)
    {
        return static_cast<uint64>(arg);
    }

    uint64 hash(const uint64& arg)
    {
        return static_cast<uint64>(arg);
    }
}
