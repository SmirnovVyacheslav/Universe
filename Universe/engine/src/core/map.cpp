// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "map.h"


namespace engine
{
    template <class t_key, class t_value>
    bool map<t_key, t_value>::contain(const t_key key)
    {
        return impl[key] ? true : false;
    }
}
