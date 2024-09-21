
#include "Camera.hpp"

namespace be::render
{
	Camera::Camera()
	{
		this->m_UpdateView();
	}

	void Camera::Move(dm::Vector3 direction)
	{
		m_position += direction;
		this->m_UpdateView();
	}

	void Camera::SetPosition(dm::Vector3 position)
	{
		m_position = position;
		this->m_UpdateView();
	}

	dm::Vector3 Camera::GetPosition() const
	{
		return m_position;
	}

	void Camera::SetTarget(dm::Vector3 target)
	{
		m_target = target;
		m_target.Normalize();
		this->m_UpdateView();
	}

	dm::Vector3 Camera::GetTarget() const
	{
		return dm::Vector3();
	}

	dm::Matrix Camera::GetView() const
	{
		return m_view;
	}

	void Camera::SetView(dm::Matrix view)
	{
		m_view = view;
	}

	void Camera::m_UpdateView()
	{
		m_view = dm::Matrix::CreateLookAt(m_position, m_position + m_target, m_up);
	}
}
