#include "TriggerAction.hpp"

namespace sw::core
{
	TriggerAction::TriggerAction(std::unique_ptr<IActionNode> next) :
			_next(std::move(next))
	{}

	bool TriggerAction::execute(Unit& self, World& world)
	{
		if (_state)
		{
			return true;
		}

		_state = _next->execute(self, world);
		return _state;
	}
}
