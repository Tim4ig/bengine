
#pragma once

#include "pch.h"

namespace be::render
{
	class Camera
	{
	public:
		void SetPosition(dm::Vector3 position);
		dm::Vector3 GetPosition();

		void SetTarget(dm::Vector3 target);
		dm::Vector3 GetTarget();

		dm::Matrix GetView();
		void SetView(dm::Matrix view);
	private:
		dm::Matrix m_view;
		dm::Vector3 m_position;
		dm::Vector3 m_target = dm::Vector3(0, 0, 1);

		void m_UpdateView();
	};
}
