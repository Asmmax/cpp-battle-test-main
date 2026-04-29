#pragma once

#include <functional>
#include <vector>

namespace sw::core
{
	class IActionNode;
	class World;

	class Simulation
	{
	public:
		using Command = std::function<void(World&)>;

	private:
		int _stepCounter{};
		std::vector<Command> _commandQueue{};

	public:
		void scheduleCommand(Command command);
		int getStepNum();
		bool step(World& world);
		void run(World& world);
	};
}
