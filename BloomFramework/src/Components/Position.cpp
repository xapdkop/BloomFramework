#include "Components/Position.h"

namespace bloom::components {
	Position::Position() : x(0), y(0), relativeTo(middle | center) {}

	Position::Position(int x, int y, Type type, int direction) : x(x), y(y), relativeTo(direction) {
		if (type == Type::absolute)
			this->relativeTo = (middle | center);
	}

	Position::Position(const SDL_Point & point) : x(point.x), y(point.y), relativeTo(middle | center) {}

	Position Position::toAbsolute(components::Size objSize, components::Size frameSize) {
		Position result;
		if ((relativeTo & left) == left)
			result.x = x;
		else if ((relativeTo & center) == center)
			result.x = frameSize.w / 2 - objSize.w / 2 + x;
		else if ((relativeTo & right) == right)
			result.x = frameSize.w - objSize.w + x;
		else
			result.x = x;

		// Get SDL style Y position, factoring object height as well.
		if ((relativeTo & top) == top)
			result.y = y;
		else if ((relativeTo & middle) == middle)
			result.y = frameSize.h / 2 - objSize.h / 2 - y;
		else if ((relativeTo & bottom) == bottom)
			result.y = frameSize.h - objSize.h - y;
		else
			result.y = y;

		return result;
	}

	Position Position::toAbsolute(SDL_Renderer * targetRenderer, components::Size objSize) {
		int rendererWidth, rendererHeight;
		SDL_RenderGetLogicalSize(targetRenderer, &rendererWidth, &rendererHeight);

		return toAbsolute(objSize, { rendererWidth, rendererHeight });
	}

	SDL_Point Position::toSDLPoint(SDL_Renderer * targetRenderer) {
		auto tmp = toAbsolute(targetRenderer, { 0, 0 });
		return SDL_Point{ tmp.x, tmp.y };
	}
}