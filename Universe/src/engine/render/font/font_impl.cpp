// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "font_impl.h"

#include "engine/render/settings/api_settings.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace engine::render::font
{
    impl::impl(string name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.font.u8_str() + name.u8_str() + u8".fnt");

        size_t index;
        std::string line, item, key, value;
        while(!ifstream.eof())
        {
            std::stringstream sstream;
		    std::getline(ifstream, line);
            sstream << line;

            sstream >> item;
            if(item == "common")
            {
                while(!sstream.eof())
                {
                    sstream >> item;
                    index = item.find('=');
                    key = item.substr(0, index);
                    value = item.substr(index + 1);

                    std::stringstream vsstream;
                    vsstream << value;
                    if(key == "scaleW")
                    {
                        vsstream >> char_width;
                    }
                    else if(key == "scaleH")
                    {
                        vsstream >> char_height;
                    }
                }
            }
            else if(item == "char")
            {
                uint16 id = 0;
                char_data data;

                while(!sstream.eof())
                {
                    sstream >> item;
                    index = item.find('=');
                    key = item.substr(0, index);
                    value = item.substr(index + 1);

                    std::stringstream vsstream;
                    vsstream << value;
                    if(key == "id")
                    {
                        vsstream >> id;
                    }
                    else if(key == "x")
                    {
                        vsstream >> data.pos_x;
                    }
                    else if(key == "y")
                    {
                        vsstream >> data.pos_y;
                    }
                    else if(key == "width")
                    {
                        vsstream >> data.size_w;
                    }
                    else if(key == "height")
                    {
                        vsstream >> data.size_h;
                    }
                    else if(key == "xoffset")
                    {
                        vsstream >> data.offset_x;
                    }
                    else if(key == "yoffset")
                    {
                        vsstream >> data.offset_y;
                    }
                    else if(key == "xadvance")
                    {
                        vsstream >> data.advance_x;
                    }
                    char_map[id] = data;
                }
            }
        }

        ifstream.close();
    }
}
