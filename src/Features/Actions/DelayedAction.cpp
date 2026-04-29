#include "DelayedAction.hpp"

namespace sw::features
{
	DelayedAction::DelayedAction(std::unique_ptr<core::IActionNode> next, bool startState) :
			_next(std::move(next)),
			_prevState(startState)
	{}

	bool DelayedAction::execute(core::Unit& self, core::World& world)
	{
		const bool prevState = _prevState;
		_prevState = _next->execute(self, world);
		return prevState;
	}
}
