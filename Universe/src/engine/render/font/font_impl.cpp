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

        /*size_t index;
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
            else if(data == "char")
            {
                uint16 id = 0;
                char_data chard;

                while(!sstream.eof())
                {
                    sstream >> data;
                    index = data.find('=');
                    key = data.substr(0, index);
                    value = data.substr(index + 1);

                    std::stringstream vsstream;
                    vsstream << value;
                    if(key == "id")
                    {
                        vsstream >> id;
                    }
                    else if(key == "x")
                    {
                        vsstream >> chard.x;
                    }
                    else if(key == "y")
                    {
                        vsstream >> chard.y;
                    }
                    else if(key == "width")
                    {
                        vsstream >> chard.w;
                    }
                    else if(key == "height")
                    {
                        vsstream >> chard.h;
                    }
                    else if(key == "xoffset")
                    {
                        vsstream >> chard.ox;
                    }
                    else if(key == "yoffset")
                    {
                        vsstream >> chard.oy;
                    }
                    else if(key == "xadvance")
                    {
                        vsstream >> chard.ax;
                    }
                    char_map[id] = chard;
                }
            }
        }*/

        ifstream.close();
    }
}
