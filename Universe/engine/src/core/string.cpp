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


    /*class string_converter
    {
    public:
        static std::string u32_u8(const std::u32string str);
        static std::u16string u32_u16(const std::u32string str);

    private:
        string_converter() = default;
        ~string_converter() = default;
    };

    std::string string_converter::u32_u8(const std::u32string str)
    {
        return std::string();
    }

    std::u16string string_converter::u32_u16(const std::u32string str)
    {
        return std::u16string();
    }*/


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
        return std::u16string();
    }

    std::u32string string::u32_str()
    {
        return std::u32string();
    }

    const char* string::c_str()
    {
        return reinterpret_cast<const char*>(string_map::inst.get(id).c_str());
    }
}
