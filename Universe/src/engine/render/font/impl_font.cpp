// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_font.h"


namespace engine::render::font
{
    impl::impl(string name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.font.u8_str() + name.u8_str() + u8".fnt");

        string str;
        /*while ((ifstream >> str) && (str != string(u8"index")));
        if (str != string(u8"index")) {
            throw error("Incorrect file format");
        }*/
    }
}
