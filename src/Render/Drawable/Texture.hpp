
#pragma once

#include "pch.h"

namespace be::render::drawable
{
	struct Texture
	{
		ComPtr<ID3D11ShaderResourceView> textureView;
	};
}
