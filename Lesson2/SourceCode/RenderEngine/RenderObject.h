#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Common.h"
#include "RenderProxy.h"

class RENDERENGINE_API RenderObject
{
public:
	RenderObject(RenderProxy* pRenderProxy) :
		m_pRenderProxy(pRenderProxy)
	{}

	bgfx::VertexBufferHandle GetVertexBuffer() { return m_vbh; }
	bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; }
	bgfx::ProgramHandle GetProgramHandle() { return m_ProgramHandle; }

	void GetPosition(float* result) { m_pRenderProxy->GetPosition(result); }

protected:
	bgfx::VertexLayout m_Layout = bgfx::VertexLayout();
	bgfx::VertexBufferHandle m_vbh = bgfx::VertexBufferHandle();
	bgfx::IndexBufferHandle m_ibh = bgfx::IndexBufferHandle();
	bgfx::ProgramHandle m_ProgramHandle = bgfx::ProgramHandle();

	RenderProxy* m_pRenderProxy;
};

