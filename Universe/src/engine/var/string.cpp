// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_string.h"


namespace engine
{
    uint32 sid = 0;


    string::string() : id(sid++), str(u8"")
    {}

    string::string(const char* str) :
        id(sid++),
        str(std::u8string(reinterpret_cast<const char8_t*>(str)))
    {}

    string::string(const std::string& str) :
        id(sid++),
        str(std::u8string(reinterpret_cast<const char8_t*>(str.c_str())))
    {}

    string::string(const char8_t* str) :
        id(sid++),
        str(std::u8string(str))
    {}

    string::string(const std::u8string& str) :
        id(sid++),
        str(str)
    {}

    const char* string::c_str() const
    {
        return reinterpret_cast<const char*>(str.c_str());
    }

    std::string string::s_str() const
    {
        return std::string(c_str());
    }

    std::wstring string::w_str() const
    {
        if (sizeof(wchar_t) == size_t(2))
        {
            return std::wstring(reinterpret_cast<const wchar_t*>(u16_str().c_str()));
        }
        return std::wstring(reinterpret_cast<const wchar_t*>(u32_str().c_str()));
    }

    std::u8string string::u8_str() const
    {
        return str;
    }

    std::u16string string::u16_str() const
    {
        std::u16string utf16;
        std::u32string utf32 = u32_str();

        for (size_t i = 0; i < utf32.size(); ++i)
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

    std::u32string string::u32_str() const
    {
        std::u32string utf32;
        std::u8string utf8 = str;

        for (size_t i = 0; i < utf8.length(); ++i)
        {
            unsigned char ctrl_char = static_cast<unsigned char>(utf8[i]);

            if (ctrl_char <= 0x7f)
            {
                utf32.push_back(utf8[i]);
            }
            else if (ctrl_char < 0xe0)
            {
                unsigned char a = utf8[i++];
                utf32.push_back(((a & 0x1f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xf0)
            {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                utf32.push_back(((a & 0x0f) << 12) + ((b & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xf8)
            {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                unsigned char c = utf8[i++];
                utf32.push_back(((a & 0x07) << 18) + ((b & 0x3f) << 12) + ((c & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xfc)
            {
                unsigned char a = utf8[i++];
                unsigned char b = utf8[i++];
                unsigned char c = utf8[i++];
                unsigned char d = utf8[i++];
                utf32.push_back(((a & 0x03) << 24) + ((b & 0x3f) << 18) + ((c & 0x3f) << 12) + ((d & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (ctrl_char < 0xfe)
            {
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


    bool operator==(const string& str_a, const string& str_b)
    {
        // return str_a.id == str_b.id;
        return str_a.u8_str() == str_b.u8_str();
    }

    bool operator!=(const string& str_a, const string& str_b)
    {
        return !(str_a == str_b);
    }

    std::istream& operator>>(std::istream& in_stream, string& str)
    {
        std::string std_str;
        in_stream >> std_str;
        str = string(std_str);
        return in_stream;
    }

    std::ostream& operator<<(std::ostream& out_stream, const string& str)
    {
        return out_stream;
    }
}
