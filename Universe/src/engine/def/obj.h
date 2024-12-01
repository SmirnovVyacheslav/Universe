// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#define obj_api \
    private: \
        int32 id; \
        obj(int32 id) : id(id) {}; \
        friend obj& get(); \
    public: \
        obj(obj&& src) = default; \
        obj(const obj& src) = default; \
        obj& operator=(obj&& src) = default; \
        obj& operator=(const obj& src) = default; \
        ~obj() { mng_inst->del(); }
