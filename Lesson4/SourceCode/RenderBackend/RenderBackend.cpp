#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <cassert>

#include "RenderBackend.h"
#include "BgfxRenderData.h"
#include "../RenderEngine/RenderObject.h"

void RenderBackend::Init()
{
	bgfx::renderFrame();

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Direct3D12;
	bgfxInit.resolution.width = 800;
	bgfxInit.resolution.height = 600;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfxInit.platformData.nwh = m_windowHandle;
	if (!bgfx::init(bgfxInit))
		assert(0);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void RenderBackend::SetWindowHandle(void* windowHandle)
{
	m_windowHandle = windowHandle;
}

void RenderBackend::InitRenderObject(RenderObject* renderObject)
{
	BgfxRenderData* renderData = new BgfxRenderData(renderObject);
	renderObject->SetRenderData(renderData);
}

void RenderBackend::SetViewTransform()
{
	const bx::Vec3 at = { 0.0f, 0.5f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 7.0f, -10.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at);
	float proj[16];
	bx::mtxProj(proj, 60.0f, float(800) / float(600), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);
}

void RenderBackend::Draw(RenderObject* renderObject)
{
	assert(renderObject->GetRenderData());

	float mtx[16];
	bx::mtxRotateXYZ(mtx, 0, 0, 0);

	float translate[3];
	renderObject->GetPosition(translate);

	bx::mtxTranslate(mtx, translate[0], translate[1], translate[2]);
	bgfx::setTransform(mtx);

	BgfxRenderData* renderData = reinterpret_cast<BgfxRenderData*>(renderObject->GetRenderData());

	bgfx::setVertexBuffer(0, renderData->GetVertexBuffer());
	bgfx::setIndexBuffer(renderData->GetIndexBuffer());

	bgfx::submit(0, renderData->GetProgramHandle());
}

void RenderBackend::DrawFrame()
{
	bgfx::touch(0);
	bgfx::frame();
}