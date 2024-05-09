// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/platform.h"

#include "engine/render/camera/api_camera.h"
#include "engine/render/camera/obj_camera.h"

#include "engine/render/device/directx/impl_device.h"

#include "engine/render/shader/directx/impl_shader.h"

#include "engine/var/error.h"
#include "engine/var/string.h"


#ifdef windows

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

#endif
