#pragma once

namespace bloom {
	struct Position {
		Position(int xPos = 0, int yPos = 0) : x(xPos), y(yPos) {}

		int x, y;
	};
}