
#include "Transform.hpp"

namespace be::render::drawable
{
	Transform::Transform(ComPtr<ID3D11Device> device) : m_cbuffer(device)
	{
	}

	pipeline::CBuffer* Transform::GetRawCBuffer()
	{
		return &m_cbuffer;
	}

	void Transform::SetPosition(dm::Vector3 position)
	{
		m_position = position;
		m_objectTransforms.worldMatrix = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		m_cbuffer.Update(&m_objectTransforms, sizeof(m_objectTransforms));
	}

	dm::Vector3 Transform::GetPosition() const
	{
		return m_position;
	}

}
