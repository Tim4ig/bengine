
#include "Renderer.hpp"

namespace be::render
{
	Renderer::Renderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> context, std::shared_ptr<Window> hwnd, POINT size)
	{
		m_device = device;
		m_context = context;
		m_hwnd = hwnd;

		this->m_Init(size);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::BeginDraw()
	{
		m_basePipeline->BeginDraw(m_renderTargetView);
	}

	void Renderer::EndDraw()
	{
		HRESULT hr = S_OK;

		auto list = m_basePipeline->EndDraw();
		m_context->ExecuteCommandList(list.Get(), FALSE);
		hr = m_swapChain->Present(1, 0) TIF;
	}

	void Renderer::SetCamera(Camera* camera)
	{
		m_basePipeline->SetCamera(camera);
	}

	void Renderer::DrawObject(Object* object)
	{
		m_basePipeline->DrawObject(object);
	}

	void Renderer::SetSize(POINT size)
	{
		if (!m_swapChain) return;

		HRESULT hr = S_OK;

		if (m_basePipeline)
		{
			m_basePipeline->Resize(size);
		}

		if (GetWindowLongPtr(m_hwnd->GetHandle(), GWL_STYLE) & WS_OVERLAPPEDWINDOW)
		{
			m_hwnd->SetSize(size);
		}

		m_renderTargetView.Reset();
		hr = m_swapChain->ResizeBuffers(BUFFER_COUNT, size.x, size.y, DXGI_FORMAT_R8G8B8A8_UNORM, 0) TIF;

		{
			ComPtr<ID3D11Texture2D> backBuffer;
			hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)) TIF;
			hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTargetView) TIF;
		}
	}

	void Renderer::Clear()
	{
		m_basePipeline->Clear();
	}

	void Renderer::m_Init(POINT size)
	{
		HRESULT hr = S_OK;

		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};
			desc.Width = size.x;
			desc.Height = size.y;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			desc.BufferCount = BUFFER_COUNT;
			desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullDesc = {};
			fullDesc.Windowed = TRUE;

			ComPtr<IDXGIDevice> device;
			ComPtr<IDXGIFactory2> factory;
			ComPtr<IDXGIAdapter> adapter;
			hr = m_device.As(&device) TIF;
			hr = device->GetAdapter(&adapter) TIF;
			hr = adapter->GetParent(IID_PPV_ARGS(&factory)) TIF;

			hr = factory->CreateSwapChainForHwnd(
				m_device.Get(),
				m_hwnd->GetHandle(),
				&desc,
				&fullDesc,
				nullptr,
				&m_swapChain
			) TIF;

			hr = factory->MakeWindowAssociation(m_hwnd->GetHandle(), DXGI_MWA_NO_ALT_ENTER) TIF;
		}

		this->SetSize(size);
		this->m_InitPipelines();
		m_basePipeline->Resize(size);
	}

	void Renderer::m_InitPipelines()
	{
		m_basePipeline = std::make_unique<pipeline::BasePipeline>(m_device);
	}
}
