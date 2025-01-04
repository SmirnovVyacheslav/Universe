// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "sobj.h"
#include "std.h"

#ifndef ENGINE_VAR_ID
#define ENGINE_VAR_ID

namespace engine
{
    template <typename t>
    class id
    {
    public:
        static int32 get()
        {
            id<t> inst = sobj<id<t>>::inst();
            return 0;
        }
    private:
        id()              = default;
        id(id&& src)      = delete;
        id(const id& src) = delete;

        id& operator=(id&& src)      = delete;
        id& operator=(const id& src) = delete;

        ~id() = default;
    };
}

#endif
