
#include "Device.hpp"

namespace be::render
{
	Device::Device()
	{
		this->m_Init();
	}

	Device::~Device()
	{
	}

	std::shared_ptr<Renderer> Device::CreateRenderer(std::shared_ptr<Window> hwnd, POINT size)
	{
		return std::make_shared<Renderer>(m_device, m_context, hwnd, size);
	}

	std::shared_ptr<Object> Device::CreateObject()
	{
		return std::make_shared<Object>(m_device);
	}

	ComPtr<ID3D11Device> Device::GetRawDevice()
	{
		return m_device;
	}

	ComPtr<ID3D11DeviceContext> Device::GetRawContext()
	{
		return m_context;
	}

	void Device::m_Init()
	{
		HRESULT hr = S_OK;

		hr = CreateDXGIFactory(IID_PPV_ARGS(&m_factory)) TIF;
		
		{
			UINT flags = 0;
			if constexpr (DEBUG) flags |= D3D11_CREATE_DEVICE_DEBUG;

			hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				D3D11_CREATE_DEVICE_DEBUG,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&m_device,
				nullptr,
				&m_context
			) TIF;
		}

		{
			ComPtr<IDXGIDevice> device;
			hr = m_device.As(&device) TIF;
			hr = device->GetAdapter(&m_adapter) TIF;
		}
	}
}
