// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "map.h"
#include "ptr.h"
#include "sobj.h"
#include "std.h"

#ifndef ENGINE_VAR_SET
#define ENGINE_VAR_SET

namespace engine
{
    template <typename t, typename a1 = int32, typename a2 = int32, typename a3 = int32>
    class set
    {
    public:
        static int32 add()
        {
            set<t, a1, a2, a3> inst = sobj<set<t, a1, a2, a3>>::inst();
            
            int32 id = static_cast<int32>(std::hash<t>());
            
        }
        static int32 add(a1 arg1)
        {
            //
        }
        static int32 add(a1 arg1, a2 arg2)
        {
            //
        }
        static int32 add(a1 arg1, a2 arg2, a3 arg3)
        {
            //
        }
        static ref<t> get(int32 id)
        {
            //
        }
        static void del(int32 id)
        {
            //
        }
    private:
        map<int32, ptr<t>> id_t_map;

        map<int32, int32>                           arg1_id_map;
        map<int32, map<int32, int32> >              arg2_id_map;
        map<int32, map<int32, map<int32, int32> > > arg3_id_map;

        set()               = default;
        set(set&& src)      = delete;
        set(const set& src) = delete;

        set& operator=(set&& src)      = delete;
        set& operator=(const set& src) = delete;

        ~set() = default;
    };
}

#endif
