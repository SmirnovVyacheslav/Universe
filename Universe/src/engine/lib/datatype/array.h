// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_LIB_DATATYPE_ARRAY
#define ENGINE_LIB_DATATYPE_ARRAY

#include <vector>

#include "engine/lib/datatype/std.h"


namespace engine
{
    template <typename t>
    class array
    {
    public:
        array(uint32 size = 0)
        {
            data.reserve(static_cast<size_t>(size));
        }
        array(array&& src)      = default;
        array(const array& src) = default;

        uint32 size() const
        {
            return static_cast<uint32>(data.size());
        }
        void append(T&& item)
        {
            data.push_back(std::move(item));
        }
        void append(const T& item)
        {
            data.push_back(item);
        }
        uint32 find_index(const T& item)
        {
            for (uint32 i = 0; i < size(); ++i)
            {
                if (data[static_cast<size_t>(i)] == item)
                {
                    return i;
                }
            }
            // error
        }

        array& operator=(array&& src_ptr)      = default;
        array& operator=(const array& src_ptr) = default;

        t& operator[](const int32 index)
        {
            return data[(size() + index % size()) % size()];
        }
        const T& operator[](const int32 index) const
        {
            return data[(size() + index % size()) % size()];
        }

        T* operator*()
        {
            return &data.front();
        }
        const T* operator*() const
        {
            return &data.front();
        }

        ~array() = default;
    private:
        std::vector<t> data;
    };
}

#endif
