
#include "Object.hpp"

namespace be::render
{
	Object::Object(ComPtr<ID3D11Device> device) : drawable::Transform(device), drawable::Mesh(device)
	{
	}
}
