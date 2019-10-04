#pragma once

#include "SDL.h"
#include "Components/Position.h"
#include "Input/InputDefinitions.h"

namespace bloom::events {
	enum class EventType {
		Empty,
		Quit,
		Keyboard,
		Mouse, // keep it for backward compatibility
		MouseMotion,
		MouseButton,
		MouseWheel,
		Unknown
	};

	class Event {
	public:
		virtual EventType type() = 0;
	};

	class QEvent : public Event {
	public:
		EventType type() override { return EventType::Quit; }
	};

	class UEvent : public Event {
	public:
		EventType type() override { return EventType::Unknown; }
	};

	class KBEvent : public Event {
	public:
		KBEvent(const SDL_KeyboardEvent& kbe) : m_state(kbe.state), m_key(static_cast<input::KeyboardKey>(kbe.keysym.scancode)) {}
		KBEvent(bool state, input::KeyboardKey key) : m_state(state), m_key(key) {}

		EventType type() override { return EventType::Keyboard; }
		bool state() const { return m_state; }
		input::KeyboardKey key() const { return m_key; }

	private:
		bool m_state;
		input::KeyboardKey m_key;
	};

	class MMEvent : public Event {
	public:
		MMEvent(const SDL_MouseMotionEvent& mme) : m_position(mme.x, mme.y), m_difference(mme.xrel, mme.yrel) {}
		MMEvent(components::Position position, components::Position difference) : m_position(position), m_difference(difference) {}

		EventType type() override { return EventType::MouseMotion; }
		components::Position position() const { return m_position; }
		components::Position difference() const { return m_difference; }

	private:
		components::Position m_position;
		components::Position m_difference;
	};

	class MBEvent : public Event {
	public:
		MBEvent(const SDL_MouseButtonEvent& mme) : m_state(mme.state), m_button(static_cast<input::MouseButton>(mme.button)), m_position(mme.x, mme.y) {}
		MBEvent(bool state, input::MouseButton button, components::Position position) : m_state(state), m_button(button), m_position(position) {}

		EventType type() override { return EventType::MouseButton; }
		bool state() const { return m_state; }
		input::MouseButton button() const { return m_button; }
		components::Position position() const { return m_position; }

	private:
		bool m_state;
		input::MouseButton m_button;
		components::Position m_position;
	};

	class MWEvent : public Event {
	public:
		MWEvent(const SDL_MouseWheelEvent& mwe) : m_direction(!mwe.direction), m_scroll(mwe.x, mwe.y) {
			if (!m_direction) { // follow remarks from https://wiki.libsdl.org/SDL_MouseWheelEvent
				m_scroll.x = -m_scroll.x;
				m_scroll.y = -m_scroll.y;
			}
		}

		EventType type() override { return EventType::MouseWheel; }
		// true - normal, false - flipped
		bool direction() const { return m_direction; }
		components::Position scroll() const { return m_scroll; }

	private:
		bool m_direction;
		components::Position m_scroll;
	};
}