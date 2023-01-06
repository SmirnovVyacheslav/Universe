// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include <stdexcept>

#include "video/directx/directx.h"

#include "video.h"


namespace engine {
    video video::inst = video();


    void video::initialize() {
        inst.api_list.append(lead_ptr<video_api>());
        inst.api_list[0].initialize_derivative<directx>();

        inst.set_actual_api();
        inst.create_device();
    }
    void video::create_device() {
        inst.api_list[inst.actual_api_index]->create_device();
    }
    void video::render() {
        inst.api_list[inst.actual_api_index]->render();
    }
    void video::set_actual_api() {
        for (std::int32_t i = 0; i < api_list.size(); ++i) {
            if (api_list[i]->available()) {
                actual_api_index = i;
                return;
            }
        }
        throw std::invalid_argument("No video api available");
    }
    void* video::create_vertex_shader(string shader_code) {
        return inst.api_list[inst.actual_api_index]->create_vertex_shader(shader_code);
    }
    void* video::create_pixel_shader(string shader_code) {
        return inst.api_list[inst.actual_api_index]->create_pixel_shader(shader_code);
    }
    void video::destroy_vertex_shader(void* shader_obj) {
        inst.api_list[inst.actual_api_index]->destroy_vertex_shader(shader_obj);
    }
    void video::destroy_pixel_shader(void* shader_obj) {
        inst.api_list[inst.actual_api_index]->destroy_pixel_shader(shader_obj);
    }
}
