// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


#define abstract_class struct

#define abstract_def(type) virtual void abstract_func() = 0; virtual ~type() = default;

#define abstract_impl(type) virtual void abstract_func() {};
