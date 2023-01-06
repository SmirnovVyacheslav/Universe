// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "map.h"
#include "string.h"


namespace engine {
    class string_map {
    public:
        static int_32 add(const std::u8string& value);
        static std::u8string& get(const int_32 id);
    private:
        static string_map& get_inst();

        int_32 id_counter = 0;
        map<int_32, std::u8string> id_str_map;
        map<std::u8string, int_32> str_id_map;

        string_map() = default;
        string_map(string_map&& src) = delete;
        string_map(const string_map& src) = delete;

        string_map& operator=(string_map&& src) = delete;
        string_map& operator=(const string_map& src) = delete;

        ~string_map() = default;
    };
    static string_map* string_map_inst = nullptr;


    int_32 string_map::add(const std::u8string& value) {
        string_map& inst = string_map::get_inst();
        if (inst.str_id_map.contains(value)) {
            return inst.str_id_map[value];
        }

        inst.id_counter++;
        inst.id_str_map.add(inst.id_counter, value);
        inst.str_id_map.add(value, inst.id_counter);
        return inst.id_counter;
    }
    std::u8string& string_map::get(const int_32 id) {
        string_map& inst = string_map::get_inst();
        if (inst.id_str_map.contains(id)) {
            return inst.id_str_map[id];
        }
        throw std::invalid_argument("Id does not exist");
    }
    string_map& string_map::get_inst() {
        static string_map inst;
        if (string_map_inst == nullptr) {
            string_map_inst = new string_map;
        }
        return *string_map_inst;
    }


    string::string() :
        id(string_map::add(u8"")) {
    }
    string::string(const char* value) :
        id(string_map::add(std::u8string(reinterpret_cast<const char8_t*>(value)))) {
    }
    string::string(const std::string& value) :
        id(string_map::add(std::u8string(reinterpret_cast<const char8_t*>(value.c_str())))) {
    }
    string::string(const char8_t* value) :
        id(string_map::add(std::u8string(value))) {
    }
    string::string(const std::u8string& value) :
        id(string_map::add(value)) {
    }
    std::string string::s_str() const {
        return std::string(reinterpret_cast<const char*>(string_map::get(id).c_str()));
    }
    std::wstring string::w_str() const {
        if (sizeof(wchar_t) == size_t(2)) {
            return std::wstring(reinterpret_cast<const wchar_t*>(u16_str().c_str()));
        }
        return std::wstring(reinterpret_cast<const wchar_t*>(u32_str().c_str()));
    }
    std::u8string string::u8_str() const {
        return string_map::get(id);
    }
    std::u16string string::u16_str() const {
        std::u16string utf16;
        std::u32string utf32 = u32_str();

        for (size_t i = 0; i < utf32.size(); ++i) {
            unsigned long unicode = utf32[i];
            if (unicode <= 0xFFFF) {
                utf16 += static_cast<char16_t>(unicode);
            } else {
                unicode -= 0x10000;
                utf16 += static_cast<char16_t>((unicode >> 10) + 0xD800);
                utf16 += static_cast<char16_t>((unicode & 0x3FF) + 0xDC00);
            }
        }
        return utf16;
    }
    std::u32string string::u32_str() const {
        std::u32string utf32;
        std::u8string utf8 = string_map::get(id);

        for (size_t i = 0; i < utf8.length(); ++i) {
            unsigned char ctrl_char = static_cast<unsigned char>(utf8[i]);

            if (ctrl_char <= 0x7f) {
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


    bool operator==(const string& str_a, const string& str_b) {
        return str_a.id == str_b.id;
    }
    bool operator!=(const string& str_a, const string& str_b) {
        return str_a.id != str_b.id;
    }
    std::istream& operator>>(std::istream& in_stream, string& str) {
        std::string std_str;
        in_stream >> std_str;
        str = string(reinterpret_cast<const char8_t*>(std_str.c_str()));
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const string& str) {
        return out_stream;
    }
}
