#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "IRenderData.h"

class RenderObject;

class RENDERBACKEND_API BgfxRenderData final : public IRenderData
{
public:
	BgfxRenderData(RenderObject* renderObject);

	bgfx::VertexBufferHandle GetVertexBuffer() { return m_vbh; }
	bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; }
	bgfx::ProgramHandle GetProgramHandle() { return m_ProgramHandle; }

private:
	bgfx::VertexLayout m_Layout = bgfx::VertexLayout();
	bgfx::VertexBufferHandle m_vbh = bgfx::VertexBufferHandle();
	bgfx::IndexBufferHandle m_ibh = bgfx::IndexBufferHandle();
	bgfx::ProgramHandle m_ProgramHandle = bgfx::ProgramHandle();
};

