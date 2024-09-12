
#include "Mesh.hpp"

namespace be::render::drawable
{
	Mesh::Mesh(ComPtr<ID3D11Device> device)
	{
		m_device = device;
	}

	void Mesh::SetVertices(drawable::Vertex* vertexArr, size_t count)
	{
		HRESULT hr = S_OK;

		m_vertexCount = count;
		m_vertices = std::make_unique<drawable::Vertex[]>(count);
		memcpy(m_vertices.get(), vertexArr, count * sizeof(drawable::Vertex));

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(drawable::Vertex) * count;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = m_vertices.get();

		hr = m_device->CreateBuffer(&bufferDesc, &initData, m_vertexBuffer.GetAddressOf()) TIF;
	}

	size_t Mesh::GetVertexCount() const
	{
		return m_vertexCount;
	}

	ID3D11Buffer* Mesh::GetVertexBuffer() const
	{
		return m_vertexBuffer.Get();
	}
}
