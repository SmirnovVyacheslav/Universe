// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/var/std.h"

#define obj_api \
    private: \
        int32 id; \
        obj(int32 id) : id(id) {}; \
        friend obj get(); \
    public: \
        obj(obj&& src) = default; \
        obj(const obj& src) = default; \
        obj& operator=(obj&& src) = default; \
        obj& operator=(const obj& src) = default; \
        ~obj();
