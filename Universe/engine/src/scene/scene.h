// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef SCENE_H
#define SCENE_H


namespace engine
{
	class scene
	{
	public:
		static scene inst;

		void add_object();

	private:
		scene() = default;
		~scene() = default;
	};
}
#endif
