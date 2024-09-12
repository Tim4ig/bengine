
#pragma once

#include "pch.h"

namespace be::render::drawable
{
	struct Transform
	{
		dm::Vector3 position;
		dm::Quaternion rotation;
		dm::Vector3 scale;
		bool isUpdated = true;
	};
}
