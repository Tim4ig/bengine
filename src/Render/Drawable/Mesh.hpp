
#pragma once

#include "pch.h"
#include "Vertex.hpp"

namespace be::render::drawable
{
	struct Mesh
	{
		size_t vertexCount = 0;
		std::unique_ptr<Vertex[]> vertices;
		ComPtr<ID3D11Buffer> vertexBuffer;
	};
}
