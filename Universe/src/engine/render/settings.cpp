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

    class ref
    {
    public:
        mng() = default;
        mng(mng&& src) = delete;
        mng(const mng& src) = delete;

        mng& operator=(mng&& src) = delete;
        mng& operator=(const mng& src) = delete;
        obj& operator[](const int32 id);
        const obj& operator[](const int32 id) const;

        ~mng() = default;

    private:
        obj* inst = nullptr;
        mng* inst = nullptr;
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
