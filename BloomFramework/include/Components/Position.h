#pragma once
#include "stdIncludes.h"
#include "Components/Size.h"

namespace bloom::components {
	struct BLOOMFRAMEWORK_API Position {
		int x, y;
		int relativeTo;

		enum class Type {
			absolute,
			relative
		};

		enum Relation {
			top = 1,
			middle = 2,
			bottom = 4,

			left = 8,
			center = 16,
			right = 32
		};

		Position();
		Position(const Position&) = default;
		Position(int x, int y, Type type = Type::absolute, int direction = top | left);
		Position(const SDL_Point& point);

		Position toAbsolute(components::Size objSize, components::Size frameSize);
		Position toAbsolute(SDL_Renderer* targetRenderer, components::Size objSize);
		SDL_Point toSDLPoint(SDL_Renderer * targetRenderer);
	};
}