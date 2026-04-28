#include "DelayedAction.hpp"

namespace sw::core
{
	DelayedAction::DelayedAction(std::unique_ptr<IActionNode> next, bool startState) :
			_next(std::move(next)),
			_prevState(startState)
	{}

	bool DelayedAction::execute(Unit& self, World& world)
	{
		const bool prevState = _prevState;
		_prevState = _next->execute(self, world);
		return prevState;
	}
}
