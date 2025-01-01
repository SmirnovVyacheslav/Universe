// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/var/ptr.h"

#define set_def                                  \
    public:                                      \
        static int32     add();                  \
        static ref<impl> get(int32 id);          \
        static void      del(int32 id);          \
    private:                                     \
        map<int32, int32>     arg_id_map;        \
        map<int32, ptr<impl>> id_impl_map;       \
                                                 \
        set()               = default;           \
        set(set&& src)      = delete;            \
        set(const set& src) = delete;            \
                                                 \
        set& operator=(set&& src)      = delete; \
        set& operator=(const set& src) = delete; \
                                                 \
        ~set() = default;
