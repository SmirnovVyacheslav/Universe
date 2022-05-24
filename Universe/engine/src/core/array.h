// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <vector>
#include <cstdint>


namespace engine {
    template <class type_name>
    class array {
        public:
            explicit array(size_t size = 0);
            ~array() = default;

            array(array&& src) = default;
            array(const array& src) = default;

            array& operator=(array&& src_ptr) = default;
            array& operator=(const array& src_ptr) = default;

            type_name& operator[](std::int32_t index);

            void append(type_name&& item);
            void append(const type_name& item);
        private:
            std::vector<type_name> data;
    };


    template <class type_name>
    array<type_name>::array(size_t size) {
        data.reserve(size);
    }
    template <class type_name>
    type_name& array<type_name>::operator[](std::int32_t index) {
        std::int32_t size = static_cast<std::int32_t>(data.size());
        return data[(size + index % size) % size];
    }
    template <class type_name>
    void array<type_name>::append(type_name&& item) {
        data.push_back(std::move(item));
    }
    template <class type_name>
    void array<type_name>::append(const type_name& item) {
        data.push_back(item);
    }
}
