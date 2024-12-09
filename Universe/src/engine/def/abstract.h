// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


#define abstract \
    public: \
        obj() = default; \
    public: \
        virtual ~obj() = default; \
        obj(obj&& src) = default; \
        obj(const obj& src) = default; \
        obj& operator=(obj&& src) = default; \
        obj& operator=(const obj& src) = default;

//#define abstract \
//    protected: \
//        obj() = default; \
//        obj(obj&& src) = default; \
//        obj(const obj& src) = default; \
//    public: \
//        virtual ~obj() = default; \
//        obj& operator=(obj&& src) = default; \
//        obj& operator=(const obj& src) = default;
