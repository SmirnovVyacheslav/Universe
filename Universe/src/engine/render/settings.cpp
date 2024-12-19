// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "settings.h"

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
        static int32 add();
        static obj& get(int32 id);
        static void del(int32 id);
    private:
        static set* set_inst = nullptr;
        map<int32, obj*> id_obj_map;
        map<int32, int32> arg_id_map;

        mng() = default;
        mng(mng&& src) = delete;
        mng(const mng& src) = delete;

        mng& operator=(mng&& src) = delete;
        mng& operator=(const mng& src) = delete;

        ~mng() = default;
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
