
#pragma once

#include "pch.h"

#include "../Drawable/Object.hpp"

namespace be::render::pipeline
{
	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;

		virtual void BeginDraw(ComPtr<ID3D11RenderTargetView> target) = 0;
		virtual ComPtr<ID3D11CommandList> EndDraw() = 0;

		virtual void Resize(POINT size) = 0;

		virtual void Clear() = 0;
		virtual void DrawObject(Object* object) = 0;
	protected:
		D3D11_VIEWPORT m_viewport = {};
		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;
		ComPtr<ID3D11RenderTargetView> m_target;
	};
}
