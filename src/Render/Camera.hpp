
#pragma once

#include "pch.h"

namespace be::render
{
	class Camera
	{
	public:
		Camera();

		void Move(dm::Vector3 direction);

		void SetPosition(dm::Vector3 position);
		dm::Vector3 GetPosition() const;

		void SetTarget(dm::Vector3 target);
		dm::Vector3 GetTarget() const;

		void SetView(dm::Matrix view);
		dm::Matrix GetView() const;
	private:
		dm::Matrix m_view;
		dm::Vector3 m_position;
		dm::Vector3 m_target = dm::Vector3(0, 0, -1);
		dm::Vector3 m_up = dm::Vector3(0, 1, 0);

		void m_UpdateView();
	};
}
