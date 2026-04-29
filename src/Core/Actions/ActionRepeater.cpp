#include "ActionRepeater.hpp"

namespace sw::core
{
	ActionRepeater::ActionRepeater(std::unique_ptr<IActionNode> next, uint32_t count) :
			_next(std::move(next)),
			_count(count)
	{}

	bool ActionRepeater::execute(Unit& self, World& world)
	{
		bool hasStep = false;
		for (int i = 0; i < _count; i++)
		{
			if (_next->execute(self, world))
			{
				hasStep = true;
			}
			else
			{
				break;
			}
		}
		return hasStep;
	}
}
