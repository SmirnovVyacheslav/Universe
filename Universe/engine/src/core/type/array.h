// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <vector>
#include <stdexcept>

#include "src/core/def/class_format.h"

#include "src/core/type/std.h"


namespace engine
{
    template <typename T>
    class array
    {
        ____________________public____________________
        array(int32 size = 0);
        array(array&& src) = default;
        array(const array& src) = default;

        int32 size() const;
        void append(T&& item);
        void append(const T& item);
        int32 find_index(const T& item);

        array& operator=(array&& src_ptr) = default;
        array& operator=(const array& src_ptr) = default;
        T& operator[](const int32 index);
        const T& operator[](const int32 index) const;

        ~array() = default;
        ____________________private___________________
        std::vector<T> data;
    };


    // array (int32 size) -> int32
    template <typename T>
    array<T>::array(int32 size)
    {
        if (size < 0)
        {
            throw std::invalid_argument("Negative array size");
        }
        data.reserve(static_cast<size_t>(size));
    }

    // size const () -> int32
    template<typename T>
    int32 array<T>::size() const
    {
        return static_cast<int32>(data.size());
    }

    // append (T&& item) -> void
    template <typename T>
    void array<T>::append(T&& item)
    {
        data.push_back(std::move(item));
    }

    // append (const T& item) -> void
    template <typename T>
    void array<T>::append(const T& item)
    {
        data.push_back(item);
    }

    // find_index (const T& item) -> int32
    template<typename T>
    int32 array<T>::find_index(const T& item)
    {
        for (int32 i = 0; i < size(); ++i)
        {
            if (data[static_cast<size_t>(i)] == item)
            {
                return i;
            }
        }
        throw std::invalid_argument("Item does not exist");
    }

    // [] (const int32 index) -> T&
    template <typename T>
    T& array<T>::operator[](const int32 index)
    {
        return data[(size() + index % size()) % size()];
    }

    // [] const (const int32 index) -> const T&
    template <typename T>
    const T& array<T>::operator[](const int32 index) const
    {
        return data[(size() + index % size()) % size()];
    }
}
