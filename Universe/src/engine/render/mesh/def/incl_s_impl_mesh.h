// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/render/mesh/impl_mesh.h"

#include "engine/render/indices/api_indices.h"
#include "engine/render/indices/obj_indices.h"

#include "engine/render/settings/api_settings.h"
#include "engine/render/settings/obj_settings.h"

#include "engine/render/vertices/api_vertices.h"
#include "engine/render/vertices/obj_vertices.h"

#include "engine/var/array.h"
#include "engine/var/error.h"
#include "engine/var/string.h"
#include "engine/var/std.h"
#include "engine/var/vector3.h"
#include "engine/var/vector4.h"
#include "engine/var/vertex.h"


#include <iostream>
#include <filesystem>
#include <fstream>
