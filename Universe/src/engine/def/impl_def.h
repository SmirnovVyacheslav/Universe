// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/var/std.h"

#define impl_def \
    public: \
        impl(); \
        impl(impl&& src)      = delete; \
        impl(const impl& src) = delete; \
        impl& operator=(impl&& src)      = delete; \
        impl& operator=(const impl& src) = delete; \
        ~impl(); \
    private: \
        int32 id = 0;
