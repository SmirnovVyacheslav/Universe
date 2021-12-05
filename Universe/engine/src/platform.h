/******************************************************************************
     * File: platform.h
     * Description: Platform API
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

namespace engine
{
    namespace platform
    {
        class type_properties
        {
            // System name and other properties
        };

        // Devices
        class type_device_manager
        {
            // create and control devices
        };

        class type_device
        {
            // abstract device type
        };
        // Devices

        // get global - system properties - type, name, version, ram / rom memory space ???...
        // devices - device manager
        //  processor devices - cpu, gpu, ..
        //  disk devices
        //  type: video: input, output, audio: input, output, gamepad: input, output, 
        //  support api: directX, openGL, Vulkan
        //


        class properties_type
        {
            // OS name, version
            // CPU
            // GPU
            // SPU
            // disk memory
            // RAM
            // devices
        };

        // device_manager???

        // hw devices
        class cpu_type{}; // central processor
        class gpu_type{}; // graphic processor
        class spu_type{}; // sound processor
        class npu_type{}; // network processor
        class disk_type{}; // disk
        // wifi, bluetooth

        // perferial devices / output devices
        class display_type{}; // monitor
        class speaker_type{};

        // input devices
        class microphone_type{}; //microphone
        class keyboard_type{}; // keyboard_type
        class mouse_type{}; // mouse
        class gamepad_type{}; // gamepad
        // video camera
        // accelerometr
    }
}

#endif