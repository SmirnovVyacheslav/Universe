// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_ARRAY
#define ENGINE_LIB_ARRAY


namespace engine
{
    template <typename t>
    class array
    {
    public:
        array(int size)
        {
            //
        }
        /*array(int size = 0)
        {
            data.reserve(static_cast<size_t>(size));
        }
        array(array&& src)      = default;
        array(const array& src) = default;

        int size() const
        {
            return static_cast<int>(data.size());
        }
        void append(t&& item)
        {
            data.push_back(std::move(item));
        }
        void append(const t& item)
        {
            data.push_back(item);
        }

        array& operator=(array&& src)      = default;
        array& operator=(const array& src) = default;

        t& operator[](const int index)
        {
            return data[static_cast<size_t>((size() + index % size()) % size())];
        }
        const t& operator[](const int index) const
        {
            return data[static_cast<size_t>((size() + index % size()) % size())];
        }

        t* operator*()
        {
            return &data.front();
        }
        const t* operator*() const
        {
            return &data.front();
        }

        ~array() = default;*/
    private:
    };
}

#endif
