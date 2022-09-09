#include "BgfxRenderData.h"
#include "Shaders/ShadersHelper.h"

#include "../RenderEngine/RenderObject.h"

BgfxRenderData::BgfxRenderData(RenderObject* renderObject)
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(renderObject->GetVertices(), renderObject->GetVerticesSize())
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(renderObject->GetIndices(), renderObject->GetIndicesSize())
	);

	m_ProgramHandle = ShadersHelper::LoadProgram(renderObject->GetVsShaderName().c_str(), renderObject->GetPsShaderName().c_str());
}