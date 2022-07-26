// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <stdexcept>
#include <unordered_map>


namespace engine {
    template <class type_name_key, class type_name_value>
    class map {
        public:
            map() = default;
            ~map() = default;
            map(map&& src) = default;
            map(const map& src) = default;

            bool contains(const type_name_key& key);
            void add(type_name_key&& key, type_name_value&& value);
            void add(const type_name_key& key, const type_name_value& value);

            map& operator=(map&& src) = default;
            map& operator=(const map& src) = default;
            type_name_value& operator[](const type_name_key& key);
        private:
            std::unordered_map<type_name_key, type_name_value> data;
    };


    template <class type_name_key, class type_name_value>
    bool map<type_name_key, type_name_value>::contains(const type_name_key& key) {
        return data.contains(key);
    }
    template <class type_name_key, class type_name_value>
    void map<type_name_key, type_name_value>::add(type_name_key&& key, type_name_value&& value) {
        data[std::move(key)] = std::move(value);
    }
    template <class type_name_key, class type_name_value>
    void map<type_name_key, type_name_value>::add(const type_name_key& key, const type_name_value& value) {
        data[key] = value;
    }
    template <class type_name_key, class type_name_value>
    type_name_value& map<type_name_key, type_name_value>::operator[](const type_name_key& key) {
        if (contains(key)) {
            return data[key];
        }
        throw std::invalid_argument("Key does not exist");
    }
}
