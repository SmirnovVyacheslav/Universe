/******************************************************************************
	 * Description: Platform UI
	 * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com
******************************************************************************/


#include "platform_ui.h"


namespace engine
{
	namespace platform
	{
		platform_mng_ui::platform_mng_ui() : window_mng(window_mng_ui::create()) {}
	}
}
