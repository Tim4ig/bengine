
#pragma once

#include "pch.h"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "../CBuffer.hpp"

namespace be::render
{
	class Object
	{
	public:
		Object(ComPtr<ID3D11Device> device);

		void SetVertices(drawable::Vertex* vertexArr, size_t count);

		void SetPosition(dm::Vector3 position);
		dm::Vector3 GetPosition();

		drawable::Mesh* GetRawMesh();
		drawable::Texture* GetRawTexture();
		drawable::Transform* GetRawTransform();
		pipeline::CBuffer* GetRawCBuffer();
	private:
		ComPtr<ID3D11Device> m_device;

		drawable::Mesh m_mesh;
		drawable::Texture m_texture;
		drawable::Transform m_transform;

		struct
		{
			dm::Matrix worldMatrix;
		} m_objectTransforms;
		pipeline::CBuffer m_cbuffer;
	};
}
