// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/platform.h"

#include "engine/render/device/obj_device.h"

#include "engine/render/model/obj_model.h"

#include "engine/render/settings/api_settings.h"
#include "engine/render/settings/obj_settings.h"

#include "engine/var/matrix4.h"
#include "engine/var/vector3.h"
#include "engine/var/vector4.h"


#ifdef windows

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

#endif
