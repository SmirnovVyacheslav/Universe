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

        std::string u8();
        std::u16string u16();
        std::u32string u32();

    private:
        const std::int32_t id;
    };
}
#endif
