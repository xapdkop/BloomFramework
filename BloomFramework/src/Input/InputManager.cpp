#include "Input/InputManager.h"

namespace bloom::input {
	bool InputManager::update(bool continueOnQuit) {
		reset();
		//keyboard.m_keyState.fill(0);
		//mouse.m_mouseState.fill(0);

		//mouse.m_mouseMoveX = 0;
		//mouse.m_mouseMoveY = 0;
		//keyboard.m_char.reset();
		//keyboard.m_keyboard = SDL_GetKeyboardState(nullptr);
		//mouse.m_mouse = SDL_GetMouseState(&mouse.m_mouseX, &mouse.m_mouseY);

		bool caught = false;

		// Get key events from the OS
		while (SDL_PollEvent(&m_intlEvent)) {
			handle();
			caught = true;
			if (m_quitState && !continueOnQuit)
				break;
		}
		if (!caught)
			m_lastType = events::EventType::Empty;
		return caught;
	}

	events::EventType InputManager::wait(int timeout) {
		int caught;
		if (timeout < 0)
			caught = SDL_WaitEvent(&m_intlEvent);
		else
			caught = SDL_WaitEventTimeout(&m_intlEvent, timeout);
		if (caught)
			handle();
		else
			m_lastType = events::EventType::Empty;
		return m_lastType;
	}

	void InputManager::handle() {
		switch (m_intlEvent.type) {
		case SDL_QUIT: {
			m_lastType = events::EventType::Quit;
			m_quitState = true;
			if (recorder.state()) {
				recorder._add(std::make_shared<events::QEvent>());
			}
			break;
		}
		case SDL_KEYDOWN: case SDL_KEYUP: {
			m_lastType = events::EventType::Keyboard;
			keyboard.set(m_intlEvent.key);
			if (recorder.state())
				recorder._add(std::make_shared<events::KBEvent>(m_intlEvent.key));
			break;
		}
		case SDL_MOUSEMOTION: {
			m_lastType = events::EventType::Mouse;
			mouse.set(m_intlEvent.motion);
			if (recorder.state())
				recorder._add(std::make_shared<events::MMEvent>(m_intlEvent.motion));
			break;
		}
		case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP: {
			m_lastType = events::EventType::Mouse;
			mouse.set(m_intlEvent.button);
			if (recorder.state())
				recorder._add(std::make_shared<events::MBEvent>(m_intlEvent.button));
			break;
		}
		case SDL_MOUSEWHEEL: {
			m_lastType = events::EventType::Mouse;
			mouse.set(m_intlEvent.wheel);
			if (recorder.state())
				recorder._add(std::make_shared<events::MWEvent>(m_intlEvent.wheel));
			break;
		}
		default:
			m_lastType = events::EventType::Unknown;
			//if (recorder.state())
			//	recorder._add(std::make_shared<events::UEvent>());
			break;
		}
	}

	void InputManager::reset() {
		keyboard.reset();
		mouse.reset();
	}

	void InputManager::lock() noexcept {
		keyboard.lock();
		mouse.lock();
	}

	void InputManager::unlock() noexcept {
		keyboard.unlock();
		mouse.unlock();
	}

	bool InputManager::quitRequested() noexcept {
		auto tmp = m_quitState;
		m_quitState = false;
		return tmp;
	}

	events::EventType InputManager::lastEventType() const noexcept {
		return m_lastType;
	}
}