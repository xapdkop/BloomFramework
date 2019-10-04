#pragma once

namespace bloom::events {
	enum class EventType {
		Empty,
		Quit,
		Keyboard,
		Mouse,
		Unknown
	};

	class Event {
	public:
		virtual EventType type() = 0;
	};
}