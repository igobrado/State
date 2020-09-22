#pragma once

#include <type_traits>
#include "StateMachineEvents.hxx"

namespace state{

	/**
	 * @brief Skeleton for all of machine's states.
	 */
	class MachineState {
	public:
		virtual ~MachineState() {};
	};
	
	/**
	 * @brief Template constraint for all classes that expect state as template argument.
	 */
	template<typename Type>
	concept StateConstraint = std::is_base_of<MachineState, Type>::value;

	/**
	 * @brief Template constraint for all classes that expect event as template argument.
	 */
	template<typename Type>
	concept EventConstraint = std::is_base_of<::events::Event, Type>::value;

	/**
	 * @brief Operation that indicates that state shall be changed.
	 */
	template<StateConstraint State>
	struct Transform {
		/**
		 * @brief Executes the transform operation.
		 * 
		 * @param machine
		 */
		template<typename Machine>
		void execute(Machine& machine) {
			machine.template transform<State>();
		}
	};

	/**
	 * @brief Operation that indicates that nothing shall be done on event that
			  returns this operation as result of handle method.
	 */
	struct NoOperation {
		template<typename Machine>
		void execute(Machine& machine){

		}
	};

}