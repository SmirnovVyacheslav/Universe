// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_REF
#define ENGINE_LIB_REF

namespace engine
{
    template <typename t>
    class ref
    {
    public:
        ref(t (* const get) (), void (* const set) (t)) :
            get(get),
            set(set)
        {}
        ~ref()
        {}

        ref(ref&& src)      = default;
        ref(const ref& src) = default;

        ref& operator=(ref&& src)      = delete;
        ref& operator=(const ref& src) = delete;

        ref& operator=(t&& src)
        {
            set(src);
            return *this;
        }
        ref& operator=(const t& src)
        {
            set(src);
            return *this;
        }

        operator t()
        {
            return get();
        }
        operator t() const
        {
            return get();
        }

    private:
        t (* const get) ();
        void (* const set) (t);
    };
}

#endif
