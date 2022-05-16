// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef STRING_H
#define STRING_H

#include <cstdint>
#include <string>


namespace engine
{
    class string
    {
    public:
        string(const std::u32string value);
        ~string();

    private:
        const std::int32_t id;
    };
}
#endif
