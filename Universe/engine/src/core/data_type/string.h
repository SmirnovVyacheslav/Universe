// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
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

            std::string s_str() const;
            std::wstring w_str() const;
            std::u8string u8_str() const;
            std::u16string u16_str() const;
            std::u32string u32_str() const;

            string& operator=(string&& src) = default;
            string& operator=(const string& src) = default;
        private:
            string() = delete;
            std::int32_t id = -1;
    };
}
