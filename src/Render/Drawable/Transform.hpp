
#pragma once

#include "pch.h"
#include "../CBuffer.hpp"

namespace be::render::drawable
{
	class Transform
	{
	public:
		Transform(ComPtr<ID3D11Device> device);
		pipeline::CBuffer* GetRawCBuffer();

		void SetPosition(dm::Vector3 position);
		dm::Vector3 GetPosition() const;
	protected:
		dm::Vector3 m_scale;
		dm::Vector3 m_position;
		dm::Quaternion m_rotation;
		pipeline::CBuffer m_cbuffer;

		struct
		{
			dm::Matrix worldMatrix;
		} m_objectTransforms;
	};
}
