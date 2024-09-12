
#pragma once

#include "pch.h"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

namespace be::render
{
	class Object : public drawable::Transform, public drawable::Mesh
	{
	public:
		Object(ComPtr<ID3D11Device> device);
	};
}
