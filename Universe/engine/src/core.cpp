/******************************************************************************
     * File: core.cpp
     * Description: Engine Core Systems
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include <string>
#include <memory>

#include "../include/engine.h"
#include "platform.h"

namespace engine
{
    // platform detection - compile on target

    // 

    class t_engine{}; // config path, create config

    class t_window{}; // window props, map on config - res, mode, devices, pos

    class t_user{}; // users, assosiate config, devices, game settings

    class t_manager{}; //window manager or other manager - create, delete, get
    // window_manager
    // create, destroy, get(id)

    class t_properties{}; // system props - os, monutors - res, video - api, devices

    class t_config{}; // engine config - read, write, path (arg), - should be mapped on window settings

    class t_menu {}; // game menu
    // graphics
    //  device
    //  api
    //  monitor
    //  mode
    //  res
    //  
    // audio
    //  device
    //  api
    //  
    // input
    //  mouse / keyboard
    //  gamepad
    // new game
    // load
    // settings
    // exit

    // Language / localization
    class t_locale{};

    // Text output
    class t_text{};
    class t_font{};

    // Devices
    class t_device{};
    class t_video{};
    class t_audio{};
    class t_monitor{};
    class t_keyboard{};
    class t_gamepad{};
    class t_mouse{};

    // types - int, str, ...

    // Driver: device use driver

    class t_network{};

    class t_io{}; // read/write async - low level

    class debug{};
    class assert{};
    class error_handler{};
    class check_input_data{};

}