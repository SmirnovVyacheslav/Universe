// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#define impl_def \
    public: \
        impl()  = default; \
        ~impl() = default; \
        impl(impl&& src)      = delete; \
        impl(const impl& src) = delete; \
        impl& operator=(impl&& src)      = delete; \
        impl& operator=(const impl& src) = delete;
