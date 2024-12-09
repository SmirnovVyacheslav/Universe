// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_VAR_PTR
#define ENGINE_VAR_PTR

namespace engine
{
    template <typename T>
    class ptr
    {
    public:
        ptr() = default;
        ptr(ptr&& src) = default;
        ptr(const ptr& src) = default;

        ptr& operator=(ptr&& src) = delete;
        ptr& operator=(const ptr& src) = delete;

        ~ptr() = default;
    private:
    };
}

#endif
