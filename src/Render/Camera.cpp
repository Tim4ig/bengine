
#include "Camera.hpp"

namespace be::render
{
	void Camera::SetPosition(dm::Vector3 position)
	{
		m_position = position;
		this->m_UpdateView();
	}

	dm::Vector3 Camera::GetPosition()
	{
		return m_position;
	}

	void Camera::SetTarget(dm::Vector3 target)
	{
		m_target = target;
		m_target.Normalize();
		this->m_UpdateView();
	}

	dm::Vector3 Camera::GetTarget()
	{
		return dm::Vector3();
	}

	dm::Matrix Camera::GetView()
	{
		return m_view;
	}

	void Camera::SetView(dm::Matrix view)
	{
		m_view = view;
	}

	void Camera::m_UpdateView()
	{
		dm::Vector3 up = { 0.0f, 1.0f, 0.0f };
		m_view = dm::Matrix::CreateLookAt(m_position, m_position + m_target, up);
	}
}
