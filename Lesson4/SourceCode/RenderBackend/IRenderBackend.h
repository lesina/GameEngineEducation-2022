#pragma once

#include "Common.h"

class RenderObject;

class RENDERBACKEND_API IRenderBackend
{
public:
	virtual void Init() = 0;
	virtual void SetWindowHandle(void* windowHandle) = 0;
	virtual void InitRenderObject(RenderObject* renderObject) = 0;
	virtual void SetViewTransform() = 0;
	virtual void Draw(RenderObject* renderObject) = 0;
	virtual void DrawFrame() = 0;
};