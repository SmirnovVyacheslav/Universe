// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <stdexcept>
#include <vector>

#include "std.h"


namespace engine {
    template <typename T>
    class array {
        public:
            array(int_32 size = 0);
            array(array&& src) = default;
            array(const array& src) = default;

            int_32 size() const;
            void append(T&& item);
            void append(const T& item);
            int_32 find_index(const T& item);

            array& operator=(array&& src_ptr) = default;
            array& operator=(const array& src_ptr) = default;
            T& operator[](const int_32 index);
            const T& operator[](const int_32 index) const;

            ~array() = default;
        private:
            std::vector<T> data;
    };


    template <typename T>
    array<T>::array(int_32 size) {
        if (size < 0) {
            throw std::invalid_argument("Negative array size");
        }
        data.reserve(static_cast<size_t>(size));
    }
    template<typename T>
    int_32 array<T>::size() const {
        return static_cast<int_32>(data.size());
    }
    template <typename T>
    void array<T>::append(T&& item) {
        data.push_back(std::move(item));
    }
    template <typename T>
    void array<T>::append(const T& item) {
        data.push_back(item);
    }
    template<typename T>
    int_32 array<T>::find_index(const T& item) {
        for (int_32 i = 0; i < size(); ++i) {
            if (data[static_cast<size_t>(i)] == item) {
                return i;
            }
        }
        throw std::invalid_argument("Item does not exist");
    }
    template <typename T>
    T& array<T>::operator[](const int_32 index) {
        return data[(size() + index % size()) % size()];
    }
    template <typename T>
    const T& array<T>::operator[](const int_32 index) const {
        return data[(size() + index % size()) % size()];
    }
}
