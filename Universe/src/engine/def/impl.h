// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#define impl_def \
    public: \
        impl()  = default; \
        ~impl() = default; \
        impl(impl&& src)      = default; \
        impl(const impl& src) = default; \
        impl& operator=(impl&& src)      = default; \
        impl& operator=(const impl& src) = default;
