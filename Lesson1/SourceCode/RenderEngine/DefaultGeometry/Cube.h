#pragma once

#include "../RenderObject.h"

namespace
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class Cube : public RenderObject //Not a cube anymore!
{
public:
	Cube();

private:
	inline static const PosColorVertex s_cubeVertices[] =
	{
		{ 1.0f,  2.0f,  0.0f, 0xff000000 },
		{ 0.5f,  2.0f, -1.0f, 0xff00ff00 },
		{-1.0f,  2.0f, -1.0f, 0xffff0000 },
		{-1.0f,  2.0f,  1.0f, 0xff00ffff },
		{ 0.5f,  2.0f,  1.0f, 0xff0000ff },
		
		{ 1.0f, -2.0f,  0.0f, 0xffff00ff },
		{ 0.5f, -2.0f, -1.0f, 0xffbb00aa },
		{-1.0f, -2.0f, -1.0f, 0xff00aabb },
		{-1.0f, -2.0f,  1.0f, 0xffaabb00 },
		{ 0.5f, -2.0f,  1.0f, 0xffffff00 },

		{ 0.2f, -4.0f,  0.0f, 0xffffffff }
	};

	inline static const uint16_t s_cubeTriList[] =
	{
		//bottom
		2, 1, 0, // 0
		3, 2, 0,
		4, 3, 0,

		//peak
		10, 5, 6, //3
		10, 6, 7,
		10, 7, 8,
		10, 8, 9,
		10, 9, 5,

		//sides
		0, 1, 5, // 8
		1, 6, 5,

		1, 2, 6, // 10
		2, 7, 6,

		2, 3, 7, // 12
		3, 8, 7,

		3, 4, 8, // 14
		4, 9, 8,

		4, 0, 9, // 16
		0, 5, 9,
	};
};

