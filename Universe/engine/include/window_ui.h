/******************************************************************************
     * File: window_ui.h
     * Description: API to work with windows
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_UI_H
#define WINDOW_UI_H


namespace engine
{
    using window_ptr = std::shared_ptr<window_ui>;

    class window_ui
    {
    public:
        virtual ~window_ui() = default;

    protected:
        window_ui() = default;
    };
}

#endif
