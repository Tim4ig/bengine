
#pragma once

#include "pch.h"

#include "Drawable/Object.hpp"
#include "Pipelines/BasePipeline.hpp"
#include "Window/Window.hpp"
#include "Camera.hpp"

namespace be::render
{
	class Renderer
	{
	public:
		Renderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> context, std::shared_ptr<Window> hwnd, POINT size);
		~Renderer();

		void BeginDraw();
		void EndDraw();

		void SetSize(POINT size);
		void SetCamera(Camera* camera);

		void Clear();
		void DrawObject(Object* object);
	private:
		std::shared_ptr<Window> m_hwnd;

		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;

		ComPtr<IDXGISwapChain1> m_swapChain;
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		std::unique_ptr<pipeline::BasePipeline> m_basePipeline;

		void m_Init(POINT size);
		void m_InitPipelines();
	};
}
