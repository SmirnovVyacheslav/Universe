// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/platform.h"

#include "engine/render/shader/api_shader.h"
#include "engine/render/shader/obj_shader.h"

#include "engine/var/matrix4.h"
#include "engine/var/string.h"


#ifdef windows

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

#endif
