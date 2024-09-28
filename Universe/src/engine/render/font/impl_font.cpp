// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_font.h"


namespace engine::render::font
{
    impl::impl(string name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.font.u8_str() + name.u8_str() + u8".fnt");

        size_t index;
        std::string line, data, key, value;
        while(!ifstream.eof())
        {
            std::stringstream sstream;
		    std::getline(ifstream, line);
            sstream << line;

            sstream >> data;
            if(data == "common")
            {
                while(!sstream.eof())
                {
                    sstream >> data;
                    index = data.find('=');
                    key = data.substr(0, index);
                    value = data.substr(index + 1);

                    std::stringstream vsstream;
                    vsstream << value;
                    if(key == "scaleW")
                    {
                        vsstream >> tex_width;
                    }
                    else if(key == "scaleH")
                    {
                        vsstream >> tex_height;
                    }
                }
            }
        }

        ifstream.close();
    }
}
