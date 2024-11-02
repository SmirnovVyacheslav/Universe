// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/platform.h"

#include "engine/render/indices/directx/impl_indices.h"

#include "engine/render/device/device_impl_directx.h"

#include "engine/var/array.h"
#include "engine/var/error.h"
#include "engine/var/std.h"


#ifdef windows

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

#endif
