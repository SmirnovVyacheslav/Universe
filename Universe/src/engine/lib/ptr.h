// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include <utility>

#ifndef ENGINE_LIB_PTR
#define ENGINE_LIB_PTR

namespace engine
{
    template <typename t>
    class ptr
    {
    public:
        ptr()
        {}
        ~ptr()
        {
            delete inst;
        }

        ptr(ptr&& src)      = delete;
        ptr(const ptr& src) = delete;

        template<typename... a>
        void init(a&&... args)
        {
            if (inst == nullptr)
            {
                inst = new t(std::forward<a>(args)...);
            }
            ++refs;
        }
        void term()
        {
            --refs;
            if (refs == 0)
            {
                delete inst;
            }
        }

        ptr& operator=(ptr&& src)      = delete;
        ptr& operator=(const ptr& src) = delete;

        t* operator->()
        {
            return inst;
        }
        t* operator->() const
        {
            return inst;
        }

    private:
        int refs = 0;
        t*  inst = nullptr;
    };
}

#endif
