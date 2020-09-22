#pragma once

namespace events{

	/**
	 * @brief Skeleton for event objects.
	 */
	struct Event {
	public:
		virtual ~Event() {};
	};

	struct StartApplication : public Event {};
	struct TransformState : public Event {};
	struct PauseState : public Event {};
	struct Shutdown : public Event {};
}