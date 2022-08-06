// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
 #pragma once
 #include "std.h"
 #include <stdexcept>
 #include <vector>


 namespace engine {
     template <class type_name>
     class array {
         public:
             array(int_32 size = 0);
             array(array&& src) = default;
             array(const array& src) = default;

             int_32 size() const;
             void append(type_name&& item);
             void append(const type_name& item);
             int_32 find_index(const type_name& item);

             array& operator=(array&& src_ptr) = default;
             array& operator=(const array& src_ptr) = default;
             type_name& operator[](const int_32 index);
             const type_name& operator[](const int_32 index) const;

             ~array() = default;
         private:
             std::vector<type_name> data;
     };


    template <class type_name>
    array<type_name>::array(int_32 size) {
        if (size < 0) {
            throw std::invalid_argument("Negative array size");
        }
        data.reserve(static_cast<size_t>(size));
    }
    template<class type_name>
    int_32 array<type_name>::size() const {
        return static_cast<int_32>(data.size());
    }
    template <class type_name>
    void array<type_name>::append(type_name&& item) {
        data.push_back(std::move(item));
    }
    template <class type_name>
    void array<type_name>::append(const type_name& item) {
        data.push_back(item);
    }
    template<class type_name>
    int_32 array<type_name>::find_index(const type_name& item) {
        for (int_32 i = 0; i < size(); ++i) {
            if (data[static_cast<size_t>(i)] == item) {
                return i;
            }
        }
        throw std::invalid_argument("Item does not exist");
    }
    template <class type_name>
    type_name& array<type_name>::operator[](const int_32 index) {
        return data[(size() + index % size()) % size()];
    }
    template <class type_name>
    const type_name& array<type_name>::operator[](const int_32 index) const {
        return data[(size() + index % size()) % size()];
    }
}
