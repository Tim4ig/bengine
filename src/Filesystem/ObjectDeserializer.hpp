
#pragma once

#include "pch.h"
#include "Render/Drawable/Object.hpp"
#include "tiny_gltf.h"

#include "../Render/Device.hpp"

namespace be::fs
{
	class ObjectDeserializer
	{
	public:
		static std::shared_ptr<render::Object> FromFile(std::shared_ptr<be::render::Device> dev, const std::string& path);
	private:
		static void LoadMeshes(const tinygltf::Model& model, std::shared_ptr<render::Object> obj);
	};
}
