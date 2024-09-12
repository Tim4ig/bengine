
#include "Object.hpp"

namespace be::render
{
	Object::Object(ComPtr<ID3D11Device> device) : drawable::Transform(device)
	{
		m_device = device;
	}

	void Object::SetVertices(drawable::Vertex* vertexArr, size_t count)
	{
		HRESULT hr = S_OK;

		m_mesh.vertexCount = count;
		m_mesh.vertices = std::make_unique<drawable::Vertex[]>(count);
		memcpy(m_mesh.vertices.get(), vertexArr, count * sizeof(drawable::Vertex));

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(drawable::Vertex) * count;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = m_mesh.vertices.get();

		hr = m_device->CreateBuffer(&bufferDesc, &initData, m_mesh.vertexBuffer.GetAddressOf()) TIF;
	}

	drawable::Mesh* Object::GetRawMesh()
	{
		return &m_mesh;
	}

	drawable::Texture* Object::GetRawTexture()
	{
		return &m_texture;
	}
}
