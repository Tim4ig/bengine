
#include "ObjectDeserializer.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

namespace be::fs
{
	std::shared_ptr<render::Object> ObjectDeserializer::FromFile(std::shared_ptr<be::render::Device> dev, const std::string& path)
	{
		tinygltf::Model model;
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		auto res = loader.LoadBinaryFromFile(&model, &err, &warn, path);

		if (!warn.empty() || !res || !err.empty())
		{
			THROW("ObjectDeserializer error\n" + warn + err);
		}

        auto obj = dev->CreateObject();

		LoadMeshes(model, obj);

		return obj;
	}

    void ObjectDeserializer::LoadMeshes(const tinygltf::Model& model, std::shared_ptr<render::Object> obj)
    {
        for (const auto& mesh : model.meshes)
        {
            for (const auto& primitive : mesh.primitives)
            {
                std::vector<be::render::drawable::Vertex> vertices;

                if (primitive.attributes.find("POSITION") != primitive.attributes.end())
                {
                    auto positionAccessorIndex = primitive.attributes.find("POSITION")->second;
                    const auto& positionAccessor = model.accessors[positionAccessorIndex];
                    const auto& positionBufferView = model.bufferViews[positionAccessor.bufferView];
                    const auto& positionBuffer = model.buffers[positionBufferView.buffer];

                    const auto* positions = reinterpret_cast<const float*>(&positionBuffer.data[positionBufferView.byteOffset + positionAccessor.byteOffset]);
                    auto vertexCount = positionAccessor.count;

                    if (primitive.indices >= 0)
                    {
                        const auto& indexAccessor = model.accessors[primitive.indices];
                        const auto& indexBufferView = model.bufferViews[indexAccessor.bufferView];
                        const auto& indexBuffer = model.buffers[indexBufferView.buffer];

                        const void* indices = &indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset];
                        bool isIndex32Bit = indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT;

                        for (size_t i = 0; i < indexAccessor.count; ++i)
                        {
                            uint32_t index = 0;
                            if (isIndex32Bit)
                            {
                                index = reinterpret_cast<const uint32_t*>(indices)[i];
                            }
                            else
                            {
                                index = reinterpret_cast<const uint16_t*>(indices)[i];
                            }

                            float x = positions[index * 3 + 0];
                            float y = positions[index * 3 + 1];
                            float z = positions[index * 3 + 2];

                            vertices.push_back({ x, y, z });
                        }
                    }
                    else
                    {
                        for (size_t i = 0; i < vertexCount; ++i)
                        {
                            float x = positions[i * 3 + 0];
                            float y = positions[i * 3 + 1];
                            float z = positions[i * 3 + 2];

                            vertices.push_back({ x, y, z });
                        }
                    }
                    obj->SetVertices(vertices.data(), vertices.size());
                }
            }
        }
    }
}
