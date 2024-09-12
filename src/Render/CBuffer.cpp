
#include "CBuffer.hpp"

namespace be::render::pipeline
{
	CBuffer::CBuffer(ComPtr<ID3D11Device> device)
	{
		m_device = device;
	}

	void CBuffer::BindVS(ComPtr<ID3D11DeviceContext> context, UINT slot)
	{
		context->VSSetConstantBuffers(slot, 1, m_buffer.GetAddressOf());
	}

	void CBuffer::Update(void* data, size_t size)
	{
		HRESULT hr = S_OK;

		if (size != m_size)
		{
			D3D11_SUBRESOURCE_DATA subresourceData = {};
			subresourceData.pSysMem = data;

			auto desc = CD3D11_BUFFER_DESC((size + 15) & ~15, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
			hr = m_device->CreateBuffer(
				&desc,
				&subresourceData,
				&m_buffer
			) TIF;

			m_size = size;
			return;
		}

		ComPtr<ID3D11DeviceContext> context;
		m_device->GetImmediateContext(&context);
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		hr = context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource) TIF;
		memcpy(mappedResource.pData, data, size);
		context->Unmap(m_buffer.Get(), 0);
	}
}
