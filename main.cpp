#include "StateMachine.hxx"

#include <future>

int main()
{
	machine::Application game{};

	game.handle(::events::PauseState{});
	auto handle = std::async(std::launch::async, [&game]() {
		game.handle(::events::StartApplication{});
		});

	std::cout << "Game is running and Main thread is waiting to finish" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	game.handle(::events::Shutdown{});
	handle.wait();
}