// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "map.h"

#include <stdexcept>


namespace engine
{
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
    t_value& map<t_key, t_value>::operator[](const t_key key) const
    {
        if (contains(key))
        {
            return impl[key];
        }

        throw std::invalid_argument(U"Key does not exist");
    }
}
