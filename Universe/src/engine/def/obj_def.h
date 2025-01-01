// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/var/std.h"

#define obj_def \
    public: \
        obj(); \
        obj(obj&& src); \
        obj(const obj& src); \
        obj& operator=(obj&& src); \
        obj& operator=(const obj& src); \
        ~obj(); \
    private: \
        int32 id = 0;
