
#pragma once

#include "pch.h"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

namespace be::render
{
	class Object : public drawable::Transform
	{
	public:
		Object(ComPtr<ID3D11Device> device);

		void SetVertices(drawable::Vertex* vertexArr, size_t count);

		drawable::Mesh* GetRawMesh();
		drawable::Texture* GetRawTexture();
		drawable::Transform* GetRawTransform();
	private:
		ComPtr<ID3D11Device> m_device;

		drawable::Mesh m_mesh;
		drawable::Texture m_texture;
	};
}
