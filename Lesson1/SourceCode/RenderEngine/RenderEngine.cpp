#include <bx/math.h>
#include <bx/timer.h>

#include "RenderEngine.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

CRenderEngine::CRenderEngine(HINSTANCE hInstance)
{
	assert(!m_hwnd);
	m_hwnd = InitMainWindow(hInstance);
	assert(m_hwnd);

	bgfx::renderFrame();

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Direct3D11;
	bgfxInit.resolution.width = m_Width;
	bgfxInit.resolution.height = m_Height;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfxInit.platformData.nwh = m_hwnd;
	if (!bgfx::init(bgfxInit))
		assert(0);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

	m_timeOffset = bx::getHPCounter();
	m_defaultCube = new Cube();
	m_defaultMyFigure = new MyFigure();
	m_defaultMySphere = new MySphere();
}

CRenderEngine::~CRenderEngine()
{
	bgfx::shutdown();
	DestroyWindow(m_hwnd);
}

HWND CRenderEngine::InitMainWindow(HINSTANCE hInstance)
{
	std::wstring wstrWindowName = L"MainWnd";
	std::wstring wstrWindowCaption = L"GameEngine";

	HWND hwnd = nullptr;

	WNDCLASSEXW wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = wstrWindowName.c_str();
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return hwnd;
	}

	DWORD borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	DWORD defaultStyle = WS_OVERLAPPEDWINDOW;

	RECT R = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&R, defaultStyle, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	hwnd = CreateWindow(wstrWindowName.c_str(), wstrWindowCaption.c_str(),
		defaultStyle, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hwnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return hwnd;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;
}

void CRenderEngine::Update()
{
	const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 5.0f, -10.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at);
	float proj[16];
	bx::mtxProj(proj, 60.0f, float(m_Width) / float(m_Height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);

	float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

	float mtx[16];
	bx::mtxRotateY(mtx, time / 10.0f);
	mtx[12] = 0.0f;
	mtx[13] = 0.0f;
	mtx[14] = -1.0f;

	// Set model matrix for rendering.
	bgfx::setTransform(mtx);

	bgfx::setVertexBuffer(0, m_defaultMySphere->GetVertexBuffer());
	bgfx::setIndexBuffer(m_defaultMySphere->GetIndexBuffer());

	bgfx::submit(0, m_defaultMySphere->GetProgramHandle());

	for (size_t j = 0; j < 50; j++) {
		for (size_t i = 0; i < 50; i++) {
			float mtx[16];
			bx::mtxRotateY(mtx, (float(i % 2) - 0.5f) * -time * 2.0f);
			mtx[12] = 3 * cosf(time / 5.f + i) + 100 - j * 4;
			mtx[13] = sinf(cosf(time / 3.f + i) * 10.f) / 10.0f + sinf(float(j)) + cosf(float(i));
			mtx[14] = 0.0f + float(i) * 3.0f - 20;

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			bgfx::setVertexBuffer(0, m_defaultMyFigure->GetVertexBuffer());
			bgfx::setIndexBuffer(m_defaultMyFigure->GetIndexBuffer());

			bgfx::submit(0, m_defaultMyFigure->GetProgramHandle());
		}
	}

	bgfx::touch(0);

	bgfx::frame();
}