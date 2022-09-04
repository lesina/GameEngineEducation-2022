#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

CubeGameObject::CubeGameObject()
{
	m_pRenderProxy = new CubeRenderProxy();
}
