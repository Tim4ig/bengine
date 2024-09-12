
#pragma once

#include "pch.h"
#include "Vertex.hpp"

namespace be::render::drawable
{
	class Mesh
	{
	public:
		Mesh(ComPtr<ID3D11Device> device);

		void SetVertices(drawable::Vertex* vertexArr, size_t count);

		size_t GetVertexCount() const;
		ID3D11Buffer* GetVertexBuffer() const;
	private:
		size_t m_vertexCount = 0;
		std::unique_ptr<Vertex[]> m_vertices;

		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11Buffer> m_vertexBuffer;
	};
}
