// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/platform.h"

#include "engine/platform/api/view.h"

#include "engine/render/device/directx/impl_device.h"

#include "engine/render/model/obj_model.h"

#include "engine/render/settings/api_settings.h"
#include "engine/render/settings/obj_settings.h"

#include "engine/var/error.h"
#include "engine/var/std.h"


#ifdef windows

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

#endif
