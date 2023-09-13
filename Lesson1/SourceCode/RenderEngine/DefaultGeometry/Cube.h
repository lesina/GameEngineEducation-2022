#pragma once

#include "../RenderObject.h"

class Cube : public RenderObject
{
public:
	Cube();

private:
	inline static const PosColorVertex s_cubeVertices[] =
	{
		{-1.0f,  1.0f,  1.0f, 0x00ffffff },
		{ 1.0f,  1.0f,  1.0f, 0x00ffffff },
		{-1.0f, -1.0f,  1.0f, 0x00ffffff },
		{ 1.0f, -1.0f,  1.0f, 0x00ffffff },
		{-1.0f,  1.0f, -1.0f, 0x00ffffff },
		{ 1.0f,  1.0f, -1.0f, 0x00ffffff },
		{-1.0f, -1.0f, -1.0f, 0x00ffffff },
		{ 1.0f, -1.0f, -1.0f, 0x00ffffff },
	};

	inline static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};
};

