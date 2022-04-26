// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "engine_ui.h"
#include "src/scene/scene.h"
#include "src/render/render.h"


namespace engine
{
	namespace ui
	{
		void engine_ui::add_object()
		{
			engine::scene::inst.add_object();
		}

		void engine_ui::start_render()
		{
			engine::render::inst.start_render();
		}
	}
}
