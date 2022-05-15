// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "string.h"


namespace engine
{
    class string_map {
    public:
        static string_map inst;

    private:
        string_map() = default;
        ~string_map() = default;
    };

    string_map string_map::inst = string_map();
}
