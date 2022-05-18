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
        array(std::int32_t size = 0);
        ~array() = default;

        void append(const type& item);

        type& operator[](const std::int32_t index);

    private:
        std::vector<type> impl;
    };


    template <class type>
    array<type>::array(std::int32_t size)
    {
        impl.reserve(size);
    }


    template <class type>
    void array<type>::append(const type& item)
    {
        impl.push_back(item);
    }


    template <class type>
    type& array<type>::operator[](const std::int32_t index)
    {
        return impl[(impl.size() + index % impl.size()) % impl.size()];
    }
}
#endif
