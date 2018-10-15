#pragma once

#include "stdIncludes.h"
#include "DefaultSystem.h"
#include "Components/Components.h"

namespace bloom::systems {
	using namespace components;

	class RenderSystem : public System {
		using System::DefaultSystem;
	public:
		void update(std::optional<double> deltaTime = std::nullopt) override;
	};

	void RenderSystem::update (std::optional<double> deltaTime) {
			m_registry.view<Position, Size, Sprite>().each(
				[](auto entity, Position & pos, Size& size, Sprite & spr) {
				SDL_Rect destRect{
					static_cast<int>(pos.x),
					static_cast<int>(pos.y),
					static_cast<int>(size.w),
					static_cast<int>(size.h)
				};
				spr._texture->render(spr._srcRect, destRect);
			});
	}
} 