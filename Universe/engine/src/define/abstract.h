// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


#define abstract(type) \
    protected: \
        type() = default; \
        type(type&& src) = default; \
        type(const type& src) = default; \
    public: \
        virtual ~type() = default; \
        type& operator=(type&& src) = default; \
        type& operator=(const type& src) = default;


#define abstract \
    protected: \
        obj() = default; \
        obj(obj&& src) = default; \
        obj(const obj& src) = default; \
    public: \
        virtual ~obj() = default; \
        obj& operator=(obj&& src) = default; \
        obj& operator=(const obj& src) = default;
