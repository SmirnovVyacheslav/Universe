// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MAP_H
#define MAP_H

#include <unordered_map>


namespace engine
{
    template <class t_key, class t_value>
    class map
    {
    public:
        map() = default;
        ~map() = default;

        bool contain(const t_key key);

    private:
        std::unordered_map<t_key, t_value> impl;
    };
}
#endif
