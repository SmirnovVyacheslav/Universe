// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef STRING_H
#define STRING_H

#include <cstdint>


namespace engine
{
    class string
    {
    public:
        string() = default;
        ~string() = default;

    private:
        std::int32_t id;
    };
}
#endif
