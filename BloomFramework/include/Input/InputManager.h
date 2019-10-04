#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputEvents.h"
#include "Event.h"
#include "EventRecorder.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		bool update(bool continueOnQuit = false);
		// If timeout < 0, the function will wait for the event indefinitely
		events::EventType wait(int timeout = -1);
		bool quitRequested() noexcept;

		void lock() noexcept;
		void unlock() noexcept;
		events::EventType lastEventType() const noexcept;

		KeyboardEvent keyboard{};
		MouseEvent mouse{};

		events::EventRecorder<events::Event> recorder{};
		
	private:
		void reset();
		void handle();

		bool m_quitState = false;
		SDL_Event m_intlEvent{};
		events::EventType m_lastType = events::EventType::Empty;
	};
}