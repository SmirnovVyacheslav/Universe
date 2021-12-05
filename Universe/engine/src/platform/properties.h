/******************************************************************************
     * File: platform/properties.h
     * Description: Main platform properties
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFORM_PROPERTIES_H
#define PLATFORM_PROPERTIES_H


namespace engine
{
    namespace platform
    {
    /*************************************************************************/
        class t_properties
        {
            // System name and other properties
        public:
            t_properties() {};
            ~t_properties() {};

            bool initialize() { return true; };
            bool terminate() { return true; };
        };
    /*************************************************************************/
        t_properties g_properties_instance;
    /*************************************************************************/
    }
}

#endif
