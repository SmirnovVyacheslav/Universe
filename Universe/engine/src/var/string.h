// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/var/std.h"

#include <string>
#include <iostream>
#include <functional>


namespace engine
{
    class string
    {
    public:
        string();
        string(const char* value);
        string(const std::string& value);
        string(const char8_t* value);
        string(const std::u8string& value);
        string(string&& src) = default;
        string(const string& src) = default;

        char* c_str() const;
        std::string s_str() const;
        std::wstring w_str() const;
        std::u8string u8_str() const;
        std::u16string u16_str() const;
        std::u32string u32_str() const;

        string& operator=(string&& src) = default;
        string& operator=(const string& src) = default;

        ~string() = default;
    private:
        uint32 id = 0;

        char* c_string;
        std::string s_string;
        std::wstring w_string;
        std::u8string u8_string;
        std::u16string u16_string;
        std::u32string u32_string;

        friend struct std::hash<engine::string>;
        friend bool operator==(const string& str_a, const string& str_b);
        friend bool operator!=(const string& str_a, const string& str_b);
        friend std::istream& operator>>(std::istream& in_stream, string& str);
        friend std::ostream& operator<<(std::ostream& out_stream, const string& str);
    };
}

namespace std
{
    template<>
    struct std::hash<engine::string>
    {
        size_t operator()(const engine::string& str) const
        {
            return static_cast<size_t>(str.id);
        }
    };
}
