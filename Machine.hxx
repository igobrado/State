#pragma once

#include <variant>
#include <tuple>
#include <functional>
#include <iostream>

#include "Types.hxx"


namespace state{

	/**
	 * @brief State machine class.
	 */
	template <StateConstraint... States>
	class StateMachine {
	public:
		/**
		 * @brief Changes the state to another @tparam.
		 */
		template <StateConstraint State>
		void transform()
		{
			m_CurrentState = &std::get<State>(m_States);
		}

		/**
		 * @brief Calls handle event from provided event and executes process
				  that event defines.
		 * 
		 * @param event Event to handle
		 */
		template<EventConstraint Event>
		void handle(Event const& event)
		{
			auto passEventState = [this, &event](auto statePtr){
				statePtr->handle(event).execute(*this);
			};

			std::visit(passEventState, m_CurrentState);
		}
	private:
		std::tuple<States...> m_States;
		std::variant<States*...> m_CurrentState{ &std::get<0>(m_States) };
	};

	class EndState : public MachineState {
	public:
		/**
		 * @brief Implement of event handle.
		 *
		 * @param event Event that shall be handled.
		 * @return Empty operation object.
		 */
		NoOperation handle(::events::StartApplication const& event) {
			std::cout << "Can't start application from End state!" << std::endl;
			return NoOperation{};
		}

		/**
		 * @brief Implement of event handle.
		 *
		 * @param event Event that shall be handled.
		 * @return Empty operation object.
		 */
		NoOperation handle(::events::PauseState const& event) {
			std::cout << "Ignoring: can't pause end state" << std::endl;
			return NoOperation{};
		}

		/**
		 * @brief Implement of event handle.
		 *
		 * @param event Event that shall be handled.
		 * @return Empty operation object.
		 */
		NoOperation handle(::events::Shutdown const& event) {
			// TODO:
			return NoOperation{};
		}
	};

 	class EntryState : public MachineState{
	public:

		/**
		 * @brief Implement of event handle.
		 *
		 * @param event Event that shall be handled.
		 * @return Empty operation object.
		 */
		NoOperation handle(::events::PauseState const& event ){
			// TODO: 
			return NoOperation{};
		}

		/**
		 * @brief Starts the application loop.
		 *
		 * @param event Event that shall be handled.
		 * @return Empty operation object.
		 */
		NoOperation handle(::events::StartApplication const& event) {
			std::cout << "Starting Game event loop" << std::endl;

				while (!m_ShouldStop.load()){

				}
				return {};
		}

		/**
		 * @brief Shutdowns the application and does the cleanup.
		 *
		 * @param event Event that shall be handled.
		 * @return Operation that indicates that state shall be changed.
		 */
		Transform<EndState> handle(::events::Shutdown const& event) {
			std::cout << "Shutdown application" << std::endl;
			bool expected{ false };

			m_ShouldStop.compare_exchange_strong(
				expected, 
				true,
				std::memory_order_release,
				std::memory_order_relaxed);
			return {};
		}
		
	private:
		std::atomic_bool m_ShouldStop;
	};
}