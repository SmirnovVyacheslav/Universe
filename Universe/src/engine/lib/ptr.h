// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_PTR
#define ENGINE_LIB_PTR

namespace engine
{
    template <typename t>
    class ptr
    {
    public:
        ptr()  = default;
        ~ptr() = default;

        ptr(ptr&& src)      = default;
        ptr(const ptr& src) = default;

        template<typename... a>
        void init(a&&... args)
        {
            inst = new t(std::forward<a>(args)...);
        }
        void term()
        {
            //
        }

        ptr& operator=(ptr&& src)      = delete;
        ptr& operator=(const ptr& src) = delete;

        ptr& operator=(t&& src)
        {
            return *this;
        }
        ptr& operator=(const t& src)
        {
            return *this;
        }

        operator t()
        {
            return &t;
        }
        operator t() const
        {
            return &t;
        }

    private:
        t* inst;
        int refs = 0;
    };
}

#endif
