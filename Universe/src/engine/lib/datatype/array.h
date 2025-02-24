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

        t& operator[](const int32 index)
        {
            return data[static_cast<size_t>((size() + index % size()) % size())];
        }
        const t& operator[](const int32 index) const
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

        ~array() = default;
    private:
        std::vector<t> data;
    };
}

#endif
