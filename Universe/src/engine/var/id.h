// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "queue.h"
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
            if (inst.q)
            {
                return inst.q.get();
            }
            return inst.idf++;
        }
        static void del(int32 idt)
        {
            id<t> inst = sobj<id<t>>::inst();
        }
    private:
        int32 idf;
        queue<int32> q;

        id()              = default;
        id(id&& src)      = delete;
        id(const id& src) = delete;

        id& operator=(id&& src)      = delete;
        id& operator=(const id& src) = delete;

        ~id() = default;
    };
}

#endif
