#include "TriggerAction.hpp"

namespace sw::features
{
	TriggerAction::TriggerAction(std::unique_ptr<core::IActionNode> next) :
			_next(std::move(next))
	{}

	bool TriggerAction::execute(core::Unit& self, core::World& world)
	{
		if (_state)
		{
			return true;
		}

		_state = _next->execute(self, world);
		return _state;
	}
}
