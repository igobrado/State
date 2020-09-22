#pragma once

#include "Machine.hxx"

namespace machine {
	using Application = ::state::StateMachine<::state::EntryState, ::state::EndState>;
}