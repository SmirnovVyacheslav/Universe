// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MAP_H
#define MAP_H

#include <stdexcept>
#include <unordered_map>


namespace engine
{
    template <class t_key, class t_value>
    class map
    {
    public:
        map() = default;
        ~map() = default;

        void add(const t_key key, const t_value value);
        bool contains(const t_key key);

        t_value& operator[](const t_key key);

    private:
        std::unordered_map<t_key, t_value> impl;
    };



    template <class t_key, class t_value>
    void map<t_key, t_value>::add(const t_key key, const t_value value)
    {
        impl[key] = value;
    }


    template <class t_key, class t_value>
    bool map<t_key, t_value>::contains(const t_key key)
    {
        return impl.contains(key);
    }


    template <class t_key, class t_value>
    t_value& map<t_key, t_value>::operator[](const t_key key)
    {
        if (contains(key))
        {
            return impl[key];
        }

        throw std::invalid_argument("Key does not exist");
    }
}
#endif
