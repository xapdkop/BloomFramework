#pragma once

#include "Position.h"
#include "Size.h"

namespace bloom::components {
	struct Transform {
		Position position;

		double rotation;

		Size size;
	};
}