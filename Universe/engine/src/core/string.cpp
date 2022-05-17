// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "string.h"
#include "map.h"


namespace engine
{
    class string_map {
    public:
        static string_map inst;

        std::int32_t add(const std::u32string value);

    private:
        string_map() = default;
        ~string_map() = default;

        std::int32_t id_counter = 0;

        map<std::int32_t, std::u32string> id_str_map;
        map<std::u32string, std::int32_t> str_id_map;
    };

    string_map string_map::inst = string_map();

    std::int32_t string_map::add(const std::u32string value)
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


    string::string(const std::u32string value) :
        id(string_map::inst.add(value))
    {}

    string::~string()
    {}
}
