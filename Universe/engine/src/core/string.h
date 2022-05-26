// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <cstdint>
#include <string>


namespace engine {
    class string {
        public:
            string(const char8_t* value);
            string(const std::u8string& value);
            ~string() = default;
            string(string&& src) = default;
            string(const string& src) = default;

            std::string s_str();
            std::wstring w_str();
            std::u8string u8_str();
            std::u16string u16_str();
            std::u32string u32_str();

            string& operator=(string&& src) = default;
            string& operator=(const string& src) = default;
        private:
            std::int32_t id;
    };
}
