
#pragma once

#include "pch.h"
#include "Renderer.hpp"

#include "Drawable/Object.hpp"
#include "Window/Window.hpp"

namespace be::render
{
	class Device
	{
	public:
		Device();
		~Device();

		ComPtr<ID3D11Device> GetRawDevice() const;
		ComPtr<ID3D11DeviceContext> GetRawContext() const;
		std::shared_ptr<Renderer> CreateRenderer(std::shared_ptr<Window> hwnd, POINT size);

		std::shared_ptr<Object> CreateObject();
	private:
		ComPtr<IDXGIAdapter> m_adapter;
		ComPtr<IDXGIFactory2> m_factory;

		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;

		void m_Init();
	};
}
