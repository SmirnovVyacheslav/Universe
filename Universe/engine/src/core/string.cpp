// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "array.h"
#include "map.h"
#include "string.h"


namespace engine
{
    class string_map {
    public:
        static string_map inst;

        std::int32_t add(const std::u8string value);
        std::u8string get(const std::int32_t id);

    private:
        string_map() = default;
        ~string_map() = default;

        std::int32_t id_counter = 0;

        map<std::int32_t, std::u8string> id_str_map;
        map<std::u8string, std::int32_t> str_id_map;
        array<std::u8string> str_array;
    };

    string_map string_map::inst = string_map();

    std::int32_t string_map::add(const std::u8string value)
    {
        if (str_id_map.contains(value))
        {
            return str_id_map[value];
        }

        id_counter++;
        id_str_map.add(id_counter, value);
        str_id_map.add(value, id_counter);
        return id_counter;
    }

    std::u8string string_map::get(const std::int32_t id)
    {
        if (id_str_map.contains(id))
        {
            return id_str_map[id];
        }

        throw std::invalid_argument("Id does not exist");
    }


    string::string(const std::u8string value) :
        id(string_map::inst.add(value))
    {}

    string::~string()
    {}

    std::string string::str()
    {
        return std::string(c_str());
    }

    std::u8string string::u8_str()
    {
        return string_map::inst.get(id);
    }

    std::u16string string::u16_str()
    {
        std::u16string utf16;
        std::u32string utf32 = u32_str();

        for (std::int32_t i = 0; i < utf32.size(); ++i)
        {
            unsigned long unicode = utf32[i];
            if (unicode <= 0xFFFF)
            {
                utf16 += static_cast<char16_t>(unicode);
            }
            else
            {
                unicode -= 0x10000;
                utf16 += static_cast<char16_t>((unicode >> 10) + 0xD800);
                utf16 += static_cast<char16_t>((unicode & 0x3FF) + 0xDC00);
            }
        }
        return utf16;
    }

    std::u32string string::u32_str()
    {
        std::u32string utf32;
        std::u8string utf8 = string_map::inst.get(id);

        for (std::int32_t i = 0; i < utf8.length(); ++i) {
            unsigned char ctrl_char = static_cast<unsigned char>(utf8[i]);

            if (ctrl_char <= 0x7f)
            {
                utf32.push_back(utf8[i]);
            }
            else if (ctrl_char < 0xe0) {
                unsigned char a = utf8[i++];
                utf32.push_back(((a & 0x1f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xf0) {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                utf32.push_back(((a & 0x0f) << 12) + ((b & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xf8) {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                unsigned char c = utf8[i++];
                utf32.push_back(((a & 0x07) << 18) + ((b & 0x3f) << 12) + ((c & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xfc) {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                unsigned char c = utf8[i++];
                unsigned char d = utf8[i++];
                utf32.push_back(((a & 0x03) << 24) + ((b & 0x3f) << 18) + ((c & 0x3f) << 12) + ((d & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xfe) {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                unsigned char c = utf8[i++];
                unsigned char d = utf8[i++];
                unsigned char e = utf8[i++];
                utf32.push_back(((a & 0x01) << 30) + ((b & 0x3f) << 24) + ((c & 0x3f) << 18) + ((d & 0x3f) << 12) + ((e & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
        }

        return utf32;
    }

    const char* string::c_str()
    {
        return reinterpret_cast<const char*>(string_map::inst.get(id).c_str());
    }
}
