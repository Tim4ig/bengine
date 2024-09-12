
#pragma once

#include "pch.h"

namespace be::render::pipeline
{
	class CBuffer
	{
	public:
		CBuffer(ComPtr<ID3D11Device> device);

		void BindVS(ComPtr<ID3D11DeviceContext> context, UINT slot);

		void Update(void* data, size_t size);

		template<class T>
		void Update(T& data) { Update(&data, sizeof(T)); }
	private:
		size_t m_size = 0;
		ComPtr<ID3D11Buffer> m_buffer;
		ComPtr<ID3D11Device> m_device;
	};
}
