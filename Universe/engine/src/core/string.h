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
        string(const std::u8string value);
        ~string();

        std::string str();
        std::u8string u8_str();
        std::u16string u16_str();
        std::u32string u32_str();

        const char* c_str();

    private:
        const std::int32_t id;
    };
}
#endif
