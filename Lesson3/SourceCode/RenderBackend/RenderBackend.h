#include "IRenderBackend.h"

class RENDERBACKEND_API RenderBackend final : public IRenderBackend
{
public:
	virtual void Init() override;
	virtual void SetWindowHandle(void* windowHandle) override;
	virtual void InitRenderObject(RenderObject* renderObject) override;
	virtual void SetViewTransform() override;
	virtual void Draw(RenderObject* renderObject) override;
	virtual void DrawFrame() override;

private:
	void* m_windowHandle;
};