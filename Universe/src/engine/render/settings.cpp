// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "settings.h"

#include "engine/var/ptr.h"
#include "engine/var/sobj.h"

namespace engine::render::settings
{
    obj* inst = nullptr;


    obj& get()
    {
        if (!inst)
        {
            inst = new obj;
        }

        return *inst;
    }

    /*class impl
    {
    public:
        impl() = default;
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl() = default;
    };

    class set
    {
    public:
        static int32     add();
        static ref<impl> get(int32 id);
        static void      del(int32 id);
    private:
        map<int32, int32>     arg_id_map;
        map<int32, ptr<impl>> id_impl_map;

        set()               = default;
        set(set&& src)      = delete;
        set(const set& src) = delete;

        set& operator=(set&& src)      = delete;
        set& operator=(const set& src) = delete;

        ~set() = default;
    };

    obj get()
    {
        if (!inst)
        {
            inst = new impl;
        }

        return *inst;
    }*/
}
