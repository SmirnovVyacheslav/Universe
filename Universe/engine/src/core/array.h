// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <cstdint>


namespace engine
{
    template <class type>
    class array
    {
    public:
        array(const std::int32_t size = 0);
        ~array() = default;

        void append(type& item);

        type& operator[](const std::int32_t index);

    private:
        std::vector<type> impl;
    };


    template <class type>
    array<type>::array(const std::int32_t size)
    {
        impl.reserve(size);
    }


    template <class type>
    void array<type>::append(type& item)
    {
        impl.push_back(item);
    }


    template <class type>
    type& array<type>::operator[](const std::int32_t index)
    {
        std::int32_t size = impl.size();
        return impl[(size + index % size) % size];
    }
}
#endif
