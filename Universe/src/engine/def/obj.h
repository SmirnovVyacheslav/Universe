// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#define obj_def \
    public: \
        obj();  \
        ~obj(); \
        obj(obj&& src) noexcept;      \
        obj(const obj& src) noexcept; \
        obj& operator=(obj&& src)      = delete; \
        obj& operator=(const obj& src) = delete;
