// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "video.h"
#include "video/directx/directx.h"
#include <stdexcept>


namespace engine {
    video video::inst = video();


    void video::initialize() {
		api_list.append(lead_ptr<video_api>());
		api_list[0].initialize_derivative<directx>();
    }
    void video::create_device() {
		api_list[actual_api_index]->create_device();
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
}