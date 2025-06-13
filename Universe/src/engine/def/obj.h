// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#define obj_def \
    public: \
        obj()  = default; \
        ~obj() = default; \
        obj(obj&& src)      = default; \
        obj(const obj& src) = default; \
        obj& operator=(obj&& src)      = default; \
        obj& operator=(const obj& src) = default;
