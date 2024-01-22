// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/src/device/src/ext/directx/inc/impl.h"
#include "src/render/src/settings/inc/api.h"


namespace engine::render::device::directx
{
    impl::impl()
    {
        init_device();
        init_depth_stencil_view();
        init_render_target_view();
        init_view_port();

        set_primitive_topology();
    }

    impl::~impl()
    {
        clear_resource(device_context);

        release_resource(render_target_view);
        release_resource(swap_chain);
        release_resource(device_context);
        release_resource(device);
    }
}
