// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_ARRAY
#define ENGINE_LIB_ARRAY


namespace engine
{
    template <typename t>
    class array
    {
    public:
        const int size;

        array(const int size) : 
            size(size),
            data(new t[static_cast<size_t>(size)])
        {}
        ~array()
        {
            delete[] data;
        }

        array(array&& src)      = delete;
        array(const array& src) = delete;

        array& operator=(array&& src)      = delete;
        array& operator=(const array& src) = delete;

        t* operator*()
        {
            return &data;
        }
        const t* operator*() const
        {
            return &data;
        }

        t& operator[](const int index)
        {
            return data[static_cast<size_t>((size + index % size) % size)];
        }
        const t& operator[](const int index) const
        {
            return data[static_cast<size_t>((size + index % size) % size)];
        }
        
    private:
        t* const data;
    };
}

#endif
