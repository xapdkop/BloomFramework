#pragma once

#include <vector>
#include <memory>
#include <variant>
#include "Event.h"


namespace bloom::events {
	template <typename TEvent, typename = std::enable_if_t<std::is_base_of_v<Event, TEvent>>>
	class EventRecorder {
	public:
		EventRecorder(bool state = false) : m_state(state) {}

		void start(bool clearOldEvents = true) { m_state = true; if (clearOldEvents) m_events.clear(); }
		void stop() { m_state = false; }
		const std::vector<TEvent>& events() { return m_events; }
		void clear() { m_events.clear(); }
		bool state() const { return m_state; }
		size_t size() const { return m_events.size(); }

		std::variant<std::shared_ptr<QEvent>, std::shared_ptr<KBEvent>, std::shared_ptr<MMEvent>, std::shared_ptr<MBEvent>, std::shared_ptr<MWEvent>, std::shared_ptr<Event>> get(size_t i) const {
			switch (m_events[i]->type()) {
			case EventType::Quit:
				return std::dynamic_pointer_cast<QEvent>(m_events[i]);
			case EventType::Keyboard:
				return std::dynamic_pointer_cast<KBEvent>(m_events[i]);
			case EventType::MouseMotion:
				return std::dynamic_pointer_cast<MMEvent>(m_events[i]);
			case EventType::MouseButton:
				return std::dynamic_pointer_cast<MBEvent>(m_events[i]);
			case EventType::MouseWheel:
				return std::dynamic_pointer_cast<MWEvent>(m_events[i]);
			default:
				return m_events[i];
			}
		}

		void _add(std::shared_ptr<TEvent> event) { m_events.push_back(event); }

	private:
		bool m_state;
		std::vector<std::shared_ptr<TEvent>> m_events;
	};
}